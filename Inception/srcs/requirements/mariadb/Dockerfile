# Use Alpine Linux 3.17 (penultimate stable version)
FROM alpine:3.17

# Install MariaDB and required packages
RUN apk update && apk add --no-cache \
    mariadb \
    mariadb-client \
    mariadb-server-utils \
    && mkdir -p /run/mysqld \
    && chown -R mysql:mysql /run/mysqld \
    && chmod 777 /run/mysqld

# Copy configuration and initialization scripts
COPY ./conf/my.cnf /etc/my.cnf.d/
COPY ./tools/init-db.sh /docker-entrypoint-initdb.d/

# Make the initialization script executable
RUN chmod +x /docker-entrypoint-initdb.d/init-db.sh

# Expose MySQL port
EXPOSE 3306

# Set the entrypoint
ENTRYPOINT ["/docker-entrypoint-initdb.d/init-db.sh"]
