#include "../../include/common.hpp"
#include "../../include/Client.hpp"
#include "../../include/Channel.hpp"
#include "../../include/Logger.hpp"
#include "../../include/DynamicBuffer.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <algorithm>
#include <cstring>
#include <cerrno>
#include <string>

Client::Client(int fd)
    : _fd(fd), _authenticated(false), _registered(false) {}

Client::~Client() {
    // Leave all channels
    std::vector<Channel*> channels = _channels;  // Create copy to avoid modification during iteration
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
        leaveChannel(*it);
    
    // Close socket
    if (_fd != -1) {
        close(_fd);
        _fd = -1;
    }
}

// Getters
int Client::getFd() const { return _fd; }
const std::string& Client::getNickname() const { return _nickname; }
const std::string& Client::getUsername() const { return _username; }
const std::string& Client::getRealname() const { return _realname; }
const std::string& Client::getHostname() const { return _hostname; }
bool Client::isAuthenticated() const { return _authenticated; }
bool Client::isRegistered() const { return _registered; }
DynamicBuffer& Client::getBuffer() { return _buffer; }
const std::vector<Channel*>& Client::getChannels() const { return _channels; }

// Setters
void Client::setNickname(const std::string& nickname) { _nickname = nickname; }
void Client::setUsername(const std::string& username) { _username = username; }
void Client::setRealname(const std::string& realname) { _realname = realname; }
void Client::setHostname(const std::string& hostname) { _hostname = hostname; }
void Client::setAuthenticated(bool status) { _authenticated = status; }
void Client::setRegistered(bool status) { _registered = status; }

// Channel operations
void Client::joinChannel(Channel* channel) {
    if (!isInChannel(channel)) {
        _channels.push_back(channel);
        Logger::debug("Client " + _nickname + " joined channel " + channel->getName());
    }
}

void Client::leaveChannel(Channel* channel) {
    std::vector<Channel*>::iterator it = std::find(_channels.begin(), _channels.end(), channel);
    if (it != _channels.end()) {
        _channels.erase(it);
        Logger::debug("Client " + _nickname + " left channel " + channel->getName());
    }
}

bool Client::isInChannel(const Channel* channel) const {
    return std::find(_channels.begin(), _channels.end(), channel) != _channels.end();
}

// Message handling
bool Client::appendToBuffer(const char* data, size_t len) {
    return _buffer.append(data, len);
}

void Client::sendMessage(const std::string& message) {
    std::string full_message = message + "\r\n";
    ssize_t bytes_sent = send(_fd, full_message.c_str(), full_message.length(), 0);
    
    if (bytes_sent < 0) {
        Logger::error("Failed to send message to client " + _nickname + ": " + std::string(strerror(errno)));
    } else if (static_cast<size_t>(bytes_sent) < full_message.length()) {
        Logger::warning("Partial message sent to client " + _nickname);
    }
} 