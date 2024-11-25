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
        echo -e "${GREEN}[✓] $2${NC}"
    else
        echo -e "${RED}[✗] $2${NC}"
        [ ! -z "$3" ] && echo -e "${RED}Details: $3${NC}"
    fi
}

# Kill ALL existing webserv processes
print_header "Cleanup"
pkill -9 webserv
sleep 2

# Start a fresh server
print_header "Starting Server"
./webserv config/default.conf &
SERVER_PID=$!
sleep 2

# Verify only one server is running
SERVER_COUNT=$(pgrep webserv | wc -l)
if [ "$SERVER_COUNT" -ne 1 ]; then
    print_result 1 "Server check" "Multiple servers running. Killing all and exiting."
    pkill -9 webserv
    exit 1
fi

# 1. Memory Leaks Check
print_header "Memory Leaks Check"
if [ "$(uname)" = "Darwin" ]; then
    # On macOS
    sudo leaks $SERVER_PID > leaks_output.txt
    if grep -q "0 leaks" leaks_output.txt; then
        print_result 0 "No memory leaks detected"
    else
        print_result 1 "Memory leaks found" "Check leaks_output.txt for details"
    fi
else
    # On Linux
    valgrind --leak-check=full ./webserv > leaks_output.txt 2>&1
    if grep -q "no leaks are possible" leaks_output.txt; then
        print_result 0 "No memory leaks detected"
    else
        print_result 1 "Memory leaks found" "Check leaks_output.txt for details"
    fi
fi
rm -f leaks_output.txt

# 2. Browser Compatibility
print_header "Browser Compatibility Check"
echo "Please test the following URLs in different browsers:"
echo "1. http://localhost:8080/ (main page)"
echo "2. http://localhost:8080/uploads/ (directory listing)"
echo "3. http://localhost:8080/nonexistent (404 error)"
echo "4. http://localhost:8080/cgi-bin/test.php (CGI)"

# 3. Config Parsing Test
print_header "Config Parsing Test"
echo "Testing invalid config..."
cat > config/invalid.conf << 'EOF'
server {
    invalid_directive;
    listen 8080
    missing_bracket
EOF
./webserv config/invalid.conf 2>&1 | grep -q "Error"
print_result $? "Invalid config handling"
rm -f config/invalid.conf

# 4. Error Handling Test
print_header "Error Handling Test"
echo "Testing malformed requests..."
curl -s -X INVALID http://localhost:8080/ > /dev/null
print_result $? "Invalid method handling"

curl -s -H "Content-Length: abc" http://localhost:8080/ > /dev/null
print_result $? "Invalid header handling"

# 5. C++98 Compliance Check
print_header "C++98 Compliance Check"
echo "Checking for modern C++ features..."
MODERN_FEATURES=0
for feature in "auto" "nullptr" "std::string_view" "std::array" "std::unordered_map" "std::shared_ptr" "std::unique_ptr" "constexpr" "decltype" "lambda"
do
    if grep -r "$feature" src/ > /dev/null 2>&1; then
        echo "Found modern feature: $feature"
        MODERN_FEATURES=1
    fi
done
[ $MODERN_FEATURES -eq 0 ]
print_result $? "C++98 compliance"

print_header "Final Checklist"
echo "1. Memory leaks: Run 'sudo leaks webserv' regularly"
echo "2. Browser tests: Test in Chrome, Firefox, Safari"
echo "3. Config files: Test with different configurations"
echo "4. Error handling: Test with malformed requests"
echo "5. C++98: Verify no modern C++ features are used" 