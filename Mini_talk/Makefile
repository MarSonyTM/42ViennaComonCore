CC = cc
CFLAGS = -Wall -Wextra -Werror

# Paths
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SERVER_SRC = server.c
CLIENT_SRC = client.c

# Object files
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Executable names
SERVER = server
CLIENT = client

# Compile all
all: $(LIBFT) $(SERVER) $(CLIENT)

# Server program
$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ) -L$(LIBFT_DIR) -lft

# Client program
$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ) -L$(LIBFT_DIR) -lft

# libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Compiling .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	make -C $(LIBFT_DIR) clean

# Clean everything
fclean: clean
	rm -f $(SERVER) $(CLIENT)
	make -C $(LIBFT_DIR) fclean

# Re-make everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
