 # **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 09:35:14 by mafurnic          #+#    #+#              #
#    Updated: 2024/10/29 09:36:58 by mafurnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name and Compiler Settings
NAME := Bureaucrat
COMPILER := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
CLEANUP := rm -rf

# Directory Paths
OBJECTS_PATH := obj/
INCLUDES := -I inc

# Source and Object Files
SOURCE_FILES := main.cpp Bureaucrat.cpp

OBJECTS := $(SOURCE_FILES:%.cpp=$(OBJECTS_PATH)%.o)

# Build the Project
all: $(NAME)

# Linking the Program
$(NAME): $(OBJECTS)
	@$(COMPILER) $(CXXFLAGS) $(OBJECTS) -o $(NAME)
	@echo "linking successful - executable $(NAME) created"

# Compiling Source Files
$(OBJECTS_PATH)%.o: %.cpp
	@mkdir -p $(@D)
	@$(COMPILER) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$< compiled successfully"

# Cleaning Up Object Files
clean:
	@$(CLEANUP) $(OBJECTS)
	@$(CLEANUP) $(OBJECTS_PATH)
	@echo "object cleanup completed"

# Full Clean-Up
fclean: clean
	@$(CLEANUP) $(NAME)
	@echo "cleanup completed"

# Recompile the Projects
re: fclean all
	@echo "recompilation completed"

# Phony Targets
.PHONY: all clean fclean re