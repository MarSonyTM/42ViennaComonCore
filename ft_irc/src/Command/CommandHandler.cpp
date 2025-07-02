#include "../../include/CommandHandler.hpp"
#include "../../include/Logger.hpp"
#include "../../include/Channel.hpp"
#include <sstream>

CommandHandler::CommandHandler(Server& server) : _server(server) {}

CommandHandler::~CommandHandler() {}

std::vector<std::string> CommandHandler::splitMessage(const std::string& message) {
    std::vector<std::string> tokens;
    std::string cleaned_message;

    // Remove \r and \n manually
    for (std::string::const_iterator it = message.begin(); it != message.end(); ++it) {
        if (*it != '\r' && *it != '\n') {
            cleaned_message += *it;
        }
    }

    Logger::debug("Splitting message: '" + cleaned_message + "'");

    if (cleaned_message.empty()) {
        return tokens;
    }

    // Handle trailing parameter (after :)
    size_t colon_pos = cleaned_message.find(" :");
    if (colon_pos != std::string::npos) {
        // Get the part before the colon
        std::string before_colon = cleaned_message.substr(0, colon_pos);
        // Get the trailing part (including the colon)
        std::string trailing = cleaned_message.substr(colon_pos + 2);

        // Split the part before the colon
        std::istringstream before_iss(before_colon);
        std::string token;
        while (before_iss >> token) {
            tokens.push_back(token);
        }

        // Add the trailing part as a single parameter
        if (!trailing.empty()) {
            tokens.push_back(trailing);
        }
    } else {
        // No trailing parameter, just split by spaces
        std::istringstream iss(cleaned_message);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
    }

    std::string debug_tokens;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (i > 0) debug_tokens += ", ";
        debug_tokens += "'" + tokens[i] + "'";
    }
    Logger::debug("Split into tokens: [" + debug_tokens + "]");

    return tokens;
}

bool CommandHandler::isValidNickname(const std::string& nickname) {
    if (nickname.empty() || nickname.length() > 9)
        return false;

    // First character must be a letter
    if (!isalpha(nickname[0]))
        return false;

    // Rest can be letters, digits, or special characters
    for (std::string::const_iterator it = nickname.begin() + 1; it != nickname.end(); ++it) {
        if (!isalnum(*it) && *it != '-' && *it != '_')
            return false;
    }

    return true;
}

bool CommandHandler::isValidChannelName(const std::string& channel) {
    if (channel.empty() || channel.length() > 50)
        return false;
    
    // Channel names must start with # or &
    if (channel[0] != '#' && channel[0] != '&')
        return false;
    
    // Check for invalid characters
    for (std::string::const_iterator it = channel.begin() + 1; it != channel.end(); ++it) {
        if (*it == ' ' || *it == ',' || *it == ':' || *it == 7)
            return false;
    }
    
    return true;
}

void CommandHandler::sendReply(Client* client, int code, const std::string& message) {
    std::string prefix = ":";
    prefix += SERVER_NAME;
    prefix += " ";
    
    std::ostringstream code_str;
    code_str.width(3);
    code_str.fill('0');
    code_str << code;
    
    std::string reply = prefix + code_str.str() + " " + 
                       (client->getNickname().empty() ? "*" : client->getNickname()) +
                       " " + message + "\r\n";
    
    send(client->getFd(), reply.c_str(), reply.length(), 0);
}

void CommandHandler::handlePass(Client* client, const std::vector<std::string>& params) {
    if (client->isAuthenticated()) {
        sendReply(client, ERR_ALREADYREGISTERED, ":You are already registered");
        return;
    }

    if (params.empty()) {
        sendReply(client, ERR_NEEDMOREPARAMS, "PASS :Not enough parameters");
        return;
    }

    if (params[0] == _server.getPassword()) {
        client->setAuthenticated(true);
        Logger::debug("Client authenticated successfully");
    } else {
        sendReply(client, ERR_PASSWDMISMATCH, ":Password incorrect");
        Logger::debug("Client failed to authenticate: incorrect password");
    }
}

void CommandHandler::handleNick(Client* client, const std::vector<std::string>& params) {
    if (!client->isAuthenticated()) {
        sendReply(client, ERR_NOTREGISTERED, ":You have not registered");
        return;
    }

    if (params.empty()) {
        sendReply(client, ERR_NONICKNAMEGIVEN, ":No nickname given");
        return;
    }

    std::string nickname = params[0];

    if (!isValidNickname(nickname)) {
        sendReply(client, ERR_ERRONEUSNICKNAME, nickname + " :Erroneous nickname");
        return;
    }

    // Check if nickname is already in use
    if (_server.getClientByNickname(nickname)) {
        sendReply(client, ERR_NICKNAMEINUSE, nickname + " :Nickname is already in use");
        return;
    }

    client->setNickname(nickname);
    Logger::debug("Client set nickname to: " + nickname);

    // If the client has both nickname and username set, they are fully registered
    if (!client->getUsername().empty()) {
        client->setRegistered(true);
        sendReply(client, RPL_WELCOME, ":Welcome to the Internet Relay Network " + 
                                     client->getNickname() + "!" + 
                                     client->getUsername() + "@" + SERVER_NAME);
    }
}

void CommandHandler::handleUser(Client* client, const std::vector<std::string>& params) {
    if (!client->isAuthenticated()) {
        sendReply(client, ERR_NOTREGISTERED, ":You have not registered");
        return;
    }

    if (client->isRegistered()) {
        sendReply(client, ERR_ALREADYREGISTERED, ":You may not reregister");
        return;
    }

    if (params.size() < 4) {
        sendReply(client, ERR_NEEDMOREPARAMS, "USER :Not enough parameters");
        return;
    }

    client->setUsername(params[0]);
    client->setRealname(params[3]);
    Logger::debug("Client set username to: " + params[0] + " and realname to: " + params[3]);

    // If the client has both nickname and username set, they are fully registered
    if (!client->getNickname().empty()) {
        client->setRegistered(true);
        sendReply(client, RPL_WELCOME, ":Welcome to the Internet Relay Network " + 
                                     client->getNickname() + "!" + 
                                     client->getUsername() + "@" + SERVER_NAME);
    }
}

void CommandHandler::handleQuit(Client* client, const std::vector<std::string>& params) {
    (void)client; // Silence unused parameter warning
    std::string quit_message = params.empty() ? "Client Quit" : params[0];
    Logger::info("Client quit: " + quit_message);
    // The actual client removal will be handled by the Server class
}

void CommandHandler::handleJoin(Client* client, const std::vector<std::string>& params) {
    if (!client->isRegistered()) {
        sendReply(client, ERR_NOTREGISTERED, ":You have not registered");
        return;
    }

    if (params.empty()) {
        sendReply(client, ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters");
        return;
    }

    std::string channel_name = params[0];
    std::string provided_key = params.size() > 1 ? params[1] : "";
    
    if (!isValidChannelName(channel_name)) {
        sendReply(client, ERR_NOSUCHCHANNEL, channel_name + " :No such channel");
        return;
    }

    Logger::debug("Processing JOIN for " + client->getNickname() + " to channel " + channel_name);

    Channel* channel = _server.getChannel(channel_name);
    if (!channel) {
        Logger::debug("Creating new channel " + channel_name);
        channel = _server.createChannel(channel_name);
        // First user to join becomes operator
        channel->addOperator(client);
        if (!provided_key.empty()) {
            channel->setKey(provided_key);
        }
    } else {
        // Check if user is banned
        if (channel->isBanned(client)) {
            sendReply(client, ERR_BANNEDFROMCHAN, channel_name + " :Cannot join channel (+b) - you are banned");
            return;
        }

        // Check invite-only mode
        if (channel->isInviteOnly() && !channel->isInvited(client)) {
            sendReply(client, ERR_INVITEONLYCHAN, channel_name + " :Cannot join channel (+i) - invite only");
            return;
        }
        
        // Check channel key
        if (channel->hasKey() && (provided_key != channel->getKey())) {
        sendReply(client, ERR_BADCHANNELKEY, channel_name + " :Cannot join channel (+k) - wrong channel key");
        return;
        }

        // Check user limit
        if (channel->getUserLimit() > 0 && channel->getClients().size() >= channel->getUserLimit()) {
            sendReply(client, ERR_CHANNELISFULL, channel_name + " :Cannot join channel (+l) - channel is full");
            return;
        }
    }

    if (channel->hasClient(client)) {
        Logger::debug("Client " + client->getNickname() + " already in channel " + channel_name);
        return; // Already in channel
    }

    // Format: :nick!user@host JOIN #channel
    std::string join_msg = ":";
    join_msg += client->getNickname();
    join_msg += "!";
    join_msg += client->getUsername();
    join_msg += "@";
    join_msg += SERVER_NAME;
    join_msg += " JOIN ";
    join_msg += channel_name;
    join_msg += "\r\n";
    
    // Send join message to all clients in the channel
    channel->broadcast(join_msg);
    
    // Add client to channel
    channel->addClient(client);
    client->joinChannel(channel);
    
    // Send NAMES list
    std::string names_msg = ":";
    names_msg += SERVER_NAME;
    names_msg += " 353 ";
    names_msg += client->getNickname();
    names_msg += " = ";
    names_msg += channel_name;
    names_msg += " :";
    
    std::vector<Client*> clients = channel->getClients();
    for (size_t i = 0; i < clients.size(); ++i) {
        if (i > 0) names_msg += " ";
        if (channel->isOperator(clients[i])) {
            names_msg += "@";
        }
        names_msg += clients[i]->getNickname();
    }
    names_msg += "\r\n";
    send(client->getFd(), names_msg.c_str(), names_msg.length(), 0);
    
    // Send end of NAMES list
    std::string end_names_msg = ":";
    end_names_msg += SERVER_NAME;
    end_names_msg += " 366 ";
    end_names_msg += client->getNickname();
    end_names_msg += " ";
    end_names_msg += channel_name;
    end_names_msg += " :End of NAMES list\r\n";
    send(client->getFd(), end_names_msg.c_str(), end_names_msg.length(), 0);
    
    // If channel has a topic, send it
    if (!channel->getTopic().empty()) {
        std::string topic_msg = ":";
        topic_msg += SERVER_NAME;
        topic_msg += " 332 ";
        topic_msg += client->getNickname();
        topic_msg += " ";
        topic_msg += channel_name;
        topic_msg += " :";
        topic_msg += channel->getTopic();
        topic_msg += "\r\n";
        send(client->getFd(), topic_msg.c_str(), topic_msg.length(), 0);
    }
}

void CommandHandler::handlePart(Client* client, const std::vector<std::string>& params) {
    if (!client->isRegistered()) {
        sendReply(client, ERR_NOTREGISTERED, ":You have not registered");
        return;
    }

    if (params.empty()) {
        sendReply(client, ERR_NEEDMOREPARAMS, "PART :Not enough parameters");
        return;
    }

    std::string channel_name = params[0];
    Channel* channel = _server.getChannel(channel_name);
    
    if (!channel) {
        sendReply(client, ERR_NOSUCHCHANNEL, channel_name + " :No such channel");
        return;
    }

    if (!channel->hasClient(client)) {
        sendReply(client, ERR_NOTONCHANNEL, channel_name + " :You're not on that channel");
        return;
    }

    std::string part_msg = ":" + client->getNickname() + "!" + client->getUsername() + "@" + SERVER_NAME + 
                          " PART " + channel_name;
    if (params.size() > 1)
        part_msg += " :" + params[1];
    part_msg += "\r\n";
    
    channel->broadcast(part_msg);
    channel->removeClient(client);

    // If channel is empty, remove it
    if (channel->getClients().empty())
        _server.removeChannel(channel_name);
}

void CommandHandler::handlePrivmsg(Client* client, const std::vector<std::string>& params) {
    if (!client->isRegistered()) {
        sendReply(client, ERR_NOTREGISTERED, ":You have not registered");
        return;
    }

    if (params.empty()) {
        sendReply(client, ERR_NEEDMOREPARAMS, "PRIVMSG :Not enough parameters");
        return;
    }

    if (params.size() < 2) {
        // No message provided
        return;
    }

    std::string target = params[0];
    std::string message = params[1];

    if (target[0] == '#' || target[0] == '&') {
        // Channel message
        Channel* channel = _server.getChannel(target);
        if (!channel) {
            sendReply(client, ERR_NOSUCHCHANNEL, target + " :No such channel");
            return;
        }

        if (!channel->hasClient(client)) {
            sendReply(client, ERR_CANNOTSENDTOCHAN, target + " :Cannot send to channel");
            return;
        }

        std::string msg = ":" + client->getNickname() + "!" + client->getUsername() + "@" + SERVER_NAME + 
                         " PRIVMSG " + target + " :" + message + "\r\n";
        channel->broadcast(msg, client); // Don't send to sender
    } else {
        // Private message to user
        Client* target_client = _server.getClientByNickname(target);
        if (!target_client) {
            sendReply(client, ERR_NOSUCHNICK, target + " :No such nick/channel");
            return;
        }

        std::string msg = ":" + client->getNickname() + "!" + client->getUsername() + "@" + SERVER_NAME + 
                         " PRIVMSG " + target + " :" + message + "\r\n";
        send(target_client->getFd(), msg.c_str(), msg.length(), 0);
    }
}

void CommandHandler::handleNames(Client* client, const std::vector<std::string>& params) {
    if (!client->isRegistered()) {
        sendReply(client, ERR_NOTREGISTERED, ":You have not registered");
        return;
    }

    if (params.empty()) {
        sendReply(client, ERR_NEEDMOREPARAMS, "NAMES :Not enough parameters");
        return;
    }

    std::string channel_name = params[0];
    Channel* channel = _server.getChannel(channel_name);
    
    if (!channel) {
        sendReply(client, ERR_NOSUCHCHANNEL, channel_name + " :No such channel");
        return;
    }

    // Build names list
    std::string names_list;
    const std::vector<Client*>& clients = channel->getClients();
    const std::vector<Client*>& operators = channel->getOperators();

    for (std::vector<Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it != clients.begin())
            names_list += " ";
        
        // Add @ prefix for operators
        bool is_operator = false;
        for (std::vector<Client*>::const_iterator op_it = operators.begin(); op_it != operators.end(); ++op_it) {
            if (*op_it == *it) {
                is_operator = true;
                break;
            }
        }
        
        names_list += (is_operator ? "@" : "") + (*it)->getNickname();
    }

    // Send names reply using proper numeric code
    std::ostringstream code_str;
    code_str.width(3);
    code_str.fill('0');
    code_str << RPL_NAMREPLY;
    
    std::string reply = ":" + std::string(SERVER_NAME) + " " + code_str.str() + " " +
                       client->getNickname() + " = " + channel_name + " :" + names_list + "\r\n";
    send(client->getFd(), reply.c_str(), reply.length(), 0);

    // Send end of names
    sendReply(client, RPL_ENDOFNAMES, channel_name + " :End of NAMES list");
}

void CommandHandler::handleKick(Client* client, const std::vector<std::string>& params) {
    if (!client->isRegistered()) {
        sendReply(client, ERR_NOTREGISTERED, ":You have not registered");
        return;
    }

    if (params.size() < 2) {
        sendReply(client, ERR_NEEDMOREPARAMS, "KICK :Not enough parameters");
        return;
    }

    std::string channel_name = params[0];
    std::string target_nick = params[1];
    std::string kick_message = params.size() > 2 ? params[2] : client->getNickname();

    Channel* channel = _server.getChannel(channel_name);
    if (!channel) {
        sendReply(client, ERR_NOSUCHCHANNEL, channel_name + " :No such channel");
        return;
    }

    if (!channel->hasClient(client)) {
        sendReply(client, ERR_NOTONCHANNEL, channel_name + " :You're not on that channel");
        return;
    }

    if (!channel->isOperator(client)) {
        sendReply(client, ERR_CHANOPRIVSNEEDED, channel_name + " :You're not channel operator");
        return;
    }

    Client* target = _server.getClientByNickname(target_nick);
    if (!target) {
        sendReply(client, ERR_NOSUCHNICK, target_nick + " :No such nick/channel");
        return;
    }

    if (!channel->hasClient(target)) {
        sendReply(client, ERR_NOTONCHANNEL, channel_name + " :They aren't on that channel");
        return;
    }

    // Format: :nick!user@host KICK #channel target :reason
    std::string kick_msg = ":" + client->getNickname() + "!" + client->getUsername() + "@" + SERVER_NAME + 
                          " KICK " + channel_name + " " + target_nick + " :" + kick_message + "\r\n";
    
    // Send kick message to all clients in the channel (including the kicked user)
    channel->broadcast(kick_msg);
    
    // Remove the kicked user from the channel
    channel->removeClient(target);
}

void CommandHandler::handleTopic(Client* client, const std::vector<std::string>& params) {
    if (!client->isRegistered()) {
        sendReply(client, ERR_NOTREGISTERED, ":You have not registered");
        return;
    }

    if (params.empty()) {
        sendReply(client, ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters");
        return;
    }

    std::string channelName = params[0];
    Channel* channel = _server.getChannel(channelName);

    if (!channel) {
        sendReply(client, ERR_NOSUCHCHANNEL, channelName + " :No such channel");
        return;
    }

    if (!channel->hasClient(client)) {
        sendReply(client, ERR_NOTONCHANNEL, channelName + " :You're not on that channel");
        return;
    }

    // If no topic is provided, display the current topic
    if (params.size() == 1) {
        if (channel->getTopic().empty()) {
            sendReply(client, RPL_NOTOPIC, channelName + " :No topic is set");
        } else {
            sendReply(client, RPL_TOPIC, channelName + " :" + channel->getTopic());
        }
        return;
    }

    // If a topic is provided, check if the user has permission to set it
    // Only channel operators can set the topic if topic restriction is active
    if (channel->isTopicRestricted() && !channel->isOperator(client)) {
        sendReply(client, ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator");
        return;
    }

    // Set the new topic
    channel->setTopic(params[1], client);
}

void CommandHandler::handleInvite(Client* client, const std::vector<std::string>& params) {
    if (!client->isRegistered()) {
        sendReply(client, ERR_NOTREGISTERED, ":You have not registered");
        return;
    }

    if (params.size() < 2) {
        sendReply(client, ERR_NEEDMOREPARAMS, "INVITE :Not enough parameters");
        return;
    }

    std::string nickname = params[0];
    std::string channelName = params[1];

    // Check if target user exists
    Client* target = _server.getClientByNickname(nickname);
    if (!target) {
        sendReply(client, ERR_NOSUCHNICK, nickname + " :No such nick");
        return;
    }

    // Check if channel exists
    Channel* channel = _server.getChannel(channelName);
    if (!channel) {
        sendReply(client, ERR_NOSUCHCHANNEL, channelName + " :No such channel");
        return;
    }

    // Check if inviter is on the channel
    if (!channel->hasClient(client)) {
        sendReply(client, ERR_NOTONCHANNEL, channelName + " :You're not on that channel");
        return;
    }

    // Check if inviter is an operator
    if (!channel->isOperator(client)) {
        sendReply(client, ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator");
        return;
    }

    // Add invite
    channel->addInvite(target);

    // Send invite notification to target
    std::string invite_msg = ":";
    invite_msg += client->getNickname();
    invite_msg += "!";
    invite_msg += client->getUsername();
    invite_msg += "@";
    invite_msg += SERVER_NAME;
    invite_msg += " INVITE ";
    invite_msg += nickname;
    invite_msg += " ";
    invite_msg += channelName;
    invite_msg += "\r\n";
    send(target->getFd(), invite_msg.c_str(), invite_msg.length(), 0);

    // Send RPL_INVITING to inviter
    sendReply(client, RPL_INVITING, nickname + " " + channelName);
}

void CommandHandler::handleMode(Client* client, const std::vector<std::string>& params) {
    if (!client->isRegistered()) {
        sendReply(client, ERR_NOTREGISTERED, ":You have not registered");
        return;
    }

    if (params.size() < 2) {
        sendReply(client, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
        return;
    }

    std::string channel_name = params[0];
    Channel* channel = _server.getChannel(channel_name);
    
    if (!channel) {
        sendReply(client, ERR_NOSUCHCHANNEL, channel_name + " :No such channel");
        return;
    }

    if (!channel->hasClient(client)) {
        sendReply(client, ERR_NOTONCHANNEL, channel_name + " :You're not on that channel");
        return;
    }

    if (!channel->isOperator(client)) {
        sendReply(client, ERR_CHANOPRIVSNEEDED, channel_name + " :You're not channel operator");
        return;
    }

    std::string modes = params[1];
    size_t param_index = 2;
    bool adding = true;  // Default to adding modes
    std::string modeChanges;
    Client* targetClient = NULL;  // Moved outside switch

    for (size_t i = 0; i < modes.length(); ++i) {
        char mode = modes[i];
        
        // Handle mode flag
        if (mode == '+') {
            adding = true;
            continue;
        } else if (mode == '-') {
            adding = false;
            continue;
        }
        
        switch (mode) {
            case 't':  // Topic restriction
                channel->setTopicRestricted(adding);
                break;
            case 'i':  // Invite only
                channel->setInviteOnly(adding);
                break;
            case 'k':  // Channel key
                if (adding) {
                    if (param_index < params.size()) {
                        channel->setKey(params[param_index++]);
                    } else {
                        sendReply(client, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
                        return;
                    }
                } else {
                    channel->setKey("");
                }
                break;
            case 'l':  // User limit
                if (adding) {
                    if (param_index < params.size()) {
                        size_t limit = std::atoi(params[param_index++].c_str());
                        channel->setUserLimit(limit);
                    } else {
                        sendReply(client, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
                        return;
                    }
                } else {
                    channel->setUserLimit(0);
                }
                break;
            case 'v':
                if (i + 1 >= params.size()) {
                    sendReply(client, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
                    return;
                }
                targetClient = _server.getClientByNickname(params[i + 1]);
                if (!targetClient) {
                    sendReply(client, ERR_NOSUCHNICK, params[i + 1] + " :No such nick");
                    return;
                }
                if (!channel->hasClient(targetClient)) {
                    sendReply(client, ERR_NOTONCHANNEL, channel_name + " :They aren't on that channel");
                    return;
                }
                if (adding) {
                    if (!channel->isVoiced(targetClient)) {
                        channel->addVoice(targetClient);
                        modeChanges += "+v " + params[i + 1] + " ";
                    }
                } else {
                    if (channel->isVoiced(targetClient)) {
                        channel->removeVoice(targetClient);
                        modeChanges += "-v " + params[i + 1] + " ";
                    }
                }
                i++; // Skip the nickname parameter
                break;
            case 'o':
                if (i + 1 >= params.size()) {
                    sendReply(client, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
                    return;
                }
                targetClient = _server.getClientByNickname(params[i + 1]);
                if (!targetClient) {
                    sendReply(client, ERR_NOSUCHNICK, params[i + 1] + " :No such nick");
                    return;
                }
                if (!channel->hasClient(targetClient)) {
                    sendReply(client, ERR_NOTONCHANNEL, channel_name + " :They aren't on that channel");
                    return;
                }
                if (adding) {
                    if (!channel->isOperator(targetClient)) {
                        channel->addOperator(targetClient);
                        modeChanges += "+o " + params[i + 1] + " ";
                    }
                } else {
                    if (channel->isOperator(targetClient)) {
                        channel->removeOperator(targetClient);
                        modeChanges += "-o " + params[i + 1] + " ";
                    }
                }
                i++; // Skip the nickname parameter
                break;
            case 'b':  // Ban
                if (param_index < params.size()) {
                    std::string mask = params[param_index++];
                    if (adding) {
                        channel->addBan(mask);
                    } else {
                        channel->removeBan(mask);
                    }
                } else {
                    sendReply(client, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
                    return;
                }
                break;
            default:
                sendReply(client, ERR_UNKNOWNMODE, std::string(1, mode) + " :is unknown mode char to me");
                continue;
        }

        // Broadcast mode change
        std::string mode_msg = ":";
        mode_msg += client->getNickname();
        mode_msg += "!";
        mode_msg += client->getUsername();
        mode_msg += "@";
        mode_msg += SERVER_NAME;
        mode_msg += " MODE ";
        mode_msg += channel_name;
        mode_msg += " ";
        mode_msg += (adding ? "+" : "-");
        mode_msg += mode;
        if (mode == 'k' || mode == 'l' || mode == 'b') {
            mode_msg += " ";
            mode_msg += params[param_index - 1];
        }
        mode_msg += "\r\n";
        channel->broadcast(mode_msg);
    }

    // Broadcast mode changes
    if (!modeChanges.empty()) {
        std::string mode_changes_msg = ":";
        mode_changes_msg += client->getNickname();
        mode_changes_msg += "!";
        mode_changes_msg += client->getUsername();
        mode_changes_msg += "@";
        mode_changes_msg += SERVER_NAME;
        mode_changes_msg += " MODE ";
        mode_changes_msg += channel_name;
        mode_changes_msg += " :" + modeChanges + "\r\n";
        channel->broadcast(mode_changes_msg);
    }
}

void CommandHandler::handleCommand(Client* client, const std::string& message) {
    std::vector<std::string> tokens = splitMessage(message);
    if (tokens.empty())
        return;

    std::string command = tokens[0];
    std::vector<std::string> params(tokens.begin() + 1, tokens.end());

    // Convert command to uppercase for case-insensitive comparison
    for (std::string::iterator it = command.begin(); it != command.end(); ++it)
        *it = toupper(*it);

    Logger::debug("Processing command: " + command + " from " + client->getNickname());

    // Handle valid commands only
    if (command == "PASS")
        handlePass(client, params);
    else if (command == "NICK")
        handleNick(client, params);
    else if (command == "USER")
        handleUser(client, params);
    else if (command == "QUIT")
        handleQuit(client, params);
    else if (command == "JOIN")
        handleJoin(client, params);
    else if (command == "PART")
        handlePart(client, params);
    else if (command == "PRIVMSG")
        handlePrivmsg(client, params);
    else if (command == "NAMES")
        handleNames(client, params);
    else if (command == "KICK")
        handleKick(client, params);
    else if (command == "TOPIC")
        handleTopic(client, params);
    else if (command == "INVITE")
        handleInvite(client, params);
    else if (command == "MODE")
        handleMode(client, params);
    else {
        // Any other command is invalid
        sendReply(client, ERR_UNKNOWNCOMMAND, command + " :Unknown command");
    }
} 