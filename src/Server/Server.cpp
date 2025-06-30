#include "../../include/Server.hpp"
#include "../../include/Client.hpp"
#include "../../include/Channel.hpp"
#include "../../include/Logger.hpp"
#include "../../include/CommandHandler.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <fcntl.h>
#include <cerrno>
#include <string>
#include <sstream>

// Define static members
Server* Server::_instance = NULL;
const std::string Server::_hostname = "ft_irc";

// Helper function for number to string conversion
std::string numberToString(size_t number) {
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

Server::Server(int port, const std::string& password)
    : _socket_fd(-1), _port(port), _password(password), _command_handler(NULL) {
}

Server::~Server() {
    stop();
}

bool Server::setupSocket() {
    _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket_fd < 0) {
        Logger::error("Failed to create socket: " + std::string(strerror(errno)));
        return false;
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        Logger::error("Failed to set socket options: " + std::string(strerror(errno)));
        close(_socket_fd);
        return false;
    }

    // Set non-blocking
    if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) < 0) {
        Logger::error("Failed to set non-blocking socket: " + std::string(strerror(errno)));
        close(_socket_fd);
        return false;
    }

    // Bind socket
    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(_port);

    if (bind(_socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        Logger::error("Failed to bind socket: " + std::string(strerror(errno)));
        close(_socket_fd);
        return false;
    }

    // Listen
    if (listen(_socket_fd, 5) < 0) {
        Logger::error("Failed to listen on socket: " + std::string(strerror(errno)));
        close(_socket_fd);
        return false;
    }

    return true;
}

void Server::handleClientMessage(int client_fd) {
    char buffer[1024];
    ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_read <= 0) {
        if (bytes_read == 0) {
            Logger::debug("Client disconnected gracefully");
        } else {
            Logger::debug("Error reading from client: " + std::string(strerror(errno)));
        }
        removeClient(client_fd);
        return;
    }

    Client* client = _clients[client_fd];
    if (!client->appendToBuffer(buffer, bytes_read)) {
        Logger::error("Buffer overflow for client " + client->getNickname());
        removeClient(client_fd);
        return;
    }

    DynamicBuffer& clientBuffer = client->getBuffer();
    while (clientBuffer.hasCompleteLine()) {
        std::string cmd = clientBuffer.getLine();
        if (!cmd.empty()) {
            Logger::debug("Processing command: '" + cmd + "'");
            _command_handler->handleCommand(client, cmd);
        }
    }
}

// ... rest of existing code ... 