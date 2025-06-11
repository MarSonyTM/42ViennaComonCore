#include "../../include/Logger.hpp"

Logger::Level Logger::_level = Logger::INFO;

void Logger::setLogLevel(Level level) {
    _level = level;
}

void Logger::debug(const std::string& message) {
    log(DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(INFO, message);
}

void Logger::warning(const std::string& message) {
    log(WARNING, message);
}

void Logger::error(const std::string& message) {
    log(ERROR, message);
}

void Logger::log(Level level, const std::string& message) {
    if (level < _level)
        return;

    std::string prefix;
    switch (level) {
        case DEBUG:
            prefix = "\033[36m[DEBUG]\033[0m ";
            break;
        case INFO:
            prefix = "\033[32m[INFO]\033[0m ";
            break;
        case WARNING:
            prefix = "\033[33m[WARNING]\033[0m ";
            break;
        case ERROR:
            prefix = "\033[31m[ERROR]\033[0m ";
            break;
    }
    
    std::cout << prefix << message << std::endl;
} 