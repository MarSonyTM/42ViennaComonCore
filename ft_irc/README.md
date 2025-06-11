# ft_irc - Internet Relay Chat Server

This is an implementation of an IRC (Internet Relay Chat) server in C++98. The project aims to create a server that can handle multiple clients simultaneously and implements the IRC protocol.

## Current Implementation Status

### ✅ Completed Features

1. **Basic Server Infrastructure**
   - Non-blocking socket operations
   - Multiple client handling using poll()
   - Clean connection management

2. **Authentication & Registration**
   - PASS command for server password authentication
   - NICK command with proper nickname validation
   - USER command for user registration
   - Complete registration sequence
   - Welcome messages

3. **Error Handling**
   - Invalid password detection
   - Nickname collision prevention
   - Invalid nickname format rejection
   - Proper registration sequence enforcement
   - Clean client disconnection handling

### 🚧 Planned Features

1. Channel Operations
   - JOIN command
   - PART command
   - Channel message broadcasting

2. Private Messaging
   - PRIVMSG command for both users and channels

3. Channel Operator Commands
   - KICK command
   - INVITE command
   - TOPIC command
   - MODE command with various flags

## Building the Project

```bash
make        # Build the project
make re     # Rebuild the project
make clean  # Remove object files
make fclean # Remove object files and executable
```

## Running the Server

```bash
./ircserv <port> <password>
```
Example:
```bash
./ircserv 6667 password
```

## Testing the Current Implementation

You can test the server using netcat (nc). Here's a step-by-step testing guide:

### 1. Basic Connection Test
```bash
nc localhost 6667
```

### 2. Registration Sequence Test
```bash
# Connect and try to set nickname without authentication (should fail)
NICK testuser
# Expected: Error 451 - Not registered

# Try wrong password (should fail)
PASS wrongpassword
# Expected: Error 464 - Password incorrect

# Use correct password
PASS password
# Expected: No response (success)

# Set nickname
NICK testuser
# Expected: No response if successful

# Complete registration
USER testuser 0 * :Real Name
# Expected: Welcome message (001)
```

### 3. Nickname Validation Test
```bash
# Try invalid nicknames
NICK 123test     # Starts with number (should fail)
NICK test@user   # Contains special character (should fail)
NICK t_est-user  # Valid nickname with allowed special characters
```

### 4. Multiple Client Test
1. Open two terminal windows
2. Connect to the server from both terminals
3. Try to use the same nickname in both connections
4. Verify that nickname collision is properly handled

### 5. Quit Test
```bash
QUIT :Goodbye!
# Expected: Connection closes
```

## Error Codes

- 001: Welcome message
- 431: No nickname given
- 432: Erroneous nickname
- 433: Nickname already in use
- 451: Not registered
- 461: Not enough parameters
- 462: Already registered
- 464: Password incorrect

## Project Structure

```
ft_irc/
├── src/
│   ├── main.cpp
│   ├── Server/
│   │   └── Server.cpp
│   ├── Client/
│   │   └── Client.cpp
│   ├── Channel/
│   │   └── Channel.cpp
│   ├── Command/
│   │   └── CommandHandler.cpp
│   └── Utils/
│       └── Logger.cpp
├── include/
│   ├── Server.hpp
│   ├── Client.hpp
│   ├── Channel.hpp
│   ├── CommandHandler.hpp
│   └── Logger.hpp
└── Makefile
```

## Next Steps

1. Implement Channel Operations
   - Create channel creation/joining functionality
   - Implement channel message broadcasting
   - Add channel user list management

2. Add Private Messaging
   - Implement direct messages between users
   - Add channel message support

3. Implement Channel Operator Commands
   - Add operator privileges
   - Implement channel modes
   - Add channel management commands

## Contributing

When contributing to this project:
1. Create feature branches for new functionality
2. Test thoroughly using the provided test cases
3. Update documentation for new features
4. Follow C++98 standard
5. Maintain non-blocking I/O design

## Notes

- The server implements C++98 standard
- All I/O operations are non-blocking
- The server uses poll() for handling multiple clients
- No external libraries are used except standard C++98 libraries 