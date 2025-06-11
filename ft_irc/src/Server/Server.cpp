#include "../../include/Server.hpp"
#include "../../include/Client.hpp"
#include "../../include/Channel.hpp"
#include "../../include/Logger.hpp"
#include "../../include/CommandHandler.hpp"

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

bool Server::start() {
    if (!setupSocket())
        return false;

    // Initialize command handler
    _command_handler = new CommandHandler(*this);

    // Initialize poll with server socket
    struct pollfd pfd;
    pfd.fd = _socket_fd;
    pfd.events = POLLIN;
    _poll_fds.push_back(pfd);

    return true;
}

void Server::handleNewConnection() {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    int client_fd = accept(_socket_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        if (errno != EWOULDBLOCK)
            Logger::error("Failed to accept connection: " + std::string(strerror(errno)));
        return;
    }

    // Set client socket to non-blocking
    if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0) {
        Logger::error("Failed to set client socket to non-blocking: " + std::string(strerror(errno)));
        close(client_fd);
        return;
    }

    // Add to poll fds
    struct pollfd pfd;
    pfd.fd = client_fd;
    pfd.events = POLLIN;
    _poll_fds.push_back(pfd);

    // Create client object
    _clients[client_fd] = new Client(client_fd);

    Logger::info("New client connected from " + std::string(inet_ntoa(client_addr.sin_addr)));
}

void Server::handleClientMessage(int client_fd) {
    Client* client = _clients[client_fd];
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read = recv(client_fd, buffer, BUFFER_SIZE, 0);

    if (bytes_read <= 0) {
        if (bytes_read == 0)
            Logger::info("Client disconnected");
        else
            Logger::error("Error reading from client: " + std::string(strerror(errno)));
        
        removeClient(client_fd);
        return;
    }

    buffer[bytes_read] = '\0';
    std::string message = buffer;
    
    // Split received data into lines
    size_t pos = 0;
    std::string line;
    while ((pos = message.find("\r\n")) != std::string::npos || (pos = message.find("\n")) != std::string::npos) {
        line = message.substr(0, pos);
        if (!line.empty()) {
            Logger::debug("Received: " + line);
            _command_handler->handleCommand(client, line);
        }
        message.erase(0, pos + (message[pos] == '\r' ? 2 : 1));
    }

    // Store any remaining partial message in client's buffer
    if (!message.empty()) {
        client->appendToBuffer(message);
    }
}

void Server::removeClient(int client_fd) {
    // Remove from poll fds
    for (std::vector<pollfd>::iterator it = _poll_fds.begin(); it != _poll_fds.end(); ++it) {
        if (it->fd == client_fd) {
            _poll_fds.erase(it);
            break;
        }
    }

    // Delete client object
    delete _clients[client_fd];
    _clients.erase(client_fd);

    // Close socket
    close(client_fd);
}

void Server::run() {
    while (true) {
        int ready = poll(&_poll_fds[0], _poll_fds.size(), -1);
        if (ready < 0) {
            if (errno == EINTR)
                continue;
            Logger::error("Poll failed: " + std::string(strerror(errno)));
            break;
        }

        for (size_t i = 0; i < _poll_fds.size(); ++i) {
            if (_poll_fds[i].revents & POLLIN) {
                if (_poll_fds[i].fd == _socket_fd)
                    handleNewConnection();
                else
                    handleClientMessage(_poll_fds[i].fd);
            }
        }
    }
}

void Server::stop() {
    // Clean up clients
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        close(it->first);
        delete it->second;
    }
    _clients.clear();
    _poll_fds.clear();

    // Clean up channels
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
        delete it->second;
    _channels.clear();

    // Clean up command handler
    delete _command_handler;
    _command_handler = NULL;

    // Close server socket
    if (_socket_fd != -1) {
        close(_socket_fd);
        _socket_fd = -1;
    }
}

const std::string& Server::getPassword() const {
    return _password;
}

const std::map<std::string, Channel*>& Server::getChannels() const {
    return _channels;
}

Client* Server::getClientByNickname(const std::string& nickname) const {
    for (std::map<int, Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->second->getNickname() == nickname)
            return it->second;
    }
    return NULL;
}

Channel* Server::createChannel(const std::string& name) {
    std::map<std::string, Channel*>::iterator it = _channels.find(name);
    if (it != _channels.end())
        return it->second;
    
    Channel* channel = new Channel(name);
    _channels[name] = channel;
    Logger::debug("Created new channel: " + name);
    return channel;
}

Channel* Server::getChannel(const std::string& name) {
    std::map<std::string, Channel*>::iterator it = _channels.find(name);
    return (it != _channels.end()) ? it->second : NULL;
}

void Server::removeChannel(const std::string& name) {
    std::map<std::string, Channel*>::iterator it = _channels.find(name);
    if (it != _channels.end()) {
        delete it->second;
        _channels.erase(it);
        Logger::debug("Removed channel: " + name);
    }
}

void Server::broadcastToChannel(const std::string& channel_name, const std::string& message, Client* exclude) {
    Channel* channel = getChannel(channel_name);
    if (channel)
        channel->broadcast(message, exclude);
} 