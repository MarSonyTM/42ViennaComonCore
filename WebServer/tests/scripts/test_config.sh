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

# Test 1: Invalid Port
print_header "Testing Invalid Port"
cat > config/invalid_port.conf << 'EOF'
server {
    listen 999999;
    host 127.0.0.1;
    root www;
}
EOF

output=$(./webserv config/invalid_port.conf 2>&1)
if [[ "$output" == *"Invalid port"* ]]; then
    print_result 0 "Invalid port test" "Server correctly rejected invalid port"
else
    print_result 1 "Invalid port test" "Server should reject port > 65535, got: $output"
fi

# Test 2: Missing Root
print_header "Testing Missing Root"
cat > config/invalid_root.conf << 'EOF'
server {
    listen 8082;
    host 127.0.0.1;
}
EOF

output=$(./webserv config/invalid_root.conf 2>&1)
if [[ "$output" == *"Root directory not specified"* ]]; then
    print_result 0 "Missing root test" "Server correctly detected missing root"
else
    print_result 1 "Missing root test" "Server should require root directive, got: $output"
fi

# Test 3: Invalid Syntax
print_header "Testing Invalid Syntax"
cat > config/invalid_syntax.conf << 'EOF'
server {
    listen 8082;
    host 127.0.0.1;
    root www;
    invalid_directive;
}
EOF

# Run the test in background with a timeout
./webserv config/invalid_syntax.conf 2>&1 & 
pid=$!
sleep 3
if kill -0 $pid 2>/dev/null; then
    kill -9 $pid
    print_result 1 "Invalid syntax test" "Server hung on invalid syntax"
else
    wait $pid
    status=$?
    if [ $status -ne 0 ]; then
        print_result 0 "Invalid syntax test" "Server correctly rejected invalid syntax"
    else
        print_result 1 "Invalid syntax test" "Server should reject invalid syntax"
    fi
fi

print_header "Configuration Tests Complete" 