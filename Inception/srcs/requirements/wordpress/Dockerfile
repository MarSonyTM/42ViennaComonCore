# Use Alpine Linux 3.17 (penultimate stable version)
FROM alpine:3.17

# Install required packages
RUN apk update && apk add --no-cache \
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
    php81-phar \
    curl \
    netcat-openbsd \
    && mkdir -p /var/www/html

# Configure PHP-FPM
COPY ./conf/www.conf /etc/php81/php-fpm.d/
COPY ./tools/wp-setup.sh /usr/local/bin/

# Make the setup script executable
RUN chmod +x /usr/local/bin/wp-setup.sh

# Set working directory
WORKDIR /var/www/html

# Expose port 9000 for PHP-FPM
EXPOSE 9000

# Set entrypoint
ENTRYPOINT ["/usr/local/bin/wp-setup.sh"]
