# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 12:59:06 by mafurnic          #+#    #+#              #
#    Updated: 2023/11/29 14:08:06 by mafurnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SRCS =	srcs/checkarguments.c srcs/free_stack.c srcs/init_and_sort.c srcs/operations.c srcs/operations2.c srcs/operations3.c srcs/push_swap_main.c \
srcs/radix.c srcs/simple.c srcs/sort3.c srcs/utils1.c srcs/utils2.c

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror  -I ./include

RM = rm -rf

all: ${NAME} ${CHECK}
${NAME}: ${OBJS}
	@${MAKE} -C ./libft --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -o ${NAME}

clean: 
	@${MAKE} -C ./libft --no-print-directory clean
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}
	@${RM} ./libft/libft.a

re: fclean all
	
.PHONY: all clean fclean re
