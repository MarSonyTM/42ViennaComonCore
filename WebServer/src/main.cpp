#include "../include/Server.hpp"
#include "../include/Config.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    try {
        // Use config/default.conf as default path
        std::string config_path = (argc > 1) ? argv[1] : "config/default.conf";
        
        // Load and parse configuration
        Config config(config_path);
        std::cout << "Configuration loaded from: " << config_path << std::endl;
        
        // Get all server configurations
        std::vector<ServerConfig> servers = config.getServers();
        std::vector<pid_t> server_processes;
        
        // Create server processes for each configuration
        for (size_t i = 0; i < servers.size(); ++i) {
            ServerConfig& server_config = servers[i];
            std::cout << "\nServer " << i + 1 << ":" << std::endl;
            std::cout << "Host: " << server_config.host << std::endl;
            std::cout << "Port: " << server_config.port << std::endl;
            std::cout << "Root: " << server_config.root << std::endl;
            std::cout << "Max Body Size: " << server_config.client_max_body_size << " bytes" << std::endl;
            
            pid_t pid = fork();
            if (pid == 0) {
                // Child process
                Server server(
                    server_config.host.empty() ? "127.0.0.1" : server_config.host,
                    server_config.port ? server_config.port : 8080,
                    server_config.root.empty() ? "www" : server_config.root
                );
                server.start();
                exit(0);
            } else if (pid > 0) {
                // Parent process
                server_processes.push_back(pid);
            } else {
                throw std::runtime_error("Fork failed");
            }
        }
        
        std::cout << "\nAll servers started." << std::endl;
        
        // Wait for all server processes
        for (size_t i = 0; i < server_processes.size(); ++i) {
            int status;
            waitpid(server_processes[i], &status, 0);
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
} 