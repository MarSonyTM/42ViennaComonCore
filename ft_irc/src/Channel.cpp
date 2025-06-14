Channel::Channel(const std::string& name) : _name(name), _inviteOnly(false), _topicRestricted(false), _userLimit(0) {}

bool Channel::isTopicRestricted() const {
    return _topicRestricted;
}

void Channel::setTopicRestricted(bool restricted) {
    _topicRestricted = restricted;
}

void Channel::setTopic(const std::string& topic, Client* client) {
    if (_topicRestricted && !isOperator(client)) {
        // Send error message to client
        std::string error = ":";
        error += _server->getHostname();
        error += " 482 ";
        error += client->getNickname();
        error += " ";
        error += _name;
        error += " :You're not channel operator\r\n";
        client->sendMessage(error);
        return;
    }
    _topic = topic;
    _topicSetter = client->getNickname();
    _topicTime = time(NULL);
    
    // Broadcast topic change to channel
    std::string topicMsg = ":";
    topicMsg += client->getNickname();
    topicMsg += "!~";
    topicMsg += client->getUsername();
    topicMsg += "@";
    topicMsg += client->getHostname();
    topicMsg += " TOPIC ";
    topicMsg += _name;
    topicMsg += " :";
    topicMsg += topic;
    topicMsg += "\r\n";
    broadcast(topicMsg);
} 