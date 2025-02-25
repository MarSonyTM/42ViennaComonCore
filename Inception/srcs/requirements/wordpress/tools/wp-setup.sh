#!/bin/sh

# Wait for MariaDB to be ready
while ! nc -z mariadb 3306; do
    echo "Waiting for MariaDB to be ready..."
    sleep 2
done

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

    # Install WordPress with admin user from environment
    wp core install \
        --url="https://${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="$(cat /run/secrets/wp_admin_password)" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --allow-root

    # Create additional user
    wp user create \
        "${WP_USER}" "${WP_USER_EMAIL}" \
        --role=author \
        --user_pass="$(cat /run/secrets/wp_user_password)" \
        --allow-root
fi

# Set correct permissions
chown -R nobody:nobody /var/www/html

# Start PHP-FPM
exec php-fpm81 -F 