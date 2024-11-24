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

# 1. HTTP Methods
print_header "HTTP Methods"

# GET
response=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:8080/)
[ "$response" = "200" ]
print_result $? "GET method" "Response: $response"

# POST
response=$(curl -s -X POST -H "Content-Type: text/plain" -d "test" -o /dev/null -w "%{http_code}" http://localhost:8080/uploads/)
[ "$response" = "200" ]
print_result $? "POST method" "Response: $response"

# DELETE
echo "test" > www/uploads/test_delete.txt
response=$(curl -s -X DELETE -o /dev/null -w "%{http_code}" http://localhost:8080/uploads/test_delete.txt)
[ "$response" = "200" ]
print_result $? "DELETE method" "Response: $response"

# 2. Error Pages
print_header "Error Pages"
response=$(curl -s http://localhost:8080/nonexistent)
[[ "$response" == *"Custom 404"* ]]
print_result $? "Custom error pages" "Response: $response"

# 3. Client Body Size
print_header "Client Body Size"
dd if=/dev/zero bs=1M count=11 2>/dev/null | tr '\0' 'X' > large_file.txt
response=$(curl -s -X POST -H "Content-Type: text/plain" --data-binary "@large_file.txt" -w "%{http_code}" http://localhost:8080/)
rm -f large_file.txt
[ "$response" = "413" ]
print_result $? "Client body size limit" "Response: $response" 