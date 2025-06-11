#include "../../include/CommandHandler.hpp"
#include "../../include/Logger.hpp"
#include <sstream>

CommandHandler::CommandHandler(Server& server) : _server(server) {}

CommandHandler::~CommandHandler() {}

std::vector<std::string> CommandHandler::splitMessage(const std::string& message) {
    std::vector<std::string> tokens;
    std::string token;
    bool in_trailing = false;
    
    for (std::string::const_iterator it = message.begin(); it != message.end(); ++it) {
        if (*it == ':' && tokens.empty()) {
            in_trailing = true;
            continue;
        }
        if (*it == ' ' && !in_trailing) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += *it;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    
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

void CommandHandler::handleCommand(Client* client, const std::string& message) {
    std::vector<std::string> tokens = splitMessage(message);
    if (tokens.empty())
        return;

    std::string command = tokens[0];
    std::vector<std::string> params(tokens.begin() + 1, tokens.end());

    // Convert command to uppercase for case-insensitive comparison
    for (std::string::iterator it = command.begin(); it != command.end(); ++it)
        *it = toupper(*it);

    if (command == "PASS")
        handlePass(client, params);
    else if (command == "NICK")
        handleNick(client, params);
    else if (command == "USER")
        handleUser(client, params);
    else if (command == "QUIT")
        handleQuit(client, params);
    else
        Logger::debug("Unknown command received: " + command);
} 