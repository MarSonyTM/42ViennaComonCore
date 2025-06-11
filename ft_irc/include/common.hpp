#ifndef COMMON_HPP
# define COMMON_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <cstring>
# include <cerrno>
# include <cstdlib>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <signal.h>

# define MAX_CLIENTS 100
# define BUFFER_SIZE 512
# define SERVER_NAME "ft_irc"
# define SERVER_VERSION "1.0"

#endif 