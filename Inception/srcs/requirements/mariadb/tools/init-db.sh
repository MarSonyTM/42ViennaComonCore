#!/bin/sh

# Initialize MySQL data directory if it's empty
if [ ! -d "/var/lib/mysql/mysql" ]; then
    # Initialize MySQL data directory
    mysql_install_db --user=mysql --datadir=/var/lib/mysql > /dev/null
fi

# Start MariaDB server
/usr/bin/mysqld --user=mysql --datadir=/var/lib/mysql &

# Wait for MariaDB to be ready
until mysqladmin ping -h "localhost" --silent; do
    sleep 1
done

# Check if WordPress database exists
if ! mysql -u root -e "USE ${MYSQL_DATABASE}" 2>/dev/null; then
    # Configure MariaDB
    mysql -u root << EOF
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

# Stop the temporary MariaDB server
mysqladmin -u root shutdown

# Start MariaDB server in the foreground
exec mysqld --user=mysql --console 