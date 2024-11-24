#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

print_header() {
    echo -e "\n${YELLOW}=== $1 ===${NC}"
}

print_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}[PASS]${NC} $2"
    else
        echo -e "${RED}[FAIL]${NC} $2"
        echo -e "${RED}Details: $3${NC}"
    fi
}

# Go to WebServer root directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR/../.."

# Setup environment
print_header "Setting up environment"
./tests/scripts/setup_eval_env.sh

# Start server if not running
if ! pgrep -x "webserv" > /dev/null; then
    print_header "Starting Server"
    ./webserv config/default.conf &
    SERVER_PID=$!
    sleep 2  # Wait for server to start
fi

# 1. Mandatory Part Tests
print_header "Mandatory Part Tests"

# Check compilation
make re
print_result $? "Compilation" "Make sure no relink"

# Check poll/select usage
grep -r "poll(" src/*.cpp > /dev/null
print_result $? "Using poll() for I/O multiplexing"

# 2. Configuration Tests
print_header "Configuration Tests"

# Test multiple ports
response1=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:8080/)
response2=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:8081/)
[ "$response1" = "200" ] && [ "$response2" = "200" ]
print_result $? "Multiple ports" "Port 8080: $response1, Port 8081: $response2"

# Test server names
response=$(curl -s -H "Host: example.com" http://localhost:8080/)
[[ "$response" == *"Welcome to WebServ"* ]]
print_result $? "Server name routing" "Response: $response"

# Test error pages
response=$(curl -s http://localhost:8080/nonexistent)
[[ "$response" == *"Custom 404"* ]]
print_result $? "Custom error pages" "Response: $response"

# Test client body size
dd if=/dev/zero bs=1M count=11 2>/dev/null | tr '\0' 'X' > large_file.txt
response=$(curl -s -X POST -H "Content-Type: text/plain" --data-binary "@large_file.txt" -w "%{http_code}" http://localhost:8080/)
rm -f large_file.txt
[ "$response" = "413" ]
print_result $? "Client body size limit" "Got: $response"

# 3. HTTP Methods
print_header "HTTP Methods Tests"

# GET Test
response=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:8080/)
[ "$response" = "200" ]
print_result $? "GET method" "Got: $response"

# POST Test
response=$(curl -s -X POST -H "Content-Type: text/plain" -d "test" -o /dev/null -w "%{http_code}" http://localhost:8080/)
[ "$response" = "200" ]
print_result $? "POST method" "Got: $response"

# DELETE Test
echo "test" > www/uploads/test_delete.txt
response=$(curl -s -X DELETE -o /dev/null -w "%{http_code}" http://localhost:8080/uploads/test_delete.txt)
[ "$response" = "200" ]
print_result $? "DELETE method" "Got: $response"

# 4. CGI Tests
print_header "CGI Tests"

response=$(curl -s http://localhost:8080/cgi-bin/test.php)
[[ "$response" == *"CGI Test Successful"* ]]
print_result $? "CGI execution" "Response: $response"

# 5. Directory Listing
print_header "Directory Listing Tests"

response=$(curl -s http://localhost:8080/uploads/)
[[ "$response" == *"Index of"* || "$response" == *"Directory listing"* ]]
print_result $? "Directory listing" "Response: $response"

# 6. File Upload
print_header "File Upload Tests"

echo "test content" > test_upload.txt
response=$(curl -s -X POST -F "file=@test_upload.txt" http://localhost:8080/uploads/)
rm -f test_upload.txt
[[ "$response" == *"success"* ]]
print_result $? "File upload" "Response: $response"

# 7. Stress Test
print_header "Stress Tests"

if command -v siege &> /dev/null; then
    siege_output=$(siege -b -t10S http://localhost:8080/ 2>&1)
    availability=$(echo "$siege_output" | grep "Availability:" | awk '{print $2}' | sed 's/%//')
    
    if (( $(echo "$availability > 99.5" | bc -l) )); then
        print_result 0 "Siege test" "Availability: $availability%"
    else
        print_result 1 "Siege test" "Availability below 99.5%: $availability%"
    fi
else
    echo "Siege not installed, skipping stress test"
fi

# Stop server if we started it
if [ -n "$SERVER_PID" ]; then
    print_header "Cleanup"
    kill $SERVER_PID
    wait $SERVER_PID 2>/dev/null
fi

print_header "Evaluation Summary"
echo "1. Check for memory leaks using: leaks webserv"
echo "2. Verify browser compatibility"
echo "3. Ensure no crashes or unexpected behavior" 