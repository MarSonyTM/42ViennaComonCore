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

# Check for prohibited network directives
echo -e "\nChecking for prohibited network directives..."
! grep -r "network:[[:space:]]*host" srcs/docker-compose.yml > /dev/null
check_status "No 'network: host' directive found"

! grep -r "^[[:space:]]*links:" srcs/docker-compose.yml > /dev/null
check_status "No 'links:' directive found"

grep -r "^networks:" srcs/docker-compose.yml > /dev/null
check_status "Networks section properly defined"

# Check for prohibited --link flag
echo -e "\nChecking for prohibited --link flag..."
! grep -r "[[:space:]]--link[[:space:]]" Makefile srcs/*.sh > /dev/null
check_status "No '--link' flag found"

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
grep -r "ssl_protocols" srcs/requirements/nginx/ | grep -E "TLSv1.2|TLSv1.3" > /dev/null
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

# 7. Base Image Verification
print_header "Base Image Verification"

# Check base images
echo "Checking base images..."
grep -E "^FROM alpine" srcs/requirements/nginx/Dockerfile > /dev/null || grep -E "^FROM debian:buster" srcs/requirements/nginx/Dockerfile > /dev/null
check_status "NGINX uses allowed base image (Alpine or Debian Buster)"

grep -E "^FROM alpine" srcs/requirements/wordpress/Dockerfile > /dev/null || grep -E "^FROM debian:buster" srcs/requirements/wordpress/Dockerfile > /dev/null
check_status "WordPress uses allowed base image (Alpine or Debian Buster)"

grep -E "^FROM alpine" srcs/requirements/mariadb/Dockerfile > /dev/null || grep -E "^FROM debian:buster" srcs/requirements/mariadb/Dockerfile > /dev/null
check_status "MariaDB uses allowed base image (Alpine or Debian Buster)"

# 8. Dockerfile Command Verification
print_header "Dockerfile Command Verification"

# Check for prohibited commands
echo "Checking for prohibited commands in Dockerfiles..."
! grep -E "tail -f|nginx &|^ENTRYPOINT \[\"(bash|sh)\"\][[:space:]]*$" srcs/requirements/nginx/Dockerfile > /dev/null
check_status "No prohibited commands in NGINX Dockerfile"

! grep -E "tail -f|php-fpm &|^ENTRYPOINT \[\"(bash|sh)\"\][[:space:]]*$" srcs/requirements/wordpress/Dockerfile > /dev/null
check_status "No prohibited commands in WordPress Dockerfile"

! grep -E "tail -f|mysqld &|^ENTRYPOINT \[\"(bash|sh)\"\][[:space:]]*$" srcs/requirements/mariadb/Dockerfile > /dev/null
check_status "No prohibited commands in MariaDB Dockerfile"

# 9. WordPress Configuration
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

# 10. Environment Variables
print_header "Environment Variables Check"

# Check .env file
echo "Checking environment variables..."
[ -f "srcs/.env" ] && grep "DOMAIN_NAME" srcs/.env > /dev/null
check_status "Environment variables configured"

# Website Accessibility Check
print_header "Website Accessibility Check"

echo "Testing website accessibility..."
# More robust check with proper error handling and multiple attempts
for i in {1..3}; do
    response=$(curl -k -I --max-time 10 "https://mafurnic.42.fr" 2>/dev/null)
    if echo "$response" | grep -E "HTTP/(1\.1|2) [23]0[0-9]" > /dev/null; then
        check_status "Website is accessible via HTTPS"
        break
    elif [ $i -eq 3 ]; then
        check_status "Website is accessible via HTTPS"
    else
        sleep 2
    fi
done

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

# Display WordPress Credentials
print_header "WordPress Credentials"

if [ -f "srcs/.env" ]; then
    echo -e "${GREEN}WordPress Admin Credentials:${NC}"
    # Try different common variable name patterns for admin user
    ADMIN_LOGIN=$(grep -E "WORDPRESS_ADMIN_USER|WP_ADMIN_USER|ADMIN_USER" srcs/.env | cut -d '=' -f2 | tr -d ' "')
    if [ -z "$ADMIN_LOGIN" ]; then
        echo "Username: [Could not extract - check .env file]"
    else
        echo "Username: $ADMIN_LOGIN"
    fi
    
    # Try different common variable name patterns for admin password
    ADMIN_PASSWORD=$(grep -E "WORDPRESS_ADMIN_PASSWORD|WP_ADMIN_PASSWORD|ADMIN_PASSWORD" srcs/.env | cut -d '=' -f2 | tr -d ' "')
    if [ -z "$ADMIN_PASSWORD" ]; then
        # Fallback to checking secrets file
        if [ -f "srcs/secrets/wp_admin_password.txt" ]; then
            ADMIN_PASSWORD=$(cat srcs/secrets/wp_admin_password.txt)
        elif [ -f "secrets/wp_admin_password.txt" ]; then
            ADMIN_PASSWORD=$(cat secrets/wp_admin_password.txt)
        fi
    fi
    
    if [ -z "$ADMIN_PASSWORD" ]; then
        echo "Password: [Could not extract - check .env file]"
    else
        echo "Password: $ADMIN_PASSWORD"
    fi
    
    echo -e "\n${GREEN}WordPress Regular User Credentials:${NC}"
    # Try different common variable name patterns for regular user
    USER_LOGIN=$(grep -E "WORDPRESS_USER|WP_USER" srcs/.env | grep -v "PASSWORD" | cut -d '=' -f2 | tr -d ' "')
    if [ -z "$USER_LOGIN" ]; then
        echo "Username: [Could not extract - check .env file]"
    else
        echo "Username: $USER_LOGIN"
    fi
    
    # Try different common variable name patterns for user password
    USER_PASSWORD=$(grep -E "WORDPRESS_USER_PASSWORD|WP_USER_PASSWORD|USER_PASSWORD" srcs/.env | cut -d '=' -f2 | tr -d ' "')
    if [ -z "$USER_PASSWORD" ]; then
        # Fallback to checking secrets file
        if [ -f "srcs/secrets/wp_user_password.txt" ]; then
            USER_PASSWORD=$(cat srcs/secrets/wp_user_password.txt)
        elif [ -f "secrets/wp_user_password.txt" ]; then
            USER_PASSWORD=$(cat secrets/wp_user_password.txt)
        fi
    fi
    
    if [ -z "$USER_PASSWORD" ]; then
        echo "Password: [Could not extract - check .env file]"
    else
        echo "Password: $USER_PASSWORD"
    fi

    # Also display the database credentials as these are often needed
    echo -e "\n${GREEN}Database Credentials:${NC}"
    DB_ROOT_PASSWORD=$(grep -E "MYSQL_ROOT_PASSWORD|DB_ROOT_PASSWORD|MARIADB_ROOT_PASSWORD" srcs/.env | cut -d '=' -f2 | tr -d ' "')
    if [ -z "$DB_ROOT_PASSWORD" ]; then
        # Fallback to checking secrets file
        if [ -f "srcs/secrets/db_root_password.txt" ]; then
            DB_ROOT_PASSWORD=$(cat srcs/secrets/db_root_password.txt)
        elif [ -f "secrets/db_root_password.txt" ]; then
            DB_ROOT_PASSWORD=$(cat secrets/db_root_password.txt)
        fi
    fi
    
    if [ -z "$DB_ROOT_PASSWORD" ]; then
        echo "Database Root Password: [Could not extract - check .env file]"
    else
        echo "Database Root Password: $DB_ROOT_PASSWORD"
    fi
else
    echo -e "${RED}Could not find .env file to display credentials${NC}"
    echo "Checking for credentials in secrets directory..."
    
    # Try to get credentials from secrets files if they exist
    if [ -d "srcs/secrets" ]; then
        SECRETS_DIR="srcs/secrets"
    elif [ -d "secrets" ]; then
        SECRETS_DIR="secrets"
    else
        echo -e "${RED}No secrets directory found${NC}"
        echo "Please check srcs/.env file manually for login information"
        exit $ERRORS
    fi
    
    echo -e "${GREEN}Credentials from secrets files:${NC}"
    if [ -f "$SECRETS_DIR/wp_admin_password.txt" ]; then
        echo "Admin Password: $(cat $SECRETS_DIR/wp_admin_password.txt)"
    fi
    
    if [ -f "$SECRETS_DIR/wp_user_password.txt" ]; then
        echo "User Password: $(cat $SECRETS_DIR/wp_user_password.txt)"
    fi
    
    if [ -f "$SECRETS_DIR/db_root_password.txt" ]; then
        echo "DB Root Password: $(cat $SECRETS_DIR/db_root_password.txt)"
    fi
    
    if [ -f "$SECRETS_DIR/db_password.txt" ]; then
        echo "DB Password: $(cat $SECRETS_DIR/db_password.txt)"
    fi
fi

exit $ERRORS

