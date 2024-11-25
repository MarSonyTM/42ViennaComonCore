#include "../include/CGIHandler.hpp"
#include <sys/wait.h>
#include <cstring>
#include <cerrno>

CGIHandler::CGIHandler(const std::string& cgiPath, const std::string& root)
    : cgiPath(cgiPath), root(root) {}

CGIHandler::~CGIHandler() {}

void CGIHandler::setupEnvironment() const {
    setenv("REQUEST_METHOD", requestMethod.c_str(), 1);
    setenv("QUERY_STRING", queryString.c_str(), 1);
    if (!contentLength.empty())
        setenv("CONTENT_LENGTH", contentLength.c_str(), 1);
    if (!contentType.empty())
        setenv("CONTENT_TYPE", contentType.c_str(), 1);
    setenv("SCRIPT_NAME", scriptPath.c_str(), 1);
    setenv("SCRIPT_FILENAME", (root + scriptPath).c_str(), 1);
    setenv("REDIRECT_STATUS", "200", 1);
    setenv("SERVER_SOFTWARE", "WebServer/1.0", 1);
    setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
    setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
}

bool CGIHandler::executeCGI(std::string& response) {
    int input[2], output[2];
    
    if (pipe(input) < 0 || pipe(output) < 0) {
        std::cerr << "Pipe creation failed: " << strerror(errno) << std::endl;
        return false;
    }

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Fork failed: " << strerror(errno) << std::endl;
        return false;
    }

    if (pid == 0) {  // Child process
        setupEnvironment();

        dup2(input[0], STDIN_FILENO);
        dup2(output[1], STDOUT_FILENO);
        
        close(input[1]);
        close(output[0]);
        close(input[0]);
        close(output[1]);

        std::string fullScriptPath = root + scriptPath;

        char* const args[] = {
            const_cast<char*>(cgiPath.c_str()),
            const_cast<char*>(fullScriptPath.c_str()),
            NULL
        };

        execve(cgiPath.c_str(), args, environ);
        std::cerr << "CGI execution failed: " << strerror(errno) << std::endl;
        exit(1);
    }

    close(input[0]);
    close(output[1]);

    if (requestMethod == "POST" && !requestBody.empty()) {
        write(input[1], requestBody.c_str(), requestBody.length());
    }
    close(input[1]);

    char buffer[4096];
    ssize_t bytes;
    response.clear();
    
    while ((bytes = read(output[0], buffer, sizeof(buffer))) > 0) {
        response.append(buffer, bytes);
    }
    close(output[0]);

    int status;
    waitpid(pid, &status, 0);

    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

bool CGIHandler::processCGI(std::string& response) {
    return executeCGI(response);
} 