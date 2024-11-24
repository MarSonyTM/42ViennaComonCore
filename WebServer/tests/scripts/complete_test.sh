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

# Get absolute paths
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="$( cd "$SCRIPT_DIR/../.." && pwd )"

# Make sure we're in the WebServer root directory
cd "$ROOT_DIR"

# Kill any existing webserv processes
pkill -f webserv

# 1. Check compilation
print_header "Compilation Check"
make re
if [ $? -ne 0 ]; then
    print_result 1 "Compilation failed"
    exit 1
fi
print_result 0 "Compilation successful"

# 2. Setup environment
print_header "Environment Setup"
bash "$SCRIPT_DIR/setup_eval_env.sh"
if [ $? -ne 0 ]; then
    print_result 1 "Environment setup failed"
    exit 1
fi
print_result 0 "Environment setup complete"

# 3. Start server
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

# 4. Test Basic HTTP Methods
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

# 5. Test Error Pages
print_header "Testing Error Pages"
response=$(curl -s http://localhost:8080/nonexistent)
[[ "$response" == *"Custom 404"* ]]
print_result $? "Custom 404 page" "Response: $response" || exit 1

# 6. Test Client Body Size Limit
print_header "Testing Client Body Size Limit"
dd if=/dev/zero bs=1M count=11 2>/dev/null | tr '\0' 'X' > large_file.txt
response_code=$(curl -s -X POST -H "Content-Type: text/plain" --data-binary "@large_file.txt" -w "%{http_code}" -o /dev/null http://localhost:8080/)
rm -f large_file.txt

if [ "$response_code" = "413" ]; then
    print_result 0 "Client body size limit" "Got expected 413 response"
else
    print_result 1 "Client body size limit" "Expected 413, got: $response_code" || exit 1
fi

# 7. Test Multiple Ports
print_header "Testing Multiple Ports"
response1=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:8080/)
response2=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:8081/)
[ "$response1" = "200" ] && [ "$response2" = "200" ]
print_result $? "Multiple ports" "Port 8080: $response1, Port 8081: $response2" || exit 1

# 8. Test CGI
print_header "Testing CGI"
response=$(curl -s http://localhost:8080/cgi-bin/test.php)
[[ "$response" == *"CGI Test Successful"* ]]
print_result $? "CGI execution" "Response: $response" || exit 1

# 9. Test Directory Listing
print_header "Testing Directory Listing"
response=$(curl -s http://localhost:8080/uploads/)
[[ "$response" == *"Index"* || "$response" == *"Directory"* ]]
print_result $? "Directory listing" "Response: $response" || exit 1

# 10. Test File Upload
print_header "Testing File Upload"
echo "test content" > test_upload.txt
response=$(curl -s -X POST -F "file=@test_upload.txt" http://localhost:8080/uploads/)
rm -f test_upload.txt
[[ "$response" == *"success"* ]]
print_result $? "File upload" "Response: $response" || exit 1

# 11. Stress Test
print_header "Running Stress Test"
if command -v siege &> /dev/null; then
    siege_output=$(siege -b -t10S http://localhost:8080/ 2>&1)
    availability=$(echo "$siege_output" | grep "Availability:" | awk '{print $2}' | sed 's/%//')
    
    if (( $(echo "$availability > 99.5" | bc -l) )); then
        print_result 0 "Stress test" "Availability: $availability%"
    else
        print_result 1 "Stress test" "Availability below 99.5%: $availability%" || exit 1
    fi
else
    echo "Siege not installed, skipping stress test"
fi

# Cleanup
print_header "Cleanup"
kill $SERVER_PID
wait $SERVER_PID 2>/dev/null

print_header "All Tests Completed Successfully!"
echo "1. All HTTP methods working"
echo "2. Error pages working"
echo "3. Client body size limit working"
echo "4. Multiple ports working"
echo "5. CGI working"
echo "6. Directory listing working"
echo "7. File upload working"
echo "8. Stress test passed"

print_header "Final Checks"
echo "1. Run memory leak check:    leaks webserv"
echo "2. Test in browsers:         Open http://localhost:8080"
echo "3. Test config parsing:      Try different config files"
echo "4. Test error handling:      Try malformed requests"
echo "5. Verify C++98 compliance:  Check all source files" 