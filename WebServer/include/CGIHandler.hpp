#ifndef CGIHANDLER_HPP
#define CGIHANDLER_HPP

#include <string>
#include <vector>
#include <map>
#include <cstdlib>  // for setenv
#include <unistd.h> // for execve, fork, pipe
#include <iostream>
#include <cerrno>   // for errno
#include <cstring>  // for strerror
#include <sys/wait.h>

extern char** environ;

class CGIHandler {
private:
    std::string cgiPath;
    std::string scriptPath;
    std::string requestMethod;
    std::string queryString;
    std::string contentLength;
    std::string contentType;
    std::string requestBody;
    std::string root;

    bool executeCGI(std::string& response);
    void setupEnvironment() const;

public:
    CGIHandler(const std::string& cgiPath, const std::string& root);
    ~CGIHandler();

    void setScriptPath(const std::string& path) { scriptPath = path; }
    void setRequestMethod(const std::string& method) { requestMethod = method; }
    void setQueryString(const std::string& query) { queryString = query; }
    void setContentLength(const std::string& length) { contentLength = length; }
    void setContentType(const std::string& type) { contentType = type; }
    void setRequestBody(const std::string& body) { requestBody = body; }

    bool processCGI(std::string& response);
};

#endif 