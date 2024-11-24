#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

print_header() {
    echo -e "\n${BLUE}=== $1 ===${NC}"
}

print_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}[✓] $2${NC}"
        return 0
    else
        echo -e "${RED}[✗] $2${NC}"
        [ ! -z "$3" ] && echo -e "${RED}Details: $3${NC}"
        return 1
    fi
}

# Kill any existing webserv processes
print_header "Cleanup"
pkill -9 webserv
sleep 2

# Compilation check
print_header "Compilation Check"
make re
if [ $? -ne 0 ]; then
    print_result 1 "Compilation failed"
    exit 1
fi
print_result 0 "Compilation successful"

# Start server
print_header "Server Startup"
./webserv config/default.conf &
SERVER_PID=$!
sleep 2

# Check if server is running
if ! pgrep -x "webserv" > /dev/null; then
    print_result 1 "Server failed to start"
    exit 1
fi
print_result 0 "Server started successfully"

# Test HTTP Methods
print_header "Testing HTTP Methods"

# GET Test
response=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:8080/)
[ "$response" = "200" ]
print_result $? "GET method" "Response code: $response" || exit 1

# POST Test
response=$(curl -s -X POST -H "Content-Type: text/plain" -d "test" -o /dev/null -w "%{http_code}" http://localhost:8080/uploads/)
[ "$response" = "200" ]
print_result $? "POST method" "Response code: $response" || exit 1

# DELETE Test
echo "test" > www/uploads/test_delete.txt
response=$(curl -s -X DELETE -o /dev/null -w "%{http_code}" http://localhost:8080/uploads/test_delete.txt)
[ "$response" = "200" ]
print_result $? "DELETE method" "Response code: $response" || exit 1

# Test Error Pages
print_header "Testing Error Pages"
response=$(curl -s http://localhost:8080/nonexistent)
[[ "$response" == *"Custom 404"* ]]
print_result $? "Custom 404 page" "Response: $response" || exit 1

# Test Client Body Size Limit
print_header "Testing Client Body Size Limit"
dd if=/dev/zero bs=1M count=11 2>/dev/null | tr '\0' 'X' > large_file.txt
response=$(curl -s -X POST -H "Content-Type: text/plain" --data-binary "@large_file.txt" -w "%{http_code}" -o /dev/null http://localhost:8080/)
rm -f large_file.txt
[ "$response" = "413" ]
print_result $? "Client body size limit" "Response code: $response" || exit 1

# Test Multiple Ports
print_header "Testing Multiple Ports"
response1=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:8080/)
response2=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:8081/)
[ "$response1" = "200" ] && [ "$response2" = "200" ]
print_result $? "Multiple ports" "Port 8080: $response1, Port 8081: $response2" || exit 1

# Test CGI
print_header "Testing CGI"
response=$(curl -s http://localhost:8080/cgi-bin/test.php)
[[ "$response" == *"CGI Test Successful"* ]]
print_result $? "CGI execution" "Response: $response" || exit 1

# Test Directory Listing
print_header "Testing Directory Listing"
response=$(curl -s http://localhost:8080/uploads/)
[[ "$response" == *"Index"* || "$response" == *"Directory"* ]]
print_result $? "Directory listing" "Response: $response" || exit 1

# Test File Upload
print_header "Testing File Upload"
echo "test content" > test_upload.txt
response=$(curl -s -X POST -F "file=@test_upload.txt" http://localhost:8080/uploads/)
rm -f test_upload.txt
[[ "$response" == *"success"* ]]
print_result $? "File upload" "Response: $response" || exit 1

# Memory Leaks Check
print_header "Memory Leaks Check"
if [ "$(uname)" = "Darwin" ]; then
    # On macOS
    sudo leaks $SERVER_PID > leaks_output.txt 2>/dev/null
    if grep -q "0 leaks" leaks_output.txt; then
        print_result 0 "No memory leaks detected"
    else
        print_result 1 "Memory leaks found" "Check leaks_output.txt for details"
    fi
else
    # On Ubuntu
    valgrind --leak-check=full ./webserv > leaks_output.txt 2>&1
    if grep -q "no leaks are possible" leaks_output.txt; then
        print_result 0 "No memory leaks detected"
    else
        print_result 1 "Memory leaks found" "Check leaks_output.txt for details"
    fi
fi
rm -f leaks_output.txt

# Cleanup
print_header "Cleanup"
kill $SERVER_PID
wait $SERVER_PID 2>/dev/null

print_header "All Tests Completed!"
echo "1. All HTTP methods working"
echo "2. Error pages working"
echo "3. Client body size limit working"
echo "4. Multiple ports working"
echo "5. CGI working"
echo "6. Directory listing working"
echo "7. File upload working"
echo "8. Memory leaks checked"

print_header "Final Checklist"
echo "1. Test in browsers:         Open http://localhost:8080"
echo "2. Test config parsing:      Try different config files"
echo "3. Test error handling:      Try malformed requests"
echo "4. Verify C++98 compliance:  Check all source files" 