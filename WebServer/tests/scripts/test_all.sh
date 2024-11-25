#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Trap Ctrl+C and other exit signals
trap 'echo -e "\n${YELLOW}Caught exit signal. Cleaning up...${NC}"; cleanup_servers; exit 1' INT TERM EXIT

# Function to run command with timeout
run_with_timeout() {
    local timeout=$1
    shift
    echo -e "${YELLOW}Running command: $@${NC}"
    
    # Start the command in background
    $@ &
    local pid=$!
    
    # Timer
    local count=0
    echo -ne "${YELLOW}Waiting: "
    while kill -0 $pid 2>/dev/null; do
        if [ $count -ge $timeout ]; then
            echo -e "\nTimeout reached after ${timeout} seconds${NC}"
            kill -9 $pid 2>/dev/null
            return 1
        fi
        echo -n "."
        sleep 1
        ((count++))
    done
    echo -e "${NC}"
    
    wait $pid
    return $?
}

# Function to kill existing webserv processes
cleanup_servers() {
    echo -e "\n${YELLOW}Cleaning up existing server processes...${NC}"
    pkill -9 webserv 2>/dev/null || true
    echo "Waiting for processes to clean up..."
    sleep 2
}

echo -e "${YELLOW}Starting comprehensive WebServer testing...${NC}\n"

# Initial cleanup
cleanup_servers

# 1. Build Check
echo -e "${YELLOW}1. Building Project...${NC}"
echo "Running make clean..."
make clean 2>/dev/null || true
echo "Running make..."
make
if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi
echo -e "${GREEN}Build successful!${NC}\n"

# 2. Configuration Tests
echo -e "${YELLOW}2. Testing Configuration Files...${NC}"

# Create test configuration files
echo "Creating test configuration files..."

echo "Creating invalid_port.conf..."
echo "server {
    listen 65536;
    root www;
}" > config/invalid_port.conf

echo "Creating invalid_root.conf..."
echo "server {
    listen 8082;
}" > config/invalid_root.conf

echo "Creating invalid_syntax.conf..."
echo "server {
    listen 8083;
    root www;
    invalid_directive;
}" > config/invalid_syntax.conf

# Test invalid port
echo -e "\n${YELLOW}Testing invalid port configuration...${NC}"
run_with_timeout 5 ./webserv config/invalid_port.conf
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓ Invalid port test passed (server failed as expected)${NC}"
else
    echo -e "${RED}✗ Invalid port test failed (server should not start with invalid port)${NC}"
fi

# Test invalid root
echo -e "\n${YELLOW}Testing invalid root configuration...${NC}"
run_with_timeout 5 ./webserv config/invalid_root.conf
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓ Invalid root test passed (server failed as expected)${NC}"
else
    echo -e "${RED}✗ Invalid root test failed (server should not start without root)${NC}"
fi

# Test invalid syntax
echo -e "\n${YELLOW}Testing invalid syntax configuration...${NC}"
run_with_timeout 5 ./webserv config/invalid_syntax.conf
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓ Invalid syntax test passed (server failed as expected)${NC}"
else
    echo -e "${RED}✗ Invalid syntax test failed (server should not start with invalid syntax)${NC}"
fi

# 3. HTTP Method Tests
echo -e "\n${YELLOW}3. Testing HTTP Methods...${NC}"

# Make sure no other server is running
cleanup_servers

# Start server in background with default config
echo "Starting server with default configuration..."
./webserv config/default.conf &
SERVER_PID=$!
echo "Waiting for server to start..."
sleep 2

# GET request
echo "Testing GET request..."
curl -s -o /dev/null -w "%{http_code}" http://localhost:8080/ | grep -q "200"
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ GET request test passed${NC}"
else
    echo -e "${RED}✗ GET request test failed${NC}"
fi

# POST request
echo "Testing POST request..."
curl -s -X POST -d "test=data" -o /dev/null -w "%{http_code}" http://localhost:8080/uploads/ | grep -q "200"
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ POST request test passed${NC}"
else
    echo -e "${RED}✗ POST request test failed${NC}"
fi

# DELETE request
echo "Testing DELETE request..."
echo "Creating test file for DELETE..."
echo "test content" > www/uploads/test_file.txt
curl -s -X DELETE -o /dev/null -w "%{http_code}" http://localhost:8080/uploads/test_file.txt | grep -q "200"
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ DELETE request test passed${NC}"
else
    echo -e "${RED}✗ DELETE request test failed${NC}"
fi

# Test Multiple Ports
echo -e "\n${YELLOW}Testing Multiple Ports...${NC}"
echo "Testing second port (8081)..."
curl -s -o /dev/null -w "%{http_code}" http://localhost:8081/ | grep -q "200"
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Multiple ports test passed${NC}"
else
    echo -e "${RED}✗ Multiple ports test failed${NC}"
fi

# Test Client Body Size Limit
echo -e "\n${YELLOW}Testing Client Body Size Limit...${NC}"
dd if=/dev/zero bs=1M count=21 2>/dev/null | curl -s -X POST -d @- -o /dev/null -w "%{http_code}" http://localhost:8080/uploads/ | grep -q "413"
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Client body size limit test passed${NC}"
else
    echo -e "${RED}✗ Client body size limit test failed${NC}"
fi

# Test Directory Listing
echo -e "\n${YELLOW}Testing Directory Listing...${NC}"
response=$(curl -s http://localhost:8080/uploads/)
if echo "$response" | grep -q "Directory listing"; then
    echo -e "${GREEN}✓ Directory listing test passed${NC}"
else
    echo -e "${RED}✗ Directory listing test failed${NC}"
fi

# Test CGI Execution
echo -e "\n${YELLOW}Testing CGI...${NC}"
echo "Testing GET request to CGI..."
response=$(curl -s "http://localhost:8080/cgi-bin/test.php?test=value")
if echo "$response" | grep -q "CGI Test Successful"; then
    echo -e "${GREEN}✓ CGI GET test passed${NC}"
else
    echo -e "${RED}✗ CGI GET test failed${NC}"
fi

echo "Testing POST request to CGI..."
response=$(curl -s -X POST -d "postdata=test" "http://localhost:8080/cgi-bin/test.php")
if echo "$response" | grep -q "CGI Test Successful" && echo "$response" | grep -q "POST Data"; then
    echo -e "${GREEN}✓ CGI POST test passed${NC}"
else
    echo -e "${RED}✗ CGI POST test failed${NC}"
fi

# Test Different HTTP Methods
echo -e "\n${YELLOW}Testing HTTP Method Restrictions...${NC}"
curl -s -X PUT -o /dev/null -w "%{http_code}" http://localhost:8080/ | grep -q "405"
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Method not allowed test passed${NC}"
else
    echo -e "${RED}✗ Method not allowed test failed${NC}"
fi

# Test File Upload
echo -e "\n${YELLOW}Testing File Upload...${NC}"
echo "test file content" > test_upload.txt
curl -s -X POST -F "file=@test_upload.txt" -o /dev/null -w "%{http_code}" http://localhost:8080/uploads/ | grep -q "200"
if [ $? -eq 0 ] && [ -f "www/uploads/test_upload.txt" ]; then
    echo -e "${GREEN}✓ File upload test passed${NC}"
else
    echo -e "${RED}✗ File upload test failed${NC}"
fi
rm -f test_upload.txt

# 4. Error Page Tests
echo -e "\n${YELLOW}4. Testing Error Pages...${NC}"
echo "Testing 404 error page..."
curl -s -o /dev/null -w "%{http_code}" http://localhost:8080/nonexistent | grep -q "404"
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ 404 error page test passed${NC}"
else
    echo -e "${RED}✗ 404 error page test failed${NC}"
fi

# 5. Memory Leak Check
echo -e "\n${YELLOW}5. Checking for Memory Leaks...${NC}"
if command -v valgrind &> /dev/null; then
    echo "Running valgrind..."
    valgrind --leak-check=full ./webserv config/default.conf &
    VALGRIND_PID=$!
    sleep 5
    kill $VALGRIND_PID 2>/dev/null || true
else
    echo -e "${YELLOW}Valgrind not installed. Skipping memory leak check.${NC}"
fi

# Final cleanup
echo -e "\n${YELLOW}Performing final cleanup...${NC}"
cleanup_servers
echo "Running make fclean..."
make fclean

echo -e "\n${YELLOW}Testing Complete!${NC}" 