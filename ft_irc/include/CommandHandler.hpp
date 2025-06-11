#ifndef COMMAND_HANDLER_HPP
# define COMMAND_HANDLER_HPP

# include "common.hpp"
# include "Server.hpp"
# include "Client.hpp"

class CommandHandler {
private:
    Server& _server;

    // Command handlers
    void handlePass(Client* client, const std::vector<std::string>& params);
    void handleNick(Client* client, const std::vector<std::string>& params);
    void handleUser(Client* client, const std::vector<std::string>& params);
    void handleQuit(Client* client, const std::vector<std::string>& params);

    // Helper functions
    std::vector<std::string> splitMessage(const std::string& message);
    bool isValidNickname(const std::string& nickname);
    void sendReply(Client* client, int code, const std::string& message);

public:
    CommandHandler(Server& server);
    ~CommandHandler();

    // Deleted copy constructor and assignment operator
    CommandHandler(const CommandHandler& other);
    CommandHandler& operator=(const CommandHandler& other);

    void handleCommand(Client* client, const std::string& message);

    // IRC Reply codes
    enum {
        RPL_WELCOME = 001,
        ERR_NOSUCHNICK = 401,
        ERR_NOSUCHCHANNEL = 403,
        ERR_NONICKNAMEGIVEN = 431,
        ERR_ERRONEUSNICKNAME = 432,
        ERR_NICKNAMEINUSE = 433,
        ERR_NOTREGISTERED = 451,
        ERR_NEEDMOREPARAMS = 461,
        ERR_ALREADYREGISTERED = 462,
        ERR_PASSWDMISMATCH = 464
    };
};

#endif 