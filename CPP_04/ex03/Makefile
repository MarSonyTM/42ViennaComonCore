# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 12:35:59 by mafurnic          #+#    #+#              #
#    Updated: 2024/10/17 12:48:45 by mafurnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Interfaces
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = 
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
