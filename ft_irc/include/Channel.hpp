#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "common.hpp"
# include "Client.hpp"
# include <string>
# include <vector>
# include <map>
# include <ctime>

class Server;  // Forward declaration

class Channel {
private:
    std::string             _name;
    std::string             _topic;
    std::string             _topicSetter;
    time_t                  _topicTime;
    std::string             _password;
    std::vector<Client*>    _clients;
    std::vector<Client*>    _operators;
    std::vector<Client*>    _voiced_clients;  // List of voiced users
    bool                    _invite_only;
    bool                    _topic_restricted;
    size_t                  _user_limit;
    std::vector<Client*>    _invited_clients;
    std::vector<std::string> _ban_list;  // List of banned masks
    Server*                 _server;

    // Private copy constructor and assignment operator to prevent copying
    Channel(const Channel& other);
    Channel& operator=(const Channel& other);

public:
    Channel(const std::string& name);
    ~Channel();

    // Getters
    const std::string&          getName() const;
    const std::string&          getTopic() const;
    const std::string&          getTopicSetter() const;
    time_t                      getTopicTime() const;
    const std::string&          getPassword() const;
    const std::vector<Client*>& getClients() const;
    const std::vector<Client*>& getOperators() const;
    const std::vector<Client*>& getVoicedClients() const;
    bool                        isInviteOnly() const;
    bool                        isTopicRestricted() const;
    size_t                      getUserLimit() const;
    bool                        hasKey() const;
    const std::string&          getKey() const;
    const std::vector<std::string>& getBanList() const;
    bool                        isBanned(const std::string& mask) const;
    bool                        isVoiced(Client* client) const;

    // Setters
    void setTopic(const std::string& topic, Client* client);
    void setPassword(const std::string& password);
    void setInviteOnly(bool status);
    void setTopicRestricted(bool status);
    void setUserLimit(size_t limit);
    void setKey(const std::string& key);

    // Client operations
    void addClient(Client* client);
    void removeClient(Client* client);
    bool hasClient(Client* client) const;
    void addOperator(Client* client);
    void removeOperator(Client* client);
    bool isOperator(Client* client) const;

    // Voice operations
    void addVoice(Client* client);
    void removeVoice(Client* client);

    // Ban operations
    void addBan(const std::string& mask);
    void removeBan(const std::string& mask);
    bool isBanned(Client* client) const;

    // Invite operations
    void addInvite(Client* client);
    void removeInvite(Client* client);
    bool isInvited(Client* client) const;

    // Message broadcasting
    void broadcast(const std::string& message, Client* exclude = NULL);

    void setServer(Server* server);
};

#endif 