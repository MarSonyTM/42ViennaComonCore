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

# Start server
print_header "Server Startup"
./webserv config/test1.conf &
SERVER_PID=$!
sleep 2

# Verify server is running and listening
if ! pgrep -x "webserv" > /dev/null; then
    print_result 1 "Server failed to start"
    exit 1
fi

echo "Testing connection to server..."
# Test basic connection
response=$(curl -s -w "%{http_code}" --max-time 5 http://localhost:8082/ -o /dev/null)

if [ "$response" != "200" ]; then
    print_result 1 "Server not responding on port 8082" "Got: $response"
    kill $SERVER_PID
    exit 1
fi
print_result 0 "Server started and responding"

# Test POST with different sizes
print_header "Testing POST Size Limits"

echo "Testing 4MB POST..."
# Should succeed (4MB < 5MB limit)
response=$(dd if=/dev/zero bs=1M count=4 2>/dev/null | curl -s -X POST \
    -H "Content-Type: text/plain" \
    --data-binary @- \
    --max-time 5 \
    -w "%{http_code}" \
    -o /dev/null \
    http://localhost:8082/uploads/)

print_result $? "POST 4MB file" "Response code: $response"

echo "Testing 6MB POST..."
# Should fail (6MB > 5MB limit)
response=$(dd if=/dev/zero bs=1M count=6 2>/dev/null | curl -s -X POST \
    -H "Content-Type: text/plain" \
    --data-binary @- \
    --max-time 5 \
    -w "%{http_code}" \
    -o /dev/null \
    http://localhost:8082/uploads/)

if [ "$response" = "413" ]; then
    print_result 0 "POST 6MB file (should fail)" "Got expected 413 response"
else
    print_result 1 "POST 6MB file (should fail)" "Expected 413, got: $response"
fi

# Cleanup
print_header "Cleanup"
kill $SERVER_PID
wait $SERVER_PID 2>/dev/null 