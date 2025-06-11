#include "../../include/Channel.hpp"
#include "../../include/Client.hpp"
#include "../../include/Logger.hpp"

Channel::Channel(const std::string& name)
    : _name(name), _topic(""), _invite_only(false), _topic_restricted(false), _user_limit(0) {
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

void Channel::setInviteOnly(bool invite_only) {
    _invite_only = invite_only;
}

void Channel::setTopicRestricted(bool status) {
    _topic_restricted = status;
}

void Channel::setUserLimit(size_t limit) {
    _user_limit = limit;
}

// Client operations
void Channel::addClient(Client* client) {
    if (!hasClient(client)) {
        _clients.push_back(client);
        Logger::debug("Added client " + client->getNickname() + " to channel " + _name);
    }
}

void Channel::removeClient(Client* client) {
    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (*it == client) {
            _clients.erase(it);
            Logger::debug("Removed client " + client->getNickname() + " from channel " + _name);
            break;
        }
    }
    removeOperator(client);
    removeInvite(client);
}

bool Channel::hasClient(Client* client) const {
    for (std::vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (*it == client)
            return true;
    }
    return false;
}

void Channel::addOperator(Client* client) {
    if (!isOperator(client)) {
        _operators.push_back(client);
        Logger::debug("Added operator " + client->getNickname() + " to channel " + _name);
    }
}

void Channel::removeOperator(Client* client) {
    for (std::vector<Client*>::iterator it = _operators.begin(); it != _operators.end(); ++it) {
        if (*it == client) {
            _operators.erase(it);
            Logger::debug("Removed operator " + client->getNickname() + " from channel " + _name);
            break;
        }
    }
}

bool Channel::isOperator(Client* client) const {
    for (std::vector<Client*>::const_iterator it = _operators.begin(); it != _operators.end(); ++it) {
        if (*it == client)
            return true;
    }
    return false;
}

// Invite management
void Channel::inviteClient(Client* client) {
    if (!isInvited(client)) {
        _invited_clients.push_back(client);
        Logger::debug("Invited client " + client->getNickname() + " to channel " + _name);
    }
}

void Channel::removeInvite(Client* client) {
    for (std::vector<Client*>::iterator it = _invited_clients.begin(); it != _invited_clients.end(); ++it) {
        if (*it == client) {
            _invited_clients.erase(it);
            Logger::debug("Removed invite for client " + client->getNickname() + " from channel " + _name);
            break;
        }
    }
}

bool Channel::isInvited(Client* client) const {
    for (std::vector<Client*>::const_iterator it = _invited_clients.begin(); it != _invited_clients.end(); ++it) {
        if (*it == client)
            return true;
    }
    return false;
}

// Message broadcasting
void Channel::broadcast(const std::string& message, Client* exclude) {
    // Send to all clients in the channel, including the sender unless excluded
    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (*it != exclude) {
            send((*it)->getFd(), message.c_str(), message.length(), 0);
        }
    }
    // If the sender is excluded, send to them too (for their own messages)
    if (exclude && hasClient(exclude)) {
        send(exclude->getFd(), message.c_str(), message.length(), 0);
    }
}