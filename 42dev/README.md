# 42 School Development Environment

This setup creates a development environment that mimics the 42 school environment with full sudo access and Docker integration.

## Quick Setup (Docker Image)

1. Build the Docker image:
   ```bash
   cd 42dev
   ./build_image.sh
   ```

2. Once the image is built, you can use the 42school command from anywhere:
   ```bash
   42school
   ```

   This will:
   - Start a container with the 42school image
   - Mount your current directory to `/app` in the container
   - Provide a bash shell with sudo privileges

## Features

- Full sudo access (no password required)
- Docker with all necessary permissions
- Shared volumes with the host for easy file editing
- Access your project files at `/app` inside the container

## Using the Environment

Inside the container:

1. You have sudo access (no password required)
   ```bash
   sudo apt-get update
   ```

2. Your host files are available in the container
   ```bash
   ls /app
   ```

3. Any changes you make to files in `/app` from either the host or the container will be reflected in both places.

## Key Benefits

1. Full sudo access for installing any required packages
2. Works from any directory - just run `42school` and your current directory is available
3. Docker-in-Docker for running containerized applications
4. Seamless file editing between host and container

## Notes

- The 42school command is actually a Docker container that is aliased to simplify usage
- The container is ephemeral (data outside of mounted volumes will be lost)
- You can install additional software inside the container as needed

## Manual Setup (without installing the command)

1. Make sure you have Docker Desktop installed on your MacBook

2. Navigate to the 42dev directory:
   ```bash
   cd 42dev
   ```

3. Build and start the development environment:
   ```bash
   docker compose up -d
   ```

4. Enter the development container:
   ```bash
   docker exec -it 42dev bash
   ```

## Stopping the Environment

From your host:
```bash
42school stop
```

Or manually:
```bash
cd 42dev
docker compose down
``` 