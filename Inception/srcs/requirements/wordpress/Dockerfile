# Use Alpine Linux 3.17 (penultimate stable version)
FROM alpine:3.17

# Install required packages
RUN apk add --no-cache \
    php81 \
    php81-fpm \
    php81-mysqli \
    php81-json \
    php81-curl \
    php81-dom \
    php81-exif \
    php81-fileinfo \
    php81-mbstring \
    php81-openssl \
    php81-xml \
    php81-zip \
    php81-redis \
    php81-phar \
    curl \
    mariadb-client \
    netcat-openbsd \
    && mkdir -p /var/www/html

# Install wp-cli
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

# Copy configuration and setup script
COPY conf/www.conf /etc/php81/php-fpm.d/www.conf
COPY tools/wp-setup.sh /usr/local/bin/wp-setup.sh
RUN chmod +x /usr/local/bin/wp-setup.sh

# Create directory for PHP-FPM socket and logs
RUN mkdir -p /var/run/php-fpm81 \
    && mkdir -p /var/log/php81

# Set working directory
WORKDIR /var/www/html

# Expose PHP-FPM port
EXPOSE 9000

# Start PHP-FPM with setup script
CMD ["/usr/local/bin/wp-setup.sh"]
