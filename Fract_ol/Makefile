# Project Configuration
PROJECT_NAME := fractol
COMPILER     := cc
FLAGS        := -Wall -Wextra -Werror
MLX_LIBS     := -L minilibx-linux -lmlx -lm -lXext -lX11
CLEANUP_CMD  := rm -rf
LIBFT_PATH   := Libft/libft.a

# Directory Paths
OBJECTS_PATH := obj/
SOURCES_PATH := srcs/

# Source and Object Files
SOURCE_FILES := main.c initialize_graphics.c check_args.c create_img.c fractal_mandelbrot.c ft_handle_error.c \
                hooks_handler.c fractal_julia.c ft_zoom.c fractal_burningship.c ft_color.c ft_color_ship.c ft_isvalidfloat.c
OBJECTS      := $(SOURCE_FILES:%.c=$(OBJECTS_PATH)%.o)

# Console Output Colors
COLOR_RED    := \033[0;91m
COLOR_GREEN  := \033[0;92m
COLOR_YELLOW := \033[0;93m
COLOR_BLUE  := \033[0;94m

# Compilation Rules
.PHONY: all library clean full_clean recompile

all: library $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	@echo "$(COLOR_YELLOW)Building $(PROJECT_NAME)$(COLOR_WHITE)"
	@$(COMPILER) $(FLAGS) $(OBJECTS) $(MLX_LIBS) $(LIBFT_PATH) -o $(PROJECT_NAME)
	@echo "$(COLOR_GREEN)$(PROJECT_NAME) compiled successfully.$(COLOR_WHITE)"

$(OBJECTS_PATH)%.o: $(SOURCES_PATH)%.c
	@mkdir -p $(@D)
	@echo "$(COLOR_GREEN)Compiling:$(COLOR_WHITE) $<"
	@$(COMPILER) $(FLAGS) -c $< -o $@

library:
	@echo "$(COLOR_YELLOW)Compiling libft$(COLOR_WHITE)"
	@$(MAKE) -C Libft

clean:
	@echo "$(COLOR_RED)Removing object files...$(COLOR_WHITE)"
	@$(CLEANUP_CMD) $(OBJECTS)
	@$(MAKE) clean -C Libft

fclean: clean
	@echo "$(COLOR_RED)Removing executable and object files...$(COLOR_WHITE)"
	@$(CLEANUP_CMD) $(PROJECT_NAME) $(OBJECTS_PATH)
	@$(MAKE) fclean -C Libft

recompile: full_clean all
re: fclean all
