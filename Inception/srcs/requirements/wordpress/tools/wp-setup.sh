#!/bin/sh

# Wait for MariaDB to be ready
while ! nc -z mariadb 3306; do
    echo "Waiting for MariaDB to be ready..."
    sleep 2
done

# Download and install WP-CLI
if [ ! -f "/usr/local/bin/wp" ]; then
    curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
    chmod +x wp-cli.phar
    mv wp-cli.phar /usr/local/bin/wp
fi

# Install WordPress if not already installed
if [ ! -f wp-config.php ]; then
    # Download WordPress core
    wp core download --allow-root

    # Create wp-config.php
    wp config create \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="$(cat /run/secrets/db_password)" \
        --dbhost=mariadb \
        --allow-root

    # Install WordPress
    wp core install \
        --url="https://${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="$(head -n 1 /run/secrets/credentials)" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --allow-root

    # Create additional user
    wp user create \
        "${WP_USER}" "${WP_USER_EMAIL}" \
        --role=author \
        --user_pass="$(tail -n 1 /run/secrets/credentials)" \
        --allow-root

    # Configure Redis
    wp config set WP_CACHE true --allow-root
    wp config set WP_CACHE_KEY_SALT "${DOMAIN_NAME}" --allow-root
    
    # Add Redis configuration to wp-config.php
    wp config set WP_REDIS_HOST redis --allow-root
    wp config set WP_REDIS_PORT 6379 --allow-root
    wp config set WP_REDIS_TIMEOUT 1 --allow-root
    wp config set WP_REDIS_READ_TIMEOUT 1 --allow-root
    wp config set WP_REDIS_DATABASE 0 --allow-root

    # Install and activate Redis Cache plugin
    wp plugin install redis-cache --activate --allow-root
    
    # Enable Redis object cache
    wp redis enable --allow-root
fi

# Set correct permissions
chown -R nobody:nobody /var/www/html

# Start PHP-FPM
exec php-fpm81 -F 