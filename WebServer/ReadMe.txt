WebServer
=========

A high-performance HTTP server implementation in C++98 with support for multiple server blocks, file handling, CGI execution, and configurable settings.

Features
--------

1. HTTP Methods Support:
   - GET: Serve static files and directory listings
   - POST: Handle file uploads and form submissions
   - DELETE: Remove files from the server

2. Configuration:
   - Multiple server blocks with different settings
   - Configurable ports and host addresses
   - Custom error pages (404, 500, etc.)
   - Client body size limits
   - Directory listing options
   - Server name handling

3. File Handling:
   - Static file serving
   - Directory listing
   - Multiple file types support:
     * HTML, CSS, JavaScript
     * Images (PNG, JPG, GIF)
     * Text files
     * JSON files
   - File upload handling
   - Custom upload directories

4. CGI Support:
   - Python CGI script execution
   - Environment variable handling
   - POST/GET method support for CGI
   - Dynamic content generation

5. Error Handling:
   - Custom error pages
   - Status code handling
   - Client body size limits
   - Proper error reporting

Building
--------

1. Clone the repository:
   git clone <repository-url>
   cd WebServer

2. Build the project:
   make

3. Clean build files:
   make clean

4. Rebuild everything:
   make re

Configuration
------------

The server uses a configuration file (default: config/default.conf) with the following structure:

server {
    listen 8080
    server_name localhost
    root www
    client_max_body_size 10M

    error_page 404 /404.html
    error_page 500 /500.html

    location / {
        methods GET POST
        index index.html
        autoindex off
    }

    location /uploads {
        methods POST DELETE
        upload_store uploads
        client_max_body_size 20M
    }
}

Directory Structure
-----------------

WebServer/
├── include/
│   ├── Server.hpp
│   ├── Config.hpp
│   └── Request.hpp
├── src/
│   ├── main.cpp
│   ├── Server.cpp
│   ├── Config.cpp
│   └── Request.cpp
├── www/
│   ├── index.html
│   ├── error/
│   ├── uploads/
│   └── cgi-bin/
├── config/
│   └── default.conf
└── Makefile

Testing
-------

1. Basic GET requests:
   curl -v http://localhost:8080/
   curl -v http://localhost:8080/test.html

2. Directory listing:
   curl -v http://localhost:8080/testdir/

3. File upload:
   curl -v -F "file=@test.txt" http://localhost:8080/uploads/

4. File deletion:
   curl -v -X DELETE http://localhost:8080/uploads/test.txt

5. CGI execution:
   curl -v http://localhost:8080/cgi-bin/test.py

Requirements
-----------

- C++ compiler with C++98 support
- Make
- POSIX-compliant operating system
- Python3 (for CGI support)

Limitations
----------

- HTTP/1.1 only
- No HTTPS support
- Limited CGI support (Python only)
- No virtual host support
- No compression support

Error Codes
----------

- 200: OK
- 400: Bad Request
- 403: Forbidden
- 404: Not Found
- 405: Method Not Allowed
- 413: Request Entity Too Large
- 500: Internal Server Error

Authors
-------

[Marian Furnica]

License
-------

This project is licensed under the Marian Furnica  License.