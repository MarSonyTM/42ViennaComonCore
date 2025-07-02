#include "../../include/Server.hpp"
#include "../../include/Client.hpp"
#include "../../include/Channel.hpp"
#include "../../include/Logger.hpp"
#include "../../include/CommandHandler.hpp"
#include <sstream>

// Define static members
const std::string Server::_hostname = "ft_irc";
Server* Server::_instance = NULL;

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
        Logger::error("Failed to set socket to non-blocking mode: " + std::string(strerror(errno)));
        throw std::runtime_error("Failed to set socket to non-blocking mode");
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
    pfd.revents = 0;  // Initialize revents
    _poll_fds.push_back(pfd);

    return true;
}

void Server::handleNewConnection() {
    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    
    int clientFd = accept(_socket_fd, (struct sockaddr*)&clientAddr, &clientLen);
    if (clientFd < 0) {
        if (errno != EWOULDBLOCK)
            Logger::error("Failed to accept connection: " + std::string(strerror(errno)));
        return;
    }

    // Set socket to non-blocking mode
    if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0) {
        Logger::error("Failed to set client socket to non-blocking mode: " + std::string(strerror(errno)));
        close(clientFd);
        return;
    }

    // Create new client
    Client* newClient = new Client(clientFd);
    
    // Set hostname
    char hostname[NI_MAXHOST];
    if (getnameinfo((struct sockaddr*)&clientAddr, sizeof(clientAddr),
                    hostname, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) == 0) {
        newClient->setHostname(hostname);
    } else {
        newClient->setHostname("unknown");
    }

    // Add to poll fds
    struct pollfd pfd;
    pfd.fd = clientFd;
    pfd.events = POLLIN;
    pfd.revents = 0;  // Initialize revents
    _poll_fds.push_back(pfd);

    _clients[clientFd] = newClient;
    Logger::info("New client connected from " + std::string(hostname));
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
    // First clear the poll_fds vector to ensure proper deallocation
    clearPollFds();

    // Clean up clients
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        close(it->first);
        delete it->second;
    }
    _clients.clear();

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

const std::string& Server::getHostname() const {
    return _hostname;
} 