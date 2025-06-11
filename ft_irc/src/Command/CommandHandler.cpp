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
    } else if (channel->hasKey() && (provided_key != channel->getKey())) {
        sendReply(client, ERR_BADCHANNELKEY, channel_name + " :Cannot join channel (+k) - wrong channel key");
        return;
    }

    if (channel->hasClient(client)) {
        Logger::debug("Client " + client->getNickname() + " already in channel " + channel_name);
        return; // Already in channel
    }

    // Format: :nick!user@host JOIN #channel
    std::string join_msg = ":" + client->getNickname() + "!" + client->getUsername() + "@" + SERVER_NAME + 
                          " JOIN " + channel_name + "\r\n";
    
    Logger::debug("Adding client " + client->getNickname() + " to channel " + channel_name);
    channel->addClient(client);
    
    Logger::debug("Broadcasting JOIN message: " + join_msg);
    // Broadcast to all clients in the channel (including the joining client)
    channel->broadcast(join_msg);

    // Send NAMES list to the joining client
    handleNames(client, params);
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

    if (command == "PASS")
        handlePass(client, params);
    else if (command == "NICK")
        handleNick(client, params);
    else if (command == "USER")
        handleUser(client, params);
    else if (command == "QUIT")
        handleQuit(client, params);
    else if (command == "JOIN") {
        Logger::debug("Handling JOIN command with params: " + (params.empty() ? "none" : params[0]));
        handleJoin(client, params);
    }
    else if (command == "PART")
        handlePart(client, params);
    else if (command == "PRIVMSG")
        handlePrivmsg(client, params);
    else if (command == "NAMES")
        handleNames(client, params);
    else if (command == "KICK")
        handleKick(client, params);
    else
        Logger::debug("Unknown command received: " + command);
} 