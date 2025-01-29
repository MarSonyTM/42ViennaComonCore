# Colors for prettier output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Project name
NAME = inception

# Docker Compose file
COMPOSE_FILE = srcs/docker-compose.yml

# Detect OS and set paths accordingly
ifeq ($(shell uname),Darwin)
    DATA_PATH = /Users/$(USER)/data
else
    DATA_PATH = /home/$(USER)/data
endif

# All required directories
DIRS = $(DATA_PATH)/wordpress \
       $(DATA_PATH)/mariadb

# Basic commands
all: setup up

# Create necessary directories and setup environment
setup: $(DIRS)
	@printf "$(GREEN)Setting up directories...$(RESET)\n"
ifeq ($(shell uname),Darwin)
	@chown -R $(USER):staff $(DATA_PATH)
else
	@chown -R $(USER):$(USER) $(DATA_PATH)
endif

$(DIRS):
	@mkdir -p $@
	@printf "$(GREEN)Created $@$(RESET)\n"

# Start containers
up:
	@printf "$(GREEN)Starting containers...$(RESET)\n"
	@docker compose -f $(COMPOSE_FILE) up -d --build

# Stop containers
down:
	@printf "$(RED)Stopping containers...$(RESET)\n"
	@docker compose -f $(COMPOSE_FILE) down

# Stop and remove all containers, networks, and volumes
clean: down
	@printf "$(RED)Cleaning up...$(RESET)\n"
	@docker compose -f $(COMPOSE_FILE) down -v
	@docker system prune -af

# Remove all data directories
fclean: clean
	@printf "$(RED)Full cleanup...$(RESET)\n"
	@rm -rf $(DATA_PATH)

# Restart all services
re: fclean all

# Show container status
status:
	@docker compose -f $(COMPOSE_FILE) ps
	@echo "\nVolumes:"
	@docker volume ls
	@echo "\nNetworks:"
	@docker network ls

# Show container logs
logs:
	@docker compose -f $(COMPOSE_FILE) logs

# Enter container shell (usage: make shell service=wordpress)
shell:
	@docker compose -f $(COMPOSE_FILE) exec $(service) sh

.PHONY: all setup up down clean fclean re status logs shell
