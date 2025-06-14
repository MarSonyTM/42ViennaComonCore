#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "common.hpp"

class Channel;

class Client {
private:
    int         _fd;
    std::string _nickname;
    std::string _username;
    std::string _realname;
    std::string _hostname;
    bool        _authenticated;
    bool        _registered;
    std::string _buffer;
    std::vector<Channel*> _channels;

    // Private copy constructor and assignment operator to prevent copying
    Client(const Client& other);
    Client& operator=(const Client& other);

public:
    Client(int fd);
    ~Client();

    // Getters
    int         getFd() const;
    const std::string& getNickname() const;
    const std::string& getUsername() const;
    const std::string& getRealname() const;
    const std::string& getHostname() const;
    bool        isAuthenticated() const;
    bool        isRegistered() const;
    std::string& getBuffer();
    const std::vector<Channel*>& getChannels() const;

    // Setters
    void        setNickname(const std::string& nickname);
    void        setUsername(const std::string& username);
    void        setRealname(const std::string& realname);
    void        setHostname(const std::string& hostname);
    void        setAuthenticated(bool status);
    void        setRegistered(bool status);

    // Channel operations
    void        joinChannel(Channel* channel);
    void        leaveChannel(Channel* channel);
    bool        isInChannel(const Channel* channel) const;

    // Message handling
    void        appendToBuffer(const std::string& data);
    void        sendMessage(const std::string& message);
};

#endif 