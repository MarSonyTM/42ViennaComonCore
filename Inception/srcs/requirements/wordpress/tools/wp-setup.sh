#!/bin/sh

# Wait for MySQL to be ready
while ! nc -z mariadb 3306; do
    echo "Waiting for MariaDB to be ready..."
    sleep 1
done

# Download and install WP-CLI
if [ ! -f "/usr/local/bin/wp" ]; then
    curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
    chmod +x wp-cli.phar
    mv wp-cli.phar /usr/local/bin/wp
fi

# Download WordPress if not present
if [ ! -f "wp-config.php" ]; then
    # Download WordPress core
    wp core download --allow-root

    # Create wp-config.php
    wp config create \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="$(cat $MYSQL_PASSWORD_FILE)" \
        --dbhost="mariadb" \
        --allow-root

    # Install WordPress
    wp core install \
        --url="${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="$(cat $WP_ADMIN_PASSWORD_FILE)" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --allow-root

    # Create additional user
    wp user create \
        "${WP_USER}" \
        "${WP_USER_EMAIL}" \
        --role=author \
        --user_pass="$(cat $WP_USER_PASSWORD_FILE)" \
        --allow-root

    # Update plugins
    wp plugin update --all --allow-root
fi

# Set correct permissions
chown -R nobody:nobody /var/www/html

# Start PHP-FPM
exec php-fpm81 -F 