# 42 School Docker Environment

This Dockerfile creates a development environment that matches the 42 school environment specifications.

## System Specifications
- Ubuntu 22.04.5 LTS
- GCC 10.5.0
- Zsh shell
- Common development tools (make, gdb, valgrind, etc.)

## Building the Docker Image

```bash
# Build the image
docker build -t 42school-env .
```

## Running the Container

### Basic Usage
```bash
# Run the container with current directory mounted
docker run -it -v $(pwd):/home/student/project 42school-env
```

### Advanced Usage (with resource limits)
```bash
# Run with memory limits (8GB in this example)
docker run -it \
    --memory=8g \
    --memory-swap=12g \
    -v $(pwd):/home/student/project \
    42school-env
```

## Features
- Ubuntu 22.04.5 LTS (matching school environment)
- GCC 10.5.0
- Essential development tools
- Zsh shell
- Non-root user 'student'
- Valgrind for memory checking
- GDB for debugging

## Notes
- The container uses a non-root user 'student' for safety
- Your current directory is mounted at /home/student/project
- All changes in the mounted directory persist after container shutdown
- The environment closely mirrors the 42 school setup 

# 42Vienna Common Core

## Project Progress

### ft_irc
- [x] Basic server setup
- [x] Client connection handling
- [x] Basic command parsing
- [x] PASS command
- [x] NICK command
- [x] USER command
- [x] JOIN command
- [x] PART command
- [x] PRIVMSG command
- [x] NAMES command
- [x] KICK command
- [x] TOPIC command
- [x] INVITE command
- [x] MODE command
  - [x] Invite-only mode (+i)
  - [x] Topic restriction mode (+t)
  - [ ] Channel key mode (+k)
  - [ ] User limit mode (+l)
  - [ ] Operator privileges (+o)
  - [ ] Voice privileges (+v)

### Recent Updates
- Implemented topic restriction mode (+t)
  - Added proper mode setting and removal
  - Implemented permission checks for topic changes
  - Added broadcasting of topic changes to all channel members
  - Fixed bug in topic change permission logic
  - Added comprehensive testing for topic restriction functionality

### Next Steps
- Implement channel key mode (+k)
- Add user limit mode (+l)
- Implement operator and voice privileges
- Add more error handling and edge cases
- Improve documentation

### Testing
To test the topic restriction mode:
1. Start the server: `./ircserv 6667 password`
2. Connect as operator and set mode: `MODE #channel +t`
3. Try changing topic as regular user (should fail)
4. Remove restriction: `MODE #channel -t`
5. Verify regular users can now change topic

### Known Issues
- None at the moment

### Notes
- All implemented features follow RFC 1459 specifications
- Code follows 42 coding style guidelines
- Comprehensive error handling implemented
- All features thoroughly tested 

# ft_irc - IRC Server Implementation

This project implements an Internet Relay Chat (IRC) server following RFC 1459 specifications. The server is written in C++98 and provides robust message handling and memory management.

## Core Features

### Memory Management
- **SmartPtr Template Class**
  - Custom smart pointer implementation for C++98
  - Automatic resource cleanup
  - Memory leak prevention
  - RAII-compliant design
  - Usage example:
    ```cpp
    SmartPtr<Client> client(new Client(socket_fd));
    // No need to manually delete, SmartPtr handles cleanup
    ```

### Message Handling
- **DynamicBuffer Class**
  - Efficient message buffering system
  - Automatic buffer growth up to 16KB
  - Protection against buffer overflows
  - Line-based message parsing
  - Usage example:
    ```cpp
    DynamicBuffer buffer;
    buffer.append(data, length);
    while (buffer.hasCompleteLine()) {
        std::string line = buffer.getLine();
        // Process the line
    }
    ```

### IRC Protocol Implementation
- **Client Management**
  - Authentication (PASS command)
  - Nickname handling (NICK command)
  - User registration (USER command)
  - Private messaging (PRIVMSG command)

- **Channel Operations**
  - Channel creation and joining (JOIN command)
  - Channel messaging
  - Operator privileges
  - Channel modes:
    - Invite-only mode (+i)
    - Topic restriction (+t)
    - Channel key (+k)
    - User limit (+l)
    - Operator status (+o)

## Technical Details

### Memory Safety Features
1. **SmartPtr Implementation**
   - Prevents memory leaks through RAII
   - Disabled copy constructor to prevent double-free
   - Supports pointer operations:
     - Dereferencing (`operator*`)
     - Member access (`operator->`)
     - Resource release (`release()`)
     - Pointer reset (`reset()`)

2. **DynamicBuffer Features**
   - Initial buffer size: 1024 bytes
   - Maximum buffer size: 16KB
   - Automatic growth strategy:
     - Doubles capacity when needed
     - Stops at maximum size
   - Memory overflow protection
   - Efficient line parsing for IRC messages

### Error Handling
- Buffer overflow protection
- Socket error handling
- Memory allocation failure handling
- Invalid message format detection
- Network disconnection handling

## Building and Running

### Prerequisites
- C++98 compatible compiler
- Make build system
- POSIX-compliant operating system

### Build Instructions
```bash
make        # Build the server
make clean  # Remove object files
make re     # Rebuild everything
```

### Running the Server
```bash
./ircserv <port> <password>
```
Example:
```bash
./ircserv 6667 serverpass
```

## Testing

### Memory Testing
```bash
valgrind --leak-check=full ./ircserv 6667 password
```

### Load Testing
1. Connect multiple clients:
```bash
nc localhost 6667
```
2. Send test messages:
```
PASS password
NICK testuser
USER testuser 0 * :Test User
JOIN #testchannel
PRIVMSG #testchannel :Test message
```

## Recent Updates
- Added SmartPtr template for better memory management
- Implemented DynamicBuffer for improved message handling
- Enhanced error handling and memory safety
- Improved message parsing efficiency

## Known Issues
- None at the moment

## Notes
- All features comply with C++98 standard
- Code follows 42 coding style guidelines
- Comprehensive error handling implemented
- All features thoroughly tested

## Contributing
1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License
This project is part of the 42 school curriculum. 