#!/bin/sh

# Initialize MySQL data directory if it's empty
if [ ! -d "/var/lib/mysql/mysql" ]; then
    # Initialize MySQL data directory
    mysql_install_db --user=mysql --datadir=/var/lib/mysql > /dev/null

    # Start MariaDB server temporarily
    /usr/bin/mysqld --user=mysql --bootstrap << EOF
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '$(cat $MYSQL_ROOT_PASSWORD_FILE)';
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
CREATE USER '${MYSQL_USER}'@'%' IDENTIFIED BY '$(cat $MYSQL_PASSWORD_FILE)';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF
fi

# Start MariaDB server in the foreground
exec mysqld --user=mysql --console 