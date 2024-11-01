#include "../include/Request.hpp"
#include <sstream>

Request::Request() {}

Request::~Request() {}

bool Request::parse(const std::string& raw_request) {
    std::istringstream request_stream(raw_request);
    std::string line;

    // Parse request line
    if (!std::getline(request_stream, line)) {
        return false;
    }

    std::istringstream request_line(line);
    request_line >> _method >> _uri >> _version;

    // Parse headers
    while (std::getline(request_stream, line) && line != "\r") {
        size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            std::string key = line.substr(0, colon_pos);
            std::string value = line.substr(colon_pos + 2); // Skip ": "
            _headers[key] = value;
        }
    }

    // Parse body if present
    std::string body_line;
    while (std::getline(request_stream, body_line)) {
        _body += body_line + "\n";
    }

    return true;
}

const std::string& Request::getMethod() const {
    return _method;
}

const std::string& Request::getUri() const {
    return _uri;
}

const std::string& Request::getVersion() const {
    return _version;
}

const std::string& Request::getHeader(const std::string& key) const {
    static const std::string empty_string;
    std::map<std::string, std::string>::const_iterator it = _headers.find(key);
    return (it != _headers.end()) ? it->second : empty_string;
}

const std::string& Request::getBody() const {
    return _body;
} 