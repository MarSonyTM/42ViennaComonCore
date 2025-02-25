#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}Welcome to Inception Project Setup${NC}"
echo "This script will help you create your .env file"
echo

# Get absolute paths
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
ROOT_SECRETS_DIR="${SCRIPT_DIR}/../secrets"
mkdir -p "$ROOT_SECRETS_DIR"

# Get username and set paths
USERNAME=$(whoami)
if [[ "$(uname)" == "Darwin" ]]; then
    DATA_PATH="/Users/${USERNAME}/data"
else
    DATA_PATH="/home/${USERNAME}/data"
fi

# Generate random passwords and save them to files
ROOT_PWD=$(openssl rand -base64 32 | tr -d '/+=' | cut -c1-16)
WP_DB_PWD=$(openssl rand -base64 32 | tr -d '/+=' | cut -c1-16)
WP_ADMIN_PWD=$(openssl rand -base64 32 | tr -d '/+=' | cut -c1-16)
WP_USER_PWD=$(openssl rand -base64 32 | tr -d '/+=' | cut -c1-16)

# Save passwords to secret files
echo "$ROOT_PWD" > "$ROOT_SECRETS_DIR/db_root_password.txt"
echo "$WP_DB_PWD" > "$ROOT_SECRETS_DIR/db_password.txt"
echo "$WP_ADMIN_PWD" > "$ROOT_SECRETS_DIR/wp_admin_password.txt"
echo "$WP_USER_PWD" > "$ROOT_SECRETS_DIR/wp_user_password.txt"
echo "WP_ADMIN_USER: manager / WP_ADMIN_PASSWORD: $WP_ADMIN_PWD
WP_USER: your_wp_user / WP_USER_PASSWORD: $WP_USER_PWD" > "$ROOT_SECRETS_DIR/credentials.txt"

# Get domain name
DOMAIN="${USERNAME}.42.fr"

# Create new .env file from template
cp .env.example .env

# Update .env file with secure random passwords and paths
sed -i "s|your_root_password_here|$ROOT_PWD|g" .env
sed -i "s|your_wordpress_db_password|$WP_DB_PWD|g" .env
sed -i "s|your_admin_password_here|$WP_ADMIN_PWD|g" .env
sed -i "s|your_wp_user_password|$WP_USER_PWD|g" .env
sed -i "s|mafurnic.42.fr|$DOMAIN|g" .env
sed -i "s|/home/mafurnic/data|$DATA_PATH|g" .env

# Set proper permissions for secrets
chmod 600 "$ROOT_SECRETS_DIR"/*.txt

echo -e "${GREEN}Successfully created .env file with secure random passwords${NC}"
echo -e "${GREEN}Your domain is set to: $DOMAIN${NC}"
echo -e "${GREEN}Data path is set to: $DATA_PATH${NC}"
echo -e "${GREEN}Passwords have been saved to $ROOT_SECRETS_DIR${NC}"
echo -e "${GREEN}You can now run 'make' to start the project${NC}" 