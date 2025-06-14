#ifndef SERVER_HPP
# define SERVER_HPP

# include "common.hpp"

class Client;
class Channel;
class CommandHandler;

class Server {
private:
    int                         _socket_fd;
    int                         _port;
    std::string                 _password;
    std::vector<pollfd>        _poll_fds;
    std::map<int, Client*>     _clients;
    std::map<std::string, Channel*> _channels;
    CommandHandler*            _command_handler;
    static const std::string   _hostname;

    // Private member functions
    bool    setupSocket();
    void    handleNewConnection();
    void    handleClientMessage(int client_fd);
    void    removeClient(int client_fd);

    // Private copy constructor and assignment operator to prevent copying
    Server(const Server& other);
    Server& operator=(const Server& other);

public:
    Server(int port, const std::string& password);
    ~Server();

    // Public member functions
    bool    start();
    void    run();
    void    stop();

    // Channel operations
    Channel* createChannel(const std::string& name);
    Channel* getChannel(const std::string& name);
    void    removeChannel(const std::string& name);
    void    broadcastToChannel(const std::string& channel_name, const std::string& message, Client* exclude = NULL);

    // Getters
    const std::string&  getPassword() const;
    const std::map<std::string, Channel*>& getChannels() const;
    Client* getClientByNickname(const std::string& nickname) const;
    const std::string& getHostname() const;
};

#endif 