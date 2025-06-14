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
    
    // Channel command handlers
    void handleJoin(Client* client, const std::vector<std::string>& params);
    void handlePart(Client* client, const std::vector<std::string>& params);
    void handlePrivmsg(Client* client, const std::vector<std::string>& params);
    void handleNames(Client* client, const std::vector<std::string>& params);
    void handleKick(Client* client, const std::vector<std::string>& params);
    void handleTopic(Client* client, const std::vector<std::string>& params);
    void handleInvite(Client* client, const std::vector<std::string>& params);
    void handleMode(Client* client, const std::vector<std::string>& params);

    // Helper functions
    std::vector<std::string> splitMessage(const std::string& message);
    bool isValidNickname(const std::string& nickname);
    bool isValidChannelName(const std::string& channel);
    void sendReply(Client* client, int code, const std::string& message);
    void broadcastToChannel(const std::string& channel_name, const std::string& message, Client* exclude = NULL);

public:
    CommandHandler(Server& server);
    ~CommandHandler();

    // Deleted copy constructor and assignment operator
    CommandHandler(const CommandHandler& other);
    CommandHandler& operator=(const CommandHandler& other);

    void handleCommand(Client* client, const std::string& message);
};

#endif 