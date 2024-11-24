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
        echo -e "${RED}Details: $3${NC}"
    fi
}

# 1. Memory Leaks Check
print_header "Memory Leaks Check"
leaks webserv > leaks_output.txt
if grep -q "0 leaks" leaks_output.txt; then
    print_result 0 "No memory leaks detected"
else
    print_result 1 "Memory leaks found" "Check leaks_output.txt for details"
fi
rm leaks_output.txt

# 2. Browser Compatibility
print_header "Browser Compatibility Check"
echo "Please test the following URLs in different browsers:"
echo "1. http://localhost:8080/ (main page)"
echo "2. http://localhost:8080/uploads/ (directory listing)"
echo "3. http://localhost:8080/nonexistent (404 error)"
echo "4. http://localhost:8080/cgi-bin/test.php (CGI)"

# 3. Config Parsing
print_header "Config Parsing Test"
cp config/default.conf config/test.conf
echo "Testing invalid config..."
./webserv config/invalid.conf 2>&1 | grep -q "Error"
print_result $? "Invalid config handling"

# 4. Error Handling
print_header "Error Handling Test"
echo "Testing malformed requests..."
curl -s -X INVALID http://localhost:8080/ > /dev/null
print_result $? "Invalid method handling"

curl -s -H "Content-Length: abc" http://localhost:8080/ > /dev/null
print_result $? "Invalid header handling"

# 5. C++98 Compliance
print_header "C++98 Compliance Check"
echo "Checking for modern C++ features..."
! grep -r "auto" src/ && \
! grep -r "nullptr" src/ && \
! grep -r "std::string_view" src/ && \
! grep -r "std::array" src/
print_result $? "C++98 compliance"

print_header "Final Checklist"
echo "1. Memory leaks: Run 'leaks webserv' regularly"
echo "2. Browser tests: Test in Chrome, Firefox, Safari"
echo "3. Config files: Test with different configurations"
echo "4. Error handling: Test with malformed requests"
echo "5. C++98: Verify no modern C++ features are used" 