#include "../../include/Client.hpp"
#include "../../include/Channel.hpp"
#include "../../include/Logger.hpp"
#include <sys/socket.h>
#include <unistd.h>

Client::Client(int fd)
    : _fd(fd), _authenticated(false), _registered(false) {
}

Client::~Client() {
    // Leave all channels
    for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        (*it)->removeClient(this);
    }
    _channels.clear();
}

// Getters
int Client::getFd() const {
    return _fd;
}

const std::string& Client::getNickname() const {
    return _nickname;
}

const std::string& Client::getUsername() const {
    return _username;
}

const std::string& Client::getRealname() const {
    return _realname;
}

bool Client::isAuthenticated() const {
    return _authenticated;
}

bool Client::isRegistered() const {
    return _registered;
}

DynamicBuffer& Client::getBuffer() {
    return _buffer;
}

const std::vector<Channel*>& Client::getChannels() const {
    return _channels;
}

const std::string& Client::getHostname() const {
    return _hostname;
}

// Setters
void Client::setNickname(const std::string& nickname) {
    _nickname = nickname;
}

void Client::setUsername(const std::string& username) {
    _username = username;
}

void Client::setRealname(const std::string& realname) {
    _realname = realname;
}

void Client::setAuthenticated(bool status) {
    _authenticated = status;
}

void Client::setRegistered(bool status) {
    _registered = status;
}

void Client::setHostname(const std::string& hostname) {
    _hostname = hostname;
}

// Channel operations
void Client::joinChannel(Channel* channel) {
    if (!channel || isInChannel(channel))
        return;
    _channels.push_back(channel);
}

void Client::leaveChannel(Channel* channel) {
    if (!channel)
        return;
    
    for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (*it == channel) {
            _channels.erase(it);
            break;
        }
    }
}

bool Client::isInChannel(const Channel* channel) const {
    if (!channel)
        return false;
    
    for (std::vector<Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (*it == channel)
            return true;
    }
    return false;
}

// Message handling
bool Client::appendToBuffer(const char* data, size_t len) {
    return _buffer.append(data, len);
}

void Client::sendMessage(const std::string& message) {
    std::string full_message = message + "\r\n";
    send(_fd, full_message.c_str(), full_message.length(), 0);
} 