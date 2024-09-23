# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 12:45:41 by mafurnic          #+#    #+#              #
#    Updated: 2024/09/23 12:35:43 by mafurnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = phonebook
CC = c++
Flags = -Wall -Wextra -Werror -std=c++98
SRC =  main.cpp Contact.cpp PhoneBook.cpp
all: $(NAME) 

$(NAME): $(SRC)                          
	$(CC) $(Flags) $(SRC) -o $(NAME)      

%.o: %.cpp 							  
	$(CC) $(Flags) -c $< -o $@        

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re