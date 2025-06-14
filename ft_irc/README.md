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

4. **Channel Operations**
   - JOIN command with operator status for channel creator
   - Channel key (password) protection
   - PART command for leaving channels
   - Channel message broadcasting (PRIVMSG)
   - NAMES command showing channel members and operators
   - KICK command with proper operator permission checks
   - TOPIC command for viewing and setting channel topics
   - INVITE command for inviting users to channels

5. **Channel Modes**
   - Invite-only mode (+i)
   - Topic restriction mode (+t)
   - Channel key mode (+k)
     - Setting and removing channel keys
     - Key validation and persistence
     - Special character support
     - Proper error handling

### 🚧 In Progress

1. **Channel Operator Commands**
   - ✅ KICK command (completed)
   - ✅ Channel key protection (completed)
   - ✅ TOPIC command (completed)
   - ✅ INVITE command (completed)
   - ✅ MODE command with key flag (completed)
   - MODE command with other flags (pending)

2. **Additional Channel Features**
   - ✅ Channel password protection
   - User limit enforcement
   - Invite-only mode
   - Topic restriction mode

### 🔜 Planned Features

1. **Advanced Channel Operations**
   - Channel modes and flags
   - Ban lists
   - Exception lists
   - Invite lists

2. **Server Administration**
   - Server operator commands
   - Server configuration
   - Server statistics

### Future Test Cases

1. **Channel Key Mode (+k)**
   - Key changes with different special characters
   - Key changes with spaces or other whitespace
   - Key changes with non-ASCII characters
   - Key changes with maximum length keys
   - Key persistence after server restart
   - Key changes during high server load
   - Key changes with multiple operators

2. **Channel Modes**
   - User limit mode (+l)
   - Ban mode (+b)
   - Voice mode (+v)
   - Operator mode (+o)
   - Multiple mode changes in one command
   - Mode persistence after server restart

3. **Error Handling**
   - Invalid mode syntax
   - Invalid mode parameters
   - Mode changes on non-existent channels
   - Mode changes by non-operators
   - Mode changes with invalid permissions

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

### 3. Channel Operations Test
```bash
# Create and join a channel (becomes operator)
JOIN #testchannel
# Expected: Join confirmation and NAMES list with @ symbol

# Create a channel with a key
JOIN #secretchannel secretkey
# Expected: Join confirmation and NAMES list with @ symbol

# Try to join with wrong key
JOIN #secretchannel wrongkey
# Expected: Error 475 - Cannot join channel (+k) - bad key

# Set a channel topic (as operator)
TOPIC #testchannel :Welcome to the test channel!
# Expected: Topic change broadcast to channel

# Set user limit mode (as operator)
MODE #testchannel +l 5
# Expected: Mode change broadcast to channel

# Try to join when channel is full
JOIN #testchannel
# Expected: Error 471 - Cannot join channel (+l) - channel is full

# Remove user limit mode
MODE #testchannel -l
# Expected: Mode change broadcast to channel

# View channel topic
TOPIC #testchannel
# Expected: RPL_TOPIC (332) with the current topic

# Try to set topic without operator status
TOPIC #testchannel :This should fail
# Expected: Error 482 - Not channel operator

# Try to view topic without joining
TOPIC #testchannel
# Expected: Error 442 - You're not on that channel

# Kick someone as operator
KICK #testchannel target :you are kicked
# Expected: Kick message broadcast to channel
```

## Error Codes

- 001: Welcome message
- 331: No topic is set
- 332: Channel topic
- 353: NAMES reply
- 366: End of NAMES list
- 401: No such nick/channel
- 403: No such channel
- 404: Cannot send to channel
- 431: No nickname given
- 432: Erroneous nickname
- 433: Nickname already in use
- 442: Not on channel
- 451: Not registered
- 461: Not enough parameters
- 462: Already registered
- 464: Password incorrect
- 475: Cannot join channel (+k) - bad key
- 482: Not channel operator

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

1. Complete Channel Operator Commands
   - ✅ Implement INVITE command
   - Add MODE command functionality
   - Implement MODE command with various flags

2. Add Channel Modes
   - Password protection (+k)
   - User limit (+l)
   - Invite-only mode (+i)
   - Topic restriction (+t)

3. Implement Server Administration
   - Add server operator commands
   - Implement server configuration
   - Add server statistics

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