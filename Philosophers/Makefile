# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 13:38:05 by mafurnic          #+#    #+#              #
#    Updated: 2024/01/05 12:24:50 by mafurnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 # Project Name and Compiler Settings
NAME := philo
COMPILER     := cc
FLAGS        := -Wall -Wextra -Werror  -pthread 
CLEANUP_CMD  := rm -rf

# Directory Paths
OBJECTS_PATH := obj/
SOURCES_PATH := src/

# Source and Object Files
SOURCE_FILES := main.c utils.c initialize.c threads.c monitoring.c routine_actions.c check_arguments.c
OBJECTS      := $(SOURCE_FILES:%.c=$(OBJECTS_PATH)%.o)

# Console Output Colors
COLOR_RED    := \033[0;91m
COLOR_GREEN  := \033[0;92m
COLOR_YELLOW := \033[0;93m
COLOR_BLUE   := \033[0;94m
COLOR_WHITE  := \033[0;97m

# Build the Project
all: $(NAME)

# Linking the Program
$(NAME): $(OBJECTS)
	@echo "$(COLOR_YELLOW)Building $(NAME)$(COLOR_WHITE)"
	@$(COMPILER) $(FLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(COLOR_GREEN)$(NAME) compiled successfully.$(COLOR_WHITE)"

# Compiling Source Files
$(OBJECTS_PATH)%.o: $(SOURCES_PATH)%.c
	@mkdir -p $(@D)
	@echo "$(COLOR_GREEN)Compiling:$(COLOR_WHITE) $<"
	@$(COMPILER) $(FLAGS) -c $< -o $@

# Cleaning Up Object Files
clean:
	@echo "$(COLOR_RED)Removing object files and directory...$(COLOR_WHITE)"
	@$(CLEANUP_CMD) $(OBJECTS)
	@$(CLEANUP_CMD) $(OBJECTS_PATH)

# Full Clean-Up
fclean: clean
	@echo "$(COLOR_RED)Removing executable...$(COLOR_WHITE)"
	@$(CLEANUP_CMD) $(NAME)

# Phony Targets
.PHONY: all clean fclean re 

# Recompile the Projects
re: fclean all