#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}🔒 Testing HTTPS setup...${NC}\n"

# Function to test HTTPS endpoint
test_endpoint() {
    local url=$1
    local name=$2
    echo "Testing $name (${url})..."
    
    response=$(curl -k -s -o /dev/null -w "%{http_code}" $url)
    
    if [ $response -eq 200 ] || [ $response -eq 301 ] || [ $response -eq 302 ]; then
        echo -e "${GREEN}✅ $name is accessible over HTTPS (Status: $response)${NC}"
        return 0
    else
        echo -e "${RED}❌ $name is not accessible (Status: $response)${NC}"
        return 1
    fi
}

# Add hosts entries
echo "Adding hosts entries..."
if ! grep -q "frontend" /etc/hosts; then
    echo "127.0.0.1 frontend" | sudo tee -a /etc/hosts > /dev/null
fi
if ! grep -q "backend" /etc/hosts; then
    echo "127.0.0.1 backend" | sudo tee -a /etc/hosts > /dev/null
fi

# Test frontend HTTPS
test_endpoint "https://frontend:3000" "Frontend"
frontend_status=$?

# Test backend HTTPS
test_endpoint "https://backend:3001/health" "Backend health endpoint"
backend_status=$?

# Test HTTP to HTTPS redirect
echo -e "\nTesting HTTP to HTTPS redirect..."
redirect_response=$(curl -s -o /dev/null -w "%{redirect_url}" http://frontend:3000)

if [[ $redirect_response == https://* ]]; then
    echo -e "${GREEN}✅ HTTP to HTTPS redirect is working${NC}"
    redirect_status=0
else
    echo -e "${RED}❌ HTTP to HTTPS redirect is not working${NC}"
    redirect_status=1
fi

# Test backend database connection over HTTPS
echo -e "\nTesting database connection over HTTPS..."
db_response=$(curl -k -s https://backend:3001/db-test)

if [[ $db_response == *"ok"* ]]; then
    echo -e "${GREEN}✅ Database connection over HTTPS is working${NC}"
    db_status=0
else
    echo -e "${RED}❌ Database connection over HTTPS failed${NC}"
    db_status=1
fi

# Overall status
echo -e "\nOverall HTTPS Setup Status:"
if [ $frontend_status -eq 0 ] && [ $backend_status -eq 0 ] && [ $redirect_status -eq 0 ] && [ $db_status -eq 0 ]; then
    echo -e "${GREEN}✅ All HTTPS components are working correctly!${NC}"
    exit 0
else
    echo -e "${RED}❌ Some HTTPS components are not working correctly${NC}"
    exit 1
fi