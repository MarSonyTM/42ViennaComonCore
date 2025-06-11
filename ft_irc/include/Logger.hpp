#ifndef LOGGER_HPP
# define LOGGER_HPP

# include "common.hpp"

class Logger {
public:
    enum Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    static void setLogLevel(Level level);
    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);

private:
    static Level _level;
    static void log(Level level, const std::string& message);
    
    // Private constructor to prevent instantiation
    Logger() {}
};

#endif 