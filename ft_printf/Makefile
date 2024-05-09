# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 15:56:16 by mafurnic          #+#    #+#              #
#    Updated: 2023/09/27 16:10:05 by mafurnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# The output library's name
NAME = libftprintf.a
HEADER = ft_printf.h

# List of source files
SRC = ft_printf.c handle_char.c handle_string.c handle_pointer.c handle_int.c handle_uint.c \
 handle_hex_lower.c handle_hex_upper.c handle_percent.c  handle_specifier.c

# Adding source files from Libft
LIBFT_SRC = $(addprefix $(LIBFT_DIR)/, ft_putchar_fd.c ft_putstr_fd.c ft_strlen.c ft_itoa.c ft_putnbr_base_fd.c ft_uitoa.c ft_strdup.c) # Add other source files from Libft as needed

SRC += $(LIBFT_SRC)

# List of object files 
OBJ = $(SRC:.c=.o)

# Compiler and flags
CC = cc 
CFLAGS = -Wall -Wextra -Werror 

# Directory of the Libft library
LIBFT_DIR = ./Libft

# Default rule
all: $(NAME)

# Rule to create the library
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

# Rule to compile source fs to object files
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files
clean:
	rm -f $(OBJ)

# Fclean rule to remove both object files and the library
fclean: clean 
	rm -f $(NAME)

# Rebuild everything
re: fclean all
