#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <map>

class Request {
private:
    std::string _method;
    std::string _uri;
    std::string _version;
    std::map<std::string, std::string> _headers;
    std::string _body;

public:
    Request();
    ~Request();

    bool parse(const std::string& raw_request);
    
    // Getters
    const std::string& getMethod() const;
    const std::string& getUri() const;
    const std::string& getVersion() const;
    const std::string& getHeader(const std::string& key) const;
    const std::string& getBody() const;
};

#endif 