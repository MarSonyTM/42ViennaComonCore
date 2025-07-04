# 🚀 ft_irc - Internet Relay Chat Server

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-98-blue)
![License](https://img.shields.io/badge/License-42-orange)
![Status](https://img.shields.io/badge/Status-Completed-green)

</div>

## 📋 Table of Contents
- [Project Overview](#-project-overview)
- [Features](#-features)
- [Prerequisites](#-prerequisites)
- [Installation](#-installation)
- [Usage](#-usage)
- [Channel Modes](#-channel-modes)
- [Error Codes](#-error-codes)
- [Project Structure](#-project-structure)
- [Testing](#-testing)
- [Contributing](#-contributing)

## 🌟 Project Overview
ft_irc is an IRC server implementation in C++98 that allows multiple clients to connect and communicate in real-time. The server supports various channel modes, operator privileges, and follows the IRC protocol specifications.

## ✨ Features
- 🚀 Multi-client support with non-blocking I/O
- 🎮 Channel management with various modes
- 👑 Operator privileges and commands
- 💬 Private messaging
- 📝 Topic management
- 📨 Invite system
- 👥 User limit control
- 🔑 Channel key protection
- 🎤 Voice privileges

## 📦 Prerequisites
- C++98 compatible compiler
- Make
- Netcat (for testing)

## 🛠️ Installation
```bash
# Clone the repository
git clone https://github.com/yourusername/ft_irc.git

# Navigate to project directory
cd ft_irc

# Build the project
make
```

## 🚀 Usage

### Starting the Server
```bash
./ircserv <port> <password>
```
Example:
```bash
./ircserv 6667 serverpassword
```

### Connecting to the Server
Using netcat: in a second terminal 
```bash
nc localhost 6667
```

### Basic Commands
1. Authentication:
```
PASS serverpassword
NICK yournickname
USER username 0 * :Real Name
```

2. Channel Operations:
```
JOIN #channelname
PRIVMSG #channelname :Your message
PRIVMSG nickname :Private message
```

3. Operator Commands:
```
KICK #channel nickname
INVITE nickname #channel
TOPIC #channel :New topic
```

4. Channel Modes:
```
MODE #channel +i              # Set invite-only
MODE #channel +t              # Restrict topic changes to operators
MODE #channel +k password     # Set channel key (password)
MODE #channel +l 5           # Set user limit
```

## 🎮 Channel Modes

### 🔒 Invite-only Mode (+i)
Restricts channel access to invited users only.

#### Usage
```
MODE #channel +i    # Enable invite-only mode
MODE #channel -i    # Disable invite-only mode
```

#### Testing
1. Enable invite-only mode:
```
MODE #testchannel +i
```

2. Try to join without invite:
```
JOIN #testchannel
```
Expected: Error 473 - Cannot join channel (+i) - invite only

3. Invite a user:
```
INVITE user1 #testchannel
```

4. User joins after invite:
```
JOIN #testchannel
```
Expected: Successful join

### 📝 Topic Restriction Mode (+t)
Restricts topic changes to channel operators only.

#### Usage
```
MODE #channel +t    # Enable topic restriction
MODE #channel -t    # Disable topic restriction
```

#### Testing
1. Enable topic restriction:
```
MODE #testchannel +t
```

2. Non-operator tries to change topic:
```
TOPIC #testchannel :New topic
```
Expected: Error 482 - You're not channel operator

3. Operator changes topic:
```
TOPIC #testchannel :New topic
```
Expected: Topic change broadcast to channel

### 🔑 Channel Key Mode (+k)
Protects channel with a password.

#### Usage
```
MODE #channel +k <key>    # Set channel key
MODE #channel -k          # Remove channel key
```

#### Testing
1. Set channel key:
```
MODE #testchannel +k secretkey
```

2. Try to join with wrong key:
```
JOIN #testchannel wrongkey
```
Expected: Error 475 - Cannot join channel (+k) - bad key

3. Join with correct key:
```
JOIN #testchannel secretkey
```
Expected: Successful join

### 👥 User Limit Mode (+l)
Restricts the number of users in a channel.

#### Usage
```
MODE #channel +l <limit>    # Set user limit
MODE #channel -l            # Remove user limit
```

#### Testing
1. Set user limit:
```
MODE #testchannel +l 5
```

2. Try to join when full:
```
JOIN #testchannel
```
Expected: Error 471 - Cannot join channel (+l) - channel is full

3. Remove limit:
```
MODE #testchannel -l
```

### 🚫 Ban Mode (+b)
Bans users from joining the channel.

#### Usage
```
MODE #channel +b <mask>    # Add ban
MODE #channel -b <mask>    # Remove ban
```

#### Testing
1. Ban a user:
```
MODE #testchannel +b user1
```

2. Banned user tries to join:
```
JOIN #testchannel
```
Expected: Error 474 - Cannot join channel (+b) - you are banned

3. Remove ban:
```
MODE #testchannel -b user1
```

### 🎤 Voice Mode (+v)
Gives voice privileges to users in moderated channels.

#### Usage
```
MODE #channel +v <nickname>    # Give voice
MODE #channel -v <nickname>    # Remove voice
```

#### Testing
1. Give voice to user:
```
MODE #testchannel +v user1
```

2. Remove voice:
```
MODE #testchannel -v user1
```

### 👑 Operator Mode (+o)
Gives channel operator privileges.

#### Usage
```
MODE #channel +o <nickname>    # Make operator
MODE #channel -o <nickname>    # Remove operator
```

#### Testing
1. Make user operator:
```
MODE #testchannel +o user1
```

2. New operator uses privileges:
```
MODE #testchannel +v user2
```

3. Remove operator status:
```
MODE #testchannel -o user1
```

## ⚠️ Error Codes
| Code | Description |
|------|-------------|
| 001 | Welcome message |
| 331 | No topic is set |
| 332 | Channel topic |
| 353 | NAMES reply |
| 366 | End of NAMES list |
| 401 | No such nick/channel |
| 403 | No such channel |
| 404 | Cannot send to channel |
| 431 | No nickname given |
| 432 | Erroneous nickname |
| 433 | Nickname already in use |
| 442 | Not on channel |
| 451 | Not registered |
| 461 | Not enough parameters |
| 462 | Already registered |
| 464 | Password incorrect |
| 471 | Cannot join channel (+l) - channel is full |
| 473 | Cannot join channel (+i) - invite only |
| 474 | Cannot join channel (+b) - you are banned |
| 475 | Cannot join channel (+k) - bad key |
| 482 | Not channel operator |

## 📁 Project Structure
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
│   └── Command/
│       └── CommandHandler.cpp
├── include/
│   ├── Server.hpp
│   ├── Client.hpp
│   ├── Channel.hpp
│   ├── CommandHandler.hpp
│   └── common.hpp
└── Makefile
```

## 🧪 Testing

### Basic Testing
1. Start the server:
```bash
./ircserv 6667 serverpassword
```

2. Connect multiple clients using netcat:
```bash
# Terminal 2 - First client
nc localhost 6667

# Terminal 3 - Second client
nc localhost 6667

# Terminal 4 - Third client
nc localhost 6667
```

### Authentication Testing
```bash
# Connect and authenticate
PASS serverpassword
NICK john
USER john 0 * :John Doe

# Expected response:
# :server 001 john :Welcome to the IRC server john!
```

### Channel Operations Testing
```bash
# Create and join a channel
JOIN #testchannel

# Send a message to the channel
PRIVMSG #testchannel :Hello everyone!

# Set channel topic
TOPIC #testchannel :Welcome to our test channel

# List channel members
NAMES #testchannel

# Leave channel
PART #testchannel :Goodbye!
```

### Private Messaging Testing
```bash
# Send private message
PRIVMSG alice :Hey, how are you?

# Notice message
NOTICE bob :Important message
```

### Channel Modes Testing
```bash
# Set channel as invite-only
MODE #testchannel +i

# Set channel password
MODE #testchannel +k secretpass

# Set user limit
MODE #testchannel +l 10

# Give operator status
MODE #testchannel +o alice

# Ban a user
MODE #testchannel +b bob

# View channel modes
MODE #testchannel
```

### Error Handling Testing
```bash
# Wrong password
PASS wrongpassword
# Expected: Error 464 - Password incorrect

# Join non-existent channel
JOIN #nonexistent
# Expected: Error 403 - No such channel

# Message to non-existent user
PRIVMSG ghost :Hello
# Expected: Error 401 - No such nick/channel

# Using commands before registration
JOIN #channel
# Expected: Error 451 - Not registered
```

### Full Session Example
```bash
# Terminal 1 (Server)
./ircserv 6667 mypassword

# Terminal 2 (Alice)
nc localhost 6667
PASS mypassword
NICK alice
USER alice 0 * :Alice Smith
JOIN #general
PRIVMSG #general :Hello everyone!

# Terminal 3 (Bob)
nc localhost 6667
PASS mypassword
NICK bob
USER bob 0 * :Bob Johnson
JOIN #general
PRIVMSG #general :Hi Alice!
PRIVMSG alice :Private message to Alice

# Terminal 4 (Charlie)
nc localhost 6667
PASS mypassword
NICK charlie
USER charlie 0 * :Charlie Brown
JOIN #general
MODE #general +o charlie
TOPIC #general :Welcome to our IRC server!
```

