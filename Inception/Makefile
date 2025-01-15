NAME = inception

all: up

up:
	docker-compose -f srcs/docker-compose.yml up --build -d

down:
	docker-compose -f srcs/docker-compose.yml down

stop:
	docker-compose -f srcs/docker-compose.yml stop

start:
	docker-compose -f srcs/docker-compose.yml start

restart:
	docker-compose -f srcs/docker-compose.yml restart

clean: down
	docker system prune -a

fclean: clean
	docker volume rm $$(docker volume ls -q)
	sudo rm -rf /home/$(USER)/data/wordpress/*
	sudo rm -rf /home/$(USER)/data/mariadb/*

re: fclean all

.PHONY: all up down stop start restart clean fclean re 