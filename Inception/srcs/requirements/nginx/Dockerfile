# Use Alpine Linux 3.17 (penultimate stable version)
FROM alpine:3.17

# Install NGINX and OpenSSL
RUN apk update && apk add --no-cache \
    nginx \
    openssl

# Create SSL directory
RUN mkdir -p /etc/nginx/ssl

# Generate SSL certificate
RUN openssl req -x509 -nodes -days 365 -newkey rsa:4096 \
    -keyout /etc/nginx/ssl/inception.key \
    -out /etc/nginx/ssl/inception.crt \
    -subj "/C=AT/ST=Vienna/L=Vienna/O=42Vienna/CN=mafurnic.42.fr"

# Create directory for nginx pid file
RUN mkdir -p /run/nginx

# Copy nginx configuration
COPY ./conf/nginx.conf /etc/nginx/nginx.conf
COPY ./conf/default.conf /etc/nginx/http.d/default.conf

# Expose port 443
EXPOSE 443

# Start NGINX
CMD ["nginx", "-g", "daemon off;"]
