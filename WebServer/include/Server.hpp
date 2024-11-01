#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

class Server {
private:
    int _server_socket;
    int _port;
    std::string _host;
    std::string _root_dir;
    size_t _client_max_body_size;
    std::map<int, std::string> _error_pages;
    std::vector<struct pollfd> _poll_fds;
    std::map<int, std::string> _client_buffers;
    
    void setNonBlocking(int socket);
    void handleNewConnection();
    void handleClientData(int client_fd);
    void removeClient(int client_fd);

    std::string getContentType(const std::string& path);
    std::string readFile(const std::string& path);
    bool fileExists(const std::string& path);
    std::string buildResponse(int status_code, const std::string& content_type, 
                            const std::string& content);
    std::string generateDirectoryListing(const std::string& path);

    std::string handleGET(const std::string& path);
    std::string handlePOST(const std::string& path, const std::string& body);
    std::string handleDELETE(const std::string& path);

    bool handleFileUpload(const std::string& content_type, 
                         const std::string& body,
                         const std::string& upload_dir);
    std::string extractBoundary(const std::string& content_type);
    std::string parseMultipartFormData(const std::string& body, 
                                     const std::string& boundary);

    bool isCGI(const std::string& path);
    std::string executeCGI(const std::string& path, 
                          const std::string& method,
                          const std::string& query_string,
                          const std::string& body);
    void setupCGIEnv(const std::string& method,
                    const std::string& query_string,
                    const std::string& content_length);
    std::string getCGIExecutable(const std::string& path);

    std::string getErrorPage(int status_code);
    std::string buildErrorResponse(int status_code);

public:
    Server(const std::string& host, int port, const std::string& root = "./www",
           size_t max_body_size = 1024 * 1024);
    ~Server();

    void setErrorPage(int status_code, const std::string& path);
    void setMaxBodySize(size_t size);
    void start();
    void stop();
};

#endif 