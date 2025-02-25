# Colors for prettier output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Project name
NAME = inception

# Docker Compose file
COMPOSE_FILE = srcs/docker-compose.yml

# Environment file
ENV_FILE = srcs/.env
ENV_EXAMPLE = srcs/.env.example
ENV_SETUP = srcs/setup_env.sh

# Get username and set paths
USER_NAME = $(shell whoami)
ifeq ($(shell uname),Darwin)
    DATA_PATH = /Users/$(USER_NAME)/data
else
    DATA_PATH = /home/$(USER_NAME)/data
endif

# Export variables for docker-compose
export DATA_PATH
export PWD = $(shell pwd)

# Domain name
DOMAIN = $(USER_NAME).42.fr

# All required directories
DIRS = $(DATA_PATH)/wordpress \
       $(DATA_PATH)/mariadb \
       secrets

# Basic commands
all: env setup up

# Check and setup environment file
env:
	@if [ ! -f $(ENV_FILE) ] || [ ! -f secrets/db_root_password.txt ]; then \
		printf "$(GREEN)Setting up environment file...$(RESET)\n"; \
		chmod +x $(ENV_SETUP); \
		cd srcs && ./setup_env.sh; \
	fi

# Create necessary directories and setup environment
setup: $(DIRS) hosts
	@printf "$(GREEN)Setting up directories...$(RESET)\n"
ifeq ($(shell uname),Darwin)
	@chown -R $(USER_NAME):staff $(DATA_PATH)
	@chmod -R 755 $(DATA_PATH)
else
	@sudo chown -R $(USER_NAME):$(USER_NAME) $(DATA_PATH)
	@sudo chmod -R 755 $(DATA_PATH)
endif
	@chmod 700 secrets

$(DIRS):
	@mkdir -p $@
	@printf "$(GREEN)Created $@$(RESET)\n"

# Configure hosts file
hosts:
	@printf "$(GREEN)Configuring hosts file...$(RESET)\n"
	@if ! grep -q "$(DOMAIN)" /etc/hosts; then \
		sudo sh -c 'echo "127.0.0.1 $(DOMAIN)" >> /etc/hosts'; \
		printf "$(GREEN)Added $(DOMAIN) to hosts file$(RESET)\n"; \
	else \
		printf "$(GREEN)$(DOMAIN) already in hosts file$(RESET)\n"; \
	fi

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
	@if [ -d "$(DATA_PATH)" ]; then \
		sudo rm -rf $(DATA_PATH); \
		printf "$(GREEN)Removed $(DATA_PATH)$(RESET)\n"; \
	fi
	@if [ -d "secrets" ]; then \
		sudo rm -rf secrets; \
		printf "$(GREEN)Removed secrets directory$(RESET)\n"; \
	fi
	@if [ -f "$(ENV_FILE)" ]; then \
		rm -f $(ENV_FILE); \
		printf "$(GREEN)Removed environment file$(RESET)\n"; \
	fi

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

.PHONY: all env setup up down clean fclean re status logs shell
