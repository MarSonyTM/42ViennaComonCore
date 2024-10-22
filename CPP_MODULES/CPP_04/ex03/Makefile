# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 11:14:24 by mafurnic          #+#    #+#              #
#    Updated: 2024/10/22 11:43:29 by mafurnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = AMateria
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRCS = main.cpp AMateria.cpp Ice.cpp Cure.cpp Character.cpp MateriaSource.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
