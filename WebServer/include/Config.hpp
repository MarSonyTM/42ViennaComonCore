#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <fstream>

struct Location {
    std::string path;
    std::vector<std::string> methods;
    std::string root;
    std::string index;
    bool autoindex;
    size_t client_max_body_size;
    std::string upload_store;
};

struct ServerConfig {
    std::string host;
    int port;
    std::string root;
    std::vector<std::string> server_names;
    std::map<int, std::string> error_pages;
    std::vector<Location> locations;
    size_t client_max_body_size;
};

class Config {
private:
    std::string _config_path;
    std::vector<ServerConfig> _servers;
    void validateSettings();
    void parseServer(std::ifstream& file);
    void parseLocation(std::ifstream& file, ServerConfig& server);
    size_t parseSize(const std::string& size);

public:
    Config(const std::string& path);
    ~Config();
    
    void parse();
    const std::vector<ServerConfig>& getServers() const;
    ServerConfig getDefaultServer() const;
    
    std::string getHost() const;
    int getPort() const;
    std::string getRoot() const;
};

#endif // CONFIG_HPP 