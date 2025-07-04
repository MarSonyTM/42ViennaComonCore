#include "../include/common.hpp"
#include "../include/Server.hpp"
#include "../include/Logger.hpp"

void signal_handler(int signum) {
    (void)signum;
    Logger::info("Shutting down server...");
    
    // Get server instance and stop it
    if (Server::getInstance()) {
        Server::getInstance()->stop();
    }
    
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
        return 1;
    }

    // Set up signal handling
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    try {
        int port = std::atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            Logger::error("Invalid port number");
            return 1;
        }

        Server server(port, argv[2]);
        Server::setInstance(&server);  // Set the static instance
        
        if (!server.start()) {
            Logger::error("Failed to start server");
            return 1;
        }

        Logger::info("Server started on port " + std::string(argv[1]));
        server.run();
        
        // Clear the instance pointer before exiting
        Server::setInstance(NULL);
    }
    catch (const std::exception& e) {
        Logger::error(std::string("Error: ") + e.what());
        Server::setInstance(NULL);  // Clear instance pointer on error
        return 1;
    }

    return 0;
} 