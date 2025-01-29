#!/bin/bash

# Detect OS and set paths
OS=$(uname)
if [ "$OS" = "Darwin" ]; then
    # For macOS, we'll use named volumes instead of bind mounts
    DATA_PATH="/Users/$USER/data"
    # Create the directories just for consistency
    mkdir -p "$DATA_PATH/wordpress"
    mkdir -p "$DATA_PATH/mariadb"
    
    # Use named volumes configuration
    cat > srcs/docker-compose.override.yml << EOF
version: '3.8'
volumes:
  wordpress_data:
    name: wordpress_data
  mariadb_data:
    name: mariadb_data
EOF
else
    # For Linux, use bind mounts
    DATA_PATH="/home/$USER/data"
    mkdir -p "$DATA_PATH/wordpress"
    mkdir -p "$DATA_PATH/mariadb"
    
    # Use bind mounts configuration
    cat > srcs/docker-compose.override.yml << EOF
version: '3.8'
volumes:
  wordpress_data:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: ${DATA_PATH}/wordpress
  mariadb_data:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: ${DATA_PATH}/mariadb
EOF
fi

# Clean up any existing Docker resources
echo "Cleaning up existing Docker resources..."
docker compose -f srcs/docker-compose.yml down -v 2>/dev/null
docker system prune -af --volumes 2>/dev/null

# Set fixed domain
DOMAIN="mafurnic.42.fr"

# Update all dynamic values in .env
sed -i.bak \
    -e "s|DOMAIN_NAME=.*|DOMAIN_NAME=$DOMAIN|" \
    -e "s|WP_VOLUME_PATH=.*|WP_VOLUME_PATH=$DATA_PATH/wordpress|" \
    -e "s|DB_VOLUME_PATH=.*|DB_VOLUME_PATH=$DATA_PATH/mariadb|" \
    -e "s|manager@.*\.42\.fr|manager@$DOMAIN|" \
    -e "s|WP_USER=.*|WP_USER=mafurnic|" \
    -e "s|WP_USER_EMAIL=.*|WP_USER_EMAIL=mafurnic@student.42.fr|" \
    -e "s|WP_ADMIN_USER=.*|WP_ADMIN_USER=manager|" \
    srcs/.env

# Clean up backup files (macOS creates these with sed)
rm -f srcs/.env.bak

# Create SSL directory if it doesn't exist
mkdir -p srcs/requirements/nginx/ssl

# Generate SSL certificate with dynamic domain
cat > srcs/requirements/nginx/ssl/ssl_setup.sh << EOF
#!/bin/sh
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \\
    -keyout /etc/nginx/ssl/nginx.key \\
    -out /etc/nginx/ssl/nginx.crt \\
    -subj "/C=AT/ST=Vienna/L=Vienna/O=42School/OU=student/CN=$DOMAIN"
chmod 600 /etc/nginx/ssl/nginx.key
chmod 644 /etc/nginx/ssl/nginx.crt
EOF

chmod +x srcs/requirements/nginx/ssl/ssl_setup.sh

echo "Environment configured for user: $USER"
echo "Domain set to: $DOMAIN"
echo "Data path set to: $DATA_PATH"

# Run make with clean first
make fclean && make 