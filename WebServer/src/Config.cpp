#include "../include/Config.hpp"
#include <sstream>
#include <stdexcept>

Config::Config(const std::string& path) : _config_path(path) {
    parse();
}

Config::~Config() {}

void Config::parse() {
    std::ifstream file(_config_path.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open configuration file: " + _config_path);
    }

    ServerConfig current_server;
    std::string line;
    
    while (std::getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#')
            continue;

        if (line == "server {") {
            parseServer(file);
        }
    }

    if (_servers.empty()) {
        throw std::runtime_error("No server configuration found");
    }
}

void Config::parseServer(std::ifstream& file) {
    ServerConfig server;
    server.client_max_body_size = 1024 * 1024; // Default 1MB
    std::string line;

    while (std::getline(file, line) && line != "}") {
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream iss(line);
        std::string key, value;
        iss >> key;

        if (key == "location") {
            std::string path;
            iss >> path;
            if (std::getline(file, line) && line == "{") {
                parseLocation(file, server);
            }
        } else if (key == "listen") {
            iss >> server.port;
        } else if (key == "server_name") {
            std::string name;
            while (iss >> name) {
                server.server_names.push_back(name);
            }
        } else if (key == "root") {
            iss >> server.root;
        } else if (key == "error_page") {
            int code;
            std::string page;
            iss >> code >> page;
            server.error_pages[code] = page;
        } else if (key == "client_max_body_size") {
            std::string size;
            iss >> size;
            // Parse size (e.g., "10M", "1G")
            server.client_max_body_size = parseSize(size);
        }
    }

    _servers.push_back(server);
}

void Config::parseLocation(std::ifstream& file, ServerConfig& server) {
    Location loc;
    loc.autoindex = false;
    loc.client_max_body_size = server.client_max_body_size;
    
    std::string line;
    while (std::getline(file, line) && line != "}") {
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "methods") {
            std::string method;
            while (iss >> method) {
                loc.methods.push_back(method);
            }
        } else if (key == "root") {
            iss >> loc.root;
        } else if (key == "index") {
            iss >> loc.index;
        } else if (key == "autoindex") {
            std::string value;
            iss >> value;
            loc.autoindex = (value == "on");
        } else if (key == "client_max_body_size") {
            std::string size;
            iss >> size;
            loc.client_max_body_size = parseSize(size);
        } else if (key == "upload_store") {
            iss >> loc.upload_store;
        }
    }

    server.locations.push_back(loc);
}

size_t Config::parseSize(const std::string& size) {
    size_t len = size.length();
    char unit = size[len - 1];
    size_t value = std::atoi(size.substr(0, len - 1).c_str());
    
    switch (unit) {
        case 'K': return value * 1024;
        case 'M': return value * 1024 * 1024;
        case 'G': return value * 1024 * 1024 * 1024;
        default: return value;
    }
}

const std::vector<ServerConfig>& Config::getServers() const {
    return _servers;
}

ServerConfig Config::getDefaultServer() const {
    if (_servers.empty()) {
        throw std::runtime_error("No server configuration available");
    }
    return _servers[0];
}

std::string Config::getHost() const {
    ServerConfig server = getDefaultServer();
    return server.host.empty() ? "127.0.0.1" : server.host;
}

int Config::getPort() const {
    ServerConfig server = getDefaultServer();
    return server.port ? server.port : 8080;
}

std::string Config::getRoot() const {
    ServerConfig server = getDefaultServer();
    return server.root.empty() ? "www" : server.root;
} 