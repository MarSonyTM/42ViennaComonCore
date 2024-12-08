# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 09:35:14 by mafurnic          #+#    #+#              #
#    Updated: 2024/11/06 13:53:40 by marianfurni      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name and Compiler Settings
NAME :=  Identify
COMPILER := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
CLEANUP := rm -rf

# Directory Paths
OBJECTS_PATH := obj/

# Source and Object Files
SOURCE_FILES := main.cpp Base.cpp

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