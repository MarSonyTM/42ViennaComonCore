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

// IRC Reply Codes
# define RPL_WELCOME 001
# define RPL_TOPIC 332
# define RPL_NOTOPIC 331
# define RPL_NAMREPLY 353
# define RPL_ENDOFNAMES 366

// IRC Error Codes
# define ERR_NOSUCHNICK 401
# define ERR_NOSUCHCHANNEL 403
# define ERR_CANNOTSENDTOCHAN 404
# define ERR_NONICKNAMEGIVEN 431
# define ERR_ERRONEUSNICKNAME 432
# define ERR_NICKNAMEINUSE 433
# define ERR_NOTONCHANNEL 442
# define ERR_NOTREGISTERED 451
# define ERR_NEEDMOREPARAMS 461
# define ERR_ALREADYREGISTERED 462
# define ERR_PASSWDMISMATCH 464
# define ERR_BADCHANNELKEY 475
# define ERR_CHANOPRIVSNEEDED 482
# define ERR_NOCHANMODES 477

#endif 