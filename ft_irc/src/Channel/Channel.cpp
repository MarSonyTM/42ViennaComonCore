#include "../../include/Channel.hpp"
#include "../../include/Client.hpp"

Channel::Channel(const std::string& name)
    : _name(name), _invite_only(false), _topic_restricted(false), _user_limit(0) {
}

Channel::~Channel() {
    // Remove all clients from the channel
    _clients.clear();
    _operators.clear();
}

// Getters
const std::string& Channel::getName() const {
    return _name;
}

const std::string& Channel::getTopic() const {
    return _topic;
}

const std::string& Channel::getPassword() const {
    return _password;
}

const std::vector<Client*>& Channel::getClients() const {
    return _clients;
}

const std::vector<Client*>& Channel::getOperators() const {
    return _operators;
}

bool Channel::isInviteOnly() const {
    return _invite_only;
}

bool Channel::isTopicRestricted() const {
    return _topic_restricted;
}

size_t Channel::getUserLimit() const {
    return _user_limit;
}

// Setters
void Channel::setTopic(const std::string& topic) {
    _topic = topic;
}

void Channel::setPassword(const std::string& password) {
    _password = password;
}

void Channel::setInviteOnly(bool status) {
    _invite_only = status;
}

void Channel::setTopicRestricted(bool status) {
    _topic_restricted = status;
}

void Channel::setUserLimit(size_t limit) {
    _user_limit = limit;
}

// Client operations
void Channel::addClient(Client* client) {
    if (!client || hasClient(client))
        return;
    
    _clients.push_back(client);
    client->joinChannel(this);
}

void Channel::removeClient(Client* client) {
    if (!client)
        return;
    
    // Remove from clients list
    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (*it == client) {
            _clients.erase(it);
            break;
        }
    }

    // Remove from operators list if present
    removeOperator(client);
}

bool Channel::hasClient(const Client* client) const {
    if (!client)
        return false;
    
    for (std::vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (*it == client)
            return true;
    }
    return false;
}

void Channel::addOperator(Client* client) {
    if (!client || !hasClient(client) || isOperator(client))
        return;
    
    _operators.push_back(client);
}

void Channel::removeOperator(Client* client) {
    if (!client)
        return;
    
    for (std::vector<Client*>::iterator it = _operators.begin(); it != _operators.end(); ++it) {
        if (*it == client) {
            _operators.erase(it);
            break;
        }
    }
}

bool Channel::isOperator(const Client* client) const {
    if (!client)
        return false;
    
    for (std::vector<Client*>::const_iterator it = _operators.begin(); it != _operators.end(); ++it) {
        if (*it == client)
            return true;
    }
    return false;
}

// Message broadcasting
void Channel::broadcast(const std::string& message, Client* exclude) {
    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (*it != exclude) {
            send((*it)->getFd(), message.c_str(), message.length(), 0);
        }
    }
}