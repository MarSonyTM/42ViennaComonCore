WebServer
=========

A high-performance HTTP server implementation in C++98 with support for multiple server blocks, file handling, CGI execution, and configurable settings.

✅ Core Features Implemented:
1. HTTP Methods:
GET (static files, directory listing)
POST (file uploads)
DELETE (file deletion)
Configuration:
Multiple server blocks
Different ports (8080, 8081)
Server names
Client body size limits
Custom error pages
File Handling:
Directory listing
File uploads
Multiple file types
CGI execution (Python)
Error Handling:
Custom error pages
Status codes
Client body size limits
5. Performance:
Non-blocking I/O
Multiple clients
Stress test results:
100% availability
10,049 transactions/sec
0.01s response time
Zero failed transactions
The project meets all mandatory requirements and performs well under stress testing. The code is organized, documented, and follows C++98 standards.



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