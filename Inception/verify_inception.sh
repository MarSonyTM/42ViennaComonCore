#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to check if command was successful
check_status() {
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✓ $1${NC}"
    else
        echo -e "${RED}✗ $1${NC}"
        ERRORS=$((ERRORS + 1))
    fi
}

# Function to print section headers
print_header() {
    echo -e "\n${YELLOW}=== $1 ===${NC}"
}

# Initialize error counter
ERRORS=0

# 1. Directory Structure Verification
print_header "Directory Structure Verification"

# Check root directory structure
echo "Checking root directory structure..."
[ -f "Makefile" ] && check_status "Makefile exists"
[ -d "secrets" ] && check_status "secrets directory exists"
[ -d "srcs" ] && check_status "srcs directory exists"

# Check secrets directory
echo -e "\nChecking secrets directory..."
[ -f "secrets/credentials.txt" ] && check_status "credentials.txt exists"
[ -f "secrets/db_password.txt" ] && check_status "db_password.txt exists"
[ -f "secrets/db_root_password.txt" ] && check_status "db_root_password.txt exists"

# Check srcs directory
echo -e "\nChecking srcs directory..."
[ -f "srcs/docker-compose.yml" ] && check_status "docker-compose.yml exists"
[ -f "srcs/.env" ] && check_status ".env exists"
[ -d "srcs/requirements" ] && check_status "requirements directory exists"

# 2. Docker Configuration Verification
print_header "Docker Configuration Verification"

# Check Docker images
echo "Checking Docker images..."
docker images | grep -E "srcs-nginx|srcs-wordpress|srcs-mariadb" > /dev/null
check_status "Docker images exist"

# Check for 'latest' tag usage
echo -e "\nChecking for 'latest' tag usage..."
! grep -r "latest" srcs/requirements/*/Dockerfile > /dev/null
check_status "No 'latest' tags found"

# Check for passwords in Dockerfiles
echo -e "\nChecking for passwords in Dockerfiles..."
! grep -r "PASSWORD" srcs/requirements/*/Dockerfile > /dev/null
check_status "No passwords in Dockerfiles"

# 3. Network Verification
print_header "Network Verification"

# Check Docker network
echo "Checking Docker network..."
docker network ls | grep "inception_network" > /dev/null
check_status "inception_network exists"

# Check port exposure
echo -e "\nChecking port exposure..."
docker port nginx | grep "443" > /dev/null
check_status "NGINX exposed on port 443"

# 4. Volume Verification
print_header "Volume Verification"

# Check volume directories based on OS
echo "Checking volume directories..."
if [ "$(uname)" = "Darwin" ]; then
    # macOS paths
    [ -d "/Users/$USER/data/wordpress" ] && check_status "WordPress volume exists"
    [ -d "/Users/$USER/data/mariadb" ] && check_status "MariaDB volume exists"
else
    # Linux paths
    [ -d "/home/$USER/data/wordpress" ] && check_status "WordPress volume exists"
    [ -d "/home/$USER/data/mariadb" ] && check_status "MariaDB volume exists"
fi

# 5. SSL/TLS Verification
print_header "SSL/TLS Verification"

# Check SSL configuration
echo "Checking SSL configuration..."
grep -r "ssl_protocols" srcs/requirements/nginx/conf/ | grep -E "TLSv1.2|TLSv1.3" > /dev/null
check_status "TLS version configuration correct"

# 6. Container Health Check
print_header "Container Health Check"

# Check if containers are running
echo "Checking container status..."
docker ps | grep "nginx" | grep "Up" > /dev/null
check_status "NGINX container is running"

docker ps | grep "wordpress" | grep "Up" > /dev/null
check_status "WordPress container is running"

docker ps | grep "mariadb" | grep "Up" > /dev/null
check_status "MariaDB container is running"

# 7. WordPress Configuration
print_header "WordPress Configuration"

# Check WordPress admin user
echo "Checking WordPress configuration..."
docker exec wordpress wp user list --allow-root --fields=user_login 2>/dev/null | grep -iE "admin|administrator|supervisor" > /dev/null
if [ $? -eq 0 ]; then
    echo -e "${RED}✗ WordPress admin username contains prohibited terms${NC}"
    ERRORS=$((ERRORS + 1))
else
    echo -e "${GREEN}✓ WordPress admin username is compliant${NC}"
fi

# 8. Environment Variables
print_header "Environment Variables Check"

# Check .env file
echo "Checking environment variables..."
[ -f "srcs/.env" ] && grep "DOMAIN_NAME" srcs/.env > /dev/null
check_status "Environment variables configured"

# Website Accessibility Check
print_header "Website Accessibility Check"

echo "Testing website accessibility..."
# Try multiple times with increased timeout and different options
(curl -k -I --max-time 5 "https://mafurnic.42.fr" 2>/dev/null | grep -E "HTTP/(1\.1|2) [23]0[0-9]" > /dev/null) || \
(curl -k -I --max-time 5 "https://localhost" 2>/dev/null | grep -E "HTTP/(1\.1|2) [23]0[0-9]" > /dev/null) || \
(curl -k -I --max-time 5 "https://127.0.0.1" 2>/dev/null | grep -E "HTTP/(1\.1|2) [23]0[0-9]" > /dev/null)
check_status "Website is accessible via HTTPS"

# Final Results
print_header "Verification Results"

if [ $ERRORS -eq 0 ]; then
    echo -e "${GREEN}All checks passed successfully!${NC}"
else
    echo -e "${RED}Found $ERRORS error(s) in verification${NC}"
fi

# Print instructions for manual verification
print_header "Manual Verification Required"

echo "Please verify the following manually:"
echo "1. Visit https://mafurnic.42.fr in your browser"
echo "2. Try logging in to WordPress admin panel"
echo "3. Check if you can create posts and upload media"
echo
echo "Testing Database Persistence:"
echo "4. Follow these steps to verify data persistence:"
echo "   a) Create a test post and upload an image"
echo "   b) Run these commands to restart containers:"
echo "      docker compose -f srcs/docker-compose.yml down"
echo "      docker compose -f srcs/docker-compose.yml up -d"
echo "   c) Visit https://mafurnic.42.fr/wp-admin again"
echo "   d) Verify your test post and image still exist"
echo
echo "Note: All data should persist after container restart"
echo "If data is lost, check volume configurations"

exit $ERRORS

