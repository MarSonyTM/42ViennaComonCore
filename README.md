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