#include "../include/Server.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <stdexcept>
#include <arpa/inet.h>
#include <sstream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>

Server::Server(const std::string& host, int port, const std::string& root, size_t max_body_size)
    : _server_socket(-1), _port(port), _host(host), _root_dir(root), 
      _client_max_body_size(max_body_size) {
    
    std::cout << "Initializing server on " << host << ":" << port << std::endl;
    
    struct sockaddr_in server_addr;
    
    _server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_socket < 0) {
        throw std::runtime_error("Failed to create socket");
    }
    
    // Set socket options
    int opt = 1;
    if (setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(_server_socket);
        throw std::runtime_error("Failed to set socket options");
    }
    
    // Set non-blocking
    setNonBlocking(_server_socket);
    
    // Setup server address
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(_host.c_str());
    server_addr.sin_port = htons(_port);
    
    if (bind(_server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(_server_socket);
        throw std::runtime_error("Failed to bind socket: " + std::string(strerror(errno)));
    }
    
    if (listen(_server_socket, SOMAXCONN) < 0) {
        close(_server_socket);
        throw std::runtime_error("Failed to listen on socket");
    }
    
    // Add server socket to poll
    struct pollfd pfd;
    pfd.fd = _server_socket;
    pfd.events = POLLIN;
    _poll_fds.push_back(pfd);
    
    std::cout << "Server initialized successfully" << std::endl;
}

Server::~Server() {
    stop();
}

void Server::setNonBlocking(int socket) {
    int flags = fcntl(socket, F_GETFL, 0);
    if (flags == -1) {
        throw std::runtime_error("Failed to get socket flags");
    }
    if (fcntl(socket, F_SETFL, flags | O_NONBLOCK) == -1) {
        throw std::runtime_error("Failed to set non-blocking socket");
    }
}

void Server::handleNewConnection() {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    int client_fd = accept(_server_socket, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        if (errno != EWOULDBLOCK && errno != EAGAIN) {
            std::cerr << "Failed to accept connection: " << strerror(errno) << std::endl;
        }
        return;
    }
    
    std::cout << "New connection accepted: " << client_fd << std::endl;
    
    setNonBlocking(client_fd);
    
    struct pollfd pfd;
    pfd.fd = client_fd;
    pfd.events = POLLIN;
    _poll_fds.push_back(pfd);
    
    _client_buffers[client_fd] = "";
}

std::string Server::getContentType(const std::string& path) {
    // Text files
    if (path.find(".html") != std::string::npos) return "text/html";
    if (path.find(".css") != std::string::npos) return "text/css";
    if (path.find(".js") != std::string::npos) return "application/javascript";
    if (path.find(".txt") != std::string::npos) return "text/plain";
    if (path.find(".json") != std::string::npos) return "application/json";
    
    // Images
    if (path.find(".jpg") != std::string::npos || path.find(".jpeg") != std::string::npos) 
        return "image/jpeg";
    if (path.find(".png") != std::string::npos) return "image/png";
    if (path.find(".gif") != std::string::npos) return "image/gif";
    if (path.find(".svg") != std::string::npos) return "image/svg+xml";
    if (path.find(".ico") != std::string::npos) return "image/x-icon";
    
    // Default
    return "application/octet-stream";
}

bool Server::fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

std::string Server::readFile(const std::string& path) {
    std::ifstream file(path.c_str(), std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string Server::buildResponse(int status_code, const std::string& content_type, 
                                const std::string& content) {
    std::stringstream response;
    response << "HTTP/1.1 " << status_code << " ";
    
    switch (status_code) {
        case 200: response << "OK"; break;
        case 404: response << "Not Found"; break;
        case 405: response << "Method Not Allowed"; break;
        default: response << "Internal Server Error";
    }
    
    response << "\r\n";
    response << "Content-Type: " << content_type << "\r\n";
    response << "Content-Length: " << content.length() << "\r\n";
    response << "\r\n";
    response << content;
    
    return response.str();
}

std::string Server::generateDirectoryListing(const std::string& path) {
    DIR* dir;
    struct dirent* entry;
    std::stringstream html;
    
    html << "<!DOCTYPE html>\n"
         << "<html>\n<head>\n"
         << "<title>Directory Listing: " << path << "</title>\n"
         << "<style>\n"
         << "body { font-family: Arial, sans-serif; margin: 20px; }\n"
         << "a { text-decoration: none; color: #0066cc; }\n"
         << "a:hover { text-decoration: underline; }\n"
         << "</style>\n"
         << "</head>\n<body>\n"
         << "<h1>Directory Listing: " << path << "</h1>\n"
         << "<ul>\n";

    dir = opendir((_root_dir + path).c_str());
    if (dir != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            std::string name = entry->d_name;
            if (name != "." && name != "..") {
                html << "<li><a href=\"" << path 
                     << (path.back() == '/' ? "" : "/") 
                     << name << "\">" << name << "</a></li>\n";
            }
        }
        closedir(dir);
    }

    html << "</ul>\n</body>\n</html>";
    return html.str();
}

bool Server::isCGI(const std::string& path) {
    // Check file extensions for CGI scripts
    return (path.find(".php") != std::string::npos ||
            path.find(".py") != std::string::npos ||
            path.find(".cgi") != std::string::npos);
}

std::string Server::getCGIExecutable(const std::string& path) {
    if (path.find(".py") != std::string::npos) {
        const char* python_paths[] = {
            "/usr/bin/python3",
            "/usr/local/bin/python3",
            "/opt/homebrew/bin/python3"  // For macOS with Homebrew
        };
        
        for (size_t i = 0; i < sizeof(python_paths) / sizeof(python_paths[0]); ++i) {
            if (access(python_paths[i], X_OK) == 0) {
                return python_paths[i];
            }
        }
        throw std::runtime_error("Python3 not found");
    }
    return "";
}

void Server::setupCGIEnv(const std::string& method,
                        const std::string& query_string,
                        const std::string& content_length) {
    setenv("REQUEST_METHOD", method.c_str(), 1);
    setenv("QUERY_STRING", query_string.c_str(), 1);
    setenv("CONTENT_LENGTH", content_length.c_str(), 1);
    setenv("REDIRECT_STATUS", "200", 1);
    setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
    setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
    setenv("SERVER_SOFTWARE", "WebServ/1.0", 1);
}

std::string Server::executeCGI(const std::string& path,
                             const std::string& method,
                             const std::string& query_string,
                             const std::string& body) {
    int input_pipe[2];  // For sending data to CGI
    int output_pipe[2]; // For receiving data from CGI
    
    if (pipe(input_pipe) < 0 || pipe(output_pipe) < 0) {
        throw std::runtime_error("Failed to create pipes");
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        throw std::runtime_error("Fork failed");
    }
    
    if (pid == 0) { // Child process
        close(input_pipe[1]);  // Close write end
        close(output_pipe[0]); // Close read end
        
        // Redirect stdin/stdout
        dup2(input_pipe[0], STDIN_FILENO);
        dup2(output_pipe[1], STDOUT_FILENO);
        
        // Set up environment variables
        setupCGIEnv(method, query_string, std::to_string(body.length()));
        
        // Get CGI executable
        std::string cgi_exec = getCGIExecutable(path);
        if (cgi_exec.empty()) {
            exit(1);
        }
        
        // Create full path string before converting to c_str()
        std::string script_path = _root_dir + path;
        
        // Execute CGI script
        char* const args[] = {
            const_cast<char*>(cgi_exec.c_str()),
            const_cast<char*>(script_path.c_str()),
            NULL
        };
        
        execv(args[0], args);
        exit(1); // If execv fails
    }
    
    // Parent process
    close(input_pipe[0]);  // Close read end
    close(output_pipe[1]); // Close write end
    
    // Send body to CGI script
    write(input_pipe[1], body.c_str(), body.length());
    close(input_pipe[1]);
    
    // Read CGI output
    char buffer[4096];
    std::string output;
    ssize_t bytes_read;
    
    while ((bytes_read = read(output_pipe[0], buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        output += buffer;
    }
    
    close(output_pipe[0]);
    
    // Wait for child process
    int status;
    waitpid(pid, &status, 0);
    
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return output;
    }
    
    throw std::runtime_error("CGI execution failed");
}

std::string Server::handleGET(const std::string& path) {
    if (isCGI(path)) {
        try {
            std::string output = executeCGI(path, "GET", "", "");
            return buildResponse(200, "text/html", output);
        } catch (const std::exception& e) {
            std::cerr << "CGI error: " << e.what() << std::endl;
            return buildResponse(500, "text/html", "<h1>500 Internal Server Error</h1>");
        }
    }
    
    std::string file_path = _root_dir + path;
    if (path == "/") {
        file_path += "index.html";
    }
    
    std::cout << "GET request for: " << file_path << std::endl;
    
    try {
        if (fileExists(file_path)) {
            struct stat path_stat;
            stat(file_path.c_str(), &path_stat);
            
            if (S_ISDIR(path_stat.st_mode)) {
                // Check for index.html in directory
                std::string index_path = file_path + "/index.html";
                if (fileExists(index_path)) {
                    std::string content = readFile(index_path);
                    return buildResponse(200, "text/html", content);
                } else {
                    // Generate directory listing
                    std::string listing = generateDirectoryListing(path);
                    return buildResponse(200, "text/html", listing);
                }
            } else {
                std::string content = readFile(file_path);
                return buildResponse(200, getContentType(file_path), content);
            }
        }
        return buildResponse(404, "text/html", "<h1>404 Not Found</h1>");
    } catch (const std::exception& e) {
        std::cerr << "Error handling GET request: " << e.what() << std::endl;
        return buildResponse(500, "text/html", "<h1>500 Internal Server Error</h1>");
    }
}

std::string Server::handlePOST(const std::string& path, const std::string& body) {
    // Check body size
    if (body.length() > _client_max_body_size) {
        return buildErrorResponse(413); // Request Entity Too Large
    }
    
    if (isCGI(path)) {
        try {
            std::string output = executeCGI(path, "POST", "", body);
            return buildResponse(200, "text/html", output);
        } catch (const std::exception& e) {
            std::cerr << "CGI error: " << e.what() << std::endl;
            return buildErrorResponse(500);
        }
    }
    
    // Extract headers from body
    size_t header_end = body.find("\r\n\r\n");
    if (header_end == std::string::npos) {
        return buildResponse(400, "text/plain", "Bad Request: Missing headers");
    }

    std::string headers = body.substr(0, header_end);
    std::string content_type;

    // Find Content-Type header
    size_t content_type_pos = headers.find("Content-Type: ");
    if (content_type_pos != std::string::npos) {
        size_t content_type_end = headers.find("\r\n", content_type_pos);
        content_type = headers.substr(content_type_pos + 14, 
                                    content_type_end - (content_type_pos + 14));
    }

    // Handle file upload
    if (content_type.find("multipart/form-data") != std::string::npos) {
        std::string result;
        if (handleFileUpload(content_type, body.substr(header_end + 4), "uploads")) {
            result = "File uploaded successfully";
        } else {
            result = "Upload failed";
        }
        return buildResponse(200, "text/plain", result);
    }

    return buildResponse(400, "text/plain", "Bad Request: Unsupported Content-Type");
}

std::string Server::handleDELETE(const std::string& path) {
    std::string file_path = _root_dir + path;
    std::cout << "DELETE request for: " << file_path << std::endl;
    
    try {
        if (!fileExists(file_path)) {
            return buildResponse(404, "text/html", "<h1>404 Not Found</h1>");
        }
        
        struct stat path_stat;
        stat(file_path.c_str(), &path_stat);
        
        if (S_ISDIR(path_stat.st_mode)) {
            return buildResponse(403, "text/html", "<h1>403 Forbidden</h1><p>Cannot delete directories</p>");
        }
        
        if (remove(file_path.c_str()) == 0) {
            return buildResponse(200, "text/plain", "File deleted successfully");
        } else {
            std::cerr << "Failed to delete file: " << strerror(errno) << std::endl;
            return buildResponse(500, "text/html", "<h1>500 Internal Server Error</h1>");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error handling DELETE request: " << e.what() << std::endl;
        return buildResponse(500, "text/html", "<h1>500 Internal Server Error</h1>");
    }
}

void Server::handleClientData(int client_fd) {
    char buffer[4096];
    ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_read <= 0) {
        if (bytes_read == 0) {
            std::cout << "Client disconnected" << std::endl;
        } else if (errno != EWOULDBLOCK && errno != EAGAIN) {
            std::cerr << "Error reading from client: " << strerror(errno) << std::endl;
        }
        removeClient(client_fd);
        return;
    }
    
    buffer[bytes_read] = '\0';
    _client_buffers[client_fd] += buffer;
    
    // Parse the HTTP request
    std::istringstream request_stream(_client_buffers[client_fd]);
    std::string request_line;
    std::getline(request_stream, request_line);
    
    std::istringstream request_line_stream(request_line);
    std::string method, path, protocol;
    request_line_stream >> method >> path >> protocol;
    
    std::cout << "Received " << method << " request for " << path << std::endl;
    
    std::string response;
    if (method == "GET") {
        response = handleGET(path);
    } else if (method == "POST") {
        response = handlePOST(path, _client_buffers[client_fd]);
    } else if (method == "DELETE") {
        response = handleDELETE(path);
    } else {
        response = buildResponse(405, "text/plain", "Method not supported\n");
    }
    
    ssize_t sent = send(client_fd, response.c_str(), response.length(), 0);
    if (sent < 0) {
        std::cerr << "Error sending response: " << strerror(errno) << std::endl;
    } else {
        std::cout << "Sent " << sent << " bytes response" << std::endl;
    }
    
    removeClient(client_fd);
}

void Server::removeClient(int client_fd) {
    close(client_fd);
    _client_buffers.erase(client_fd);
    
    for (size_t i = 0; i < _poll_fds.size(); ++i) {
        if (_poll_fds[i].fd == client_fd) {
            _poll_fds.erase(_poll_fds.begin() + i);
            break;
        }
    }
}

void Server::start() {
    std::cout << "Server starting..." << std::endl;
    while (true) {
        int ready = poll(&_poll_fds[0], _poll_fds.size(), -1);
        if (ready < 0) {
            if (errno == EINTR) continue;
            throw std::runtime_error("Poll failed");
        }
        
        for (size_t i = 0; i < _poll_fds.size(); ++i) {
            if (_poll_fds[i].revents & POLLIN) {
                if (_poll_fds[i].fd == _server_socket) {
                    handleNewConnection();
                } else {
                    handleClientData(_poll_fds[i].fd);
                }
            }
        }
    }
}

void Server::stop() {
    for (size_t i = 1; i < _poll_fds.size(); ++i) {
        close(_poll_fds[i].fd);
    }
    if (_server_socket >= 0) {
        close(_server_socket);
    }
    _poll_fds.clear();
    _client_buffers.clear();
}

// Add these methods after the existing ones

std::string Server::extractBoundary(const std::string& content_type) {
    size_t pos = content_type.find("boundary=");
    if (pos == std::string::npos) {
        return "";
    }
    return content_type.substr(pos + 9); // 9 is length of "boundary="
}

bool Server::handleFileUpload(const std::string& content_type, 
                            const std::string& body,
                            const std::string& upload_dir) {
    std::cout << "Starting file upload..." << std::endl;
    std::cout << "Content-Type: " << content_type << std::endl;
    
    std::string boundary = extractBoundary(content_type);
    if (boundary.empty()) {
        std::cerr << "No boundary found in content type" << std::endl;
        return false;
    }
    std::cout << "Boundary: " << boundary << std::endl;

    // Create upload directory if it doesn't exist
    std::string dir = _root_dir + "/" + upload_dir;
    std::cout << "Upload directory: " << dir << std::endl;
    
    if (mkdir(dir.c_str(), 0755) == 0) {
        std::cout << "Created upload directory" << std::endl;
    } else if (errno != EEXIST) {
        std::cerr << "Failed to create upload directory: " << strerror(errno) << std::endl;
        return false;
    }

    std::string result = parseMultipartFormData(body, boundary);
    std::cout << "Upload result: " << result << std::endl;
    
    return !result.empty() && result.find("successfully") != std::string::npos;
}

std::string Server::parseMultipartFormData(const std::string& body, 
                                         const std::string& boundary) {
    std::string delimiter = "--" + boundary;
    size_t pos = 0;
    std::string filename;
    std::string content;

    while ((pos = body.find(delimiter, pos)) != std::string::npos) {
        size_t header_start = body.find("\r\n", pos) + 2;
        size_t header_end = body.find("\r\n\r\n", header_start);
        
        if (header_end == std::string::npos) break;

        // Parse headers
        std::string headers = body.substr(header_start, header_end - header_start);
        size_t filename_pos = headers.find("filename=\"");
        if (filename_pos != std::string::npos) {
            filename_pos += 10; // Length of 'filename="'
            size_t filename_end = headers.find("\"", filename_pos);
            filename = headers.substr(filename_pos, filename_end - filename_pos);
        }

        // Get content
        size_t content_start = header_end + 4; // Skip \r\n\r\n
        size_t content_end = body.find(delimiter, content_start) - 2; // Skip \r\n
        if (content_end == std::string::npos) break;

        content = body.substr(content_start, content_end - content_start);

        // Save file if we have a filename
        if (!filename.empty()) {
            std::string filepath = _root_dir + "/uploads/" + filename;
            std::ofstream file(filepath.c_str(), std::ios::binary);
            if (file.is_open()) {
                file.write(content.c_str(), content.length());
                file.close();
                return "File uploaded successfully: " + filename;
            }
        }

        pos = content_end + 2;
    }

    return "No file uploaded";
}

// Add new methods for error pages and body size limits
void Server::setErrorPage(int status_code, const std::string& path) {
    _error_pages[status_code] = path;
}

void Server::setMaxBodySize(size_t size) {
    _client_max_body_size = size;
}

std::string Server::getErrorPage(int status_code) {
    if (_error_pages.find(status_code) != _error_pages.end()) {
        std::string error_path = _root_dir + _error_pages[status_code];
        if (fileExists(error_path)) {
            return readFile(error_path);
        }
    }
    
    // Default error pages
    switch (status_code) {
        case 400:
            return "<h1>400 Bad Request</h1>";
        case 403:
            return "<h1>403 Forbidden</h1>";
        case 404:
            return "<h1>404 Not Found</h1>";
        case 405:
            return "<h1>405 Method Not Allowed</h1>";
        case 413:
            return "<h1>413 Request Entity Too Large</h1>";
        case 500:
            return "<h1>500 Internal Server Error</h1>";
        default:
            return "<h1>" + std::to_string(status_code) + " Error</h1>";
    }
}

std::string Server::buildErrorResponse(int status_code) {
    std::string content = getErrorPage(status_code);
    return buildResponse(status_code, "text/html", content);
}

// ... Rest of the implementation 