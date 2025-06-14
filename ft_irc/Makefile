NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I include

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/Server/Server.cpp \
       $(SRC_DIR)/Channel/Channel.cpp \
       $(SRC_DIR)/Client/Client.cpp \
       $(SRC_DIR)/Command/CommandHandler.cpp \
       $(SRC_DIR)/Utils/Logger.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re 