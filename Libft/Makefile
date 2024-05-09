# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 10:57:07 by mafurnic          #+#    #+#              #
#    Updated: 2023/09/25 13:11:01 by mafurnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC := cc
FLAGS := -Wall -Wextra -Werror
NAME := libft.a

# List of source and object files
SRCS := ft_atoi.c  ft_isalpha.c  ft_memchr.c  ft_memset.c  ft_strlcat.c   ft_strnstr.c	ft_tolower.c \
ft_bzero.c	ft_isascii.c  ft_memcmp.c  ft_strchr.c	ft_strlcpy.c  ft_strrchr.c	ft_toupper.c \
ft_calloc.c	ft_isdigit.c  ft_memcpy.c  ft_strdup.c	ft_strlen.c	 ft_strtrim.c  ft_itoa.c \
ft_isalnum.c  ft_isprint.c  ft_memmove.c  ft_strjoin.c  ft_strncmp.c  ft_substr.c	ft_split.c \
ft_strmapi.c  ft_striteri.c  ft_putchar_fd.c  ft_putstr_fd.c  ft_putendl_fd.c   ft_putnbr_fd.c  ft_atoi_base.c \
ft_itoa_base.c ft_putnbr_base_fd.c	ft_putnbr_unsigned_fd.c  ft_uitoa.c

OBJS := $(SRCS:.c=.o)

# Bonus source and object files

BONUS_SRCS := ft_lstnew_bonus.c  ft_lstadd_front_bonus.c  ft_lstsize_bonus.c  ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c ft_lstdelone_bonus.c  ft_lstclear_bonus.c ft_lstiter_bonus.c  ft_lstmap_bonus.c 
BONUS_OBJS := $(BONUS_SRCS:.c=.o)

# Default rule to make libft.a
all: $(NAME)

$(NAME): $(OBJS)
		ar rcs $@ $^

# Compiling every source file into its object file
%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@

bonus: $(OBJS) $(BONUS_OBJS)
		ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

# Clean rule to remove object files
clean:
		rm -f $(OBJS) $(BONUS_OBJS)

# Fclean rule to remove both object files and libft.a
fclean: clean
		rm -f $(NAME)

# Rule to recompile everything
re: fclean all

# With this setup, you can:
# - Compile all of libft by just typing 'make' or 'make all'.
# - Create test executables for specific functions, like 'make ft_strtrim'.
# - Clean object files with 'make clean'.
# - Remove both object files and libft.a with 'make fclean'.
# - Recompile everything with 'make re'.

