 # **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 13:32:47 by mafurnic          #+#    #+#              #
#    Updated: 2024/09/26 13:43:24 by mafurnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = zombieHorde
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS =  main.cpp Zombie.cpp zombieHorde.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
