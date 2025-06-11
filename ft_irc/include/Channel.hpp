#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "common.hpp"
# include "Client.hpp"

class Channel {
private:
    std::string             _name;
    std::string             _topic;
    std::string             _password;
    std::vector<Client*>    _clients;
    std::vector<Client*>    _operators;
    bool                    _invite_only;
    bool                    _topic_restricted;
    size_t                  _user_limit;
    std::vector<Client*>    _invited_clients;

    // Private copy constructor and assignment operator to prevent copying
    Channel(const Channel& other);
    Channel& operator=(const Channel& other);

public:
    Channel(const std::string& name);
    ~Channel();

    // Getters
    const std::string&          getName() const;
    const std::string&          getTopic() const;
    const std::string&          getPassword() const;
    const std::vector<Client*>& getClients() const;
    const std::vector<Client*>& getOperators() const;
    bool                        isInviteOnly() const;
    bool                        isTopicRestricted() const;
    size_t                      getUserLimit() const;

    // Setters
    void setTopic(const std::string& topic);
    void setPassword(const std::string& password);
    void setInviteOnly(bool status);
    void setTopicRestricted(bool status);
    void setUserLimit(size_t limit);

    // Client operations
    void addClient(Client* client);
    void removeClient(Client* client);
    bool hasClient(Client* client) const;
    void addOperator(Client* client);
    void removeOperator(Client* client);
    bool isOperator(Client* client) const;

    // Invite operations
    void inviteClient(Client* client);
    void removeInvite(Client* client);
    bool isInvited(Client* client) const;

    // Message broadcasting
    void broadcast(const std::string& message, Client* exclude = NULL);
};

#endif 