#!/bin/sh

# Wait for MySQL to be ready for connections
while ! mysqladmin ping -h localhost --silent; do
    sleep 1
done

# Initialize MySQL data directory if it's empty
if [ ! -d "/var/lib/mysql/mysql" ]; then
    # Initialize MySQL data directory
    mysql_install_db --user=mysql --datadir=/var/lib/mysql > /dev/null

    # Start MySQL server in background
    mysqld --user=mysql --bootstrap << EOF
USE mysql;
FLUSH PRIVILEGES;

# Create database
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};

# Create user and grant privileges
CREATE USER '${MYSQL_USER}'@'%' IDENTIFIED BY '$(cat $MYSQL_PASSWORD_FILE)';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';

# Set root password and secure the installation
ALTER USER 'root'@'localhost' IDENTIFIED BY '$(cat $MYSQL_ROOT_PASSWORD_FILE)';
DELETE FROM mysql.user WHERE User='';
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');
DROP DATABASE IF EXISTS test;
DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%';
FLUSH PRIVILEGES;
EOF
fi

# Start MySQL server
exec mysqld --user=mysql 