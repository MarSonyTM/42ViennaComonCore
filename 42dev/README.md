# 42 Development Environment

This setup creates a development environment that mimics the 42 school environment for testing your Inception project. It includes:

- Rootless Docker (no sudo access)
- Port restrictions (can't use privileged ports < 1024)
- Similar user permissions and limitations

## Setup on MacBook

1. Make sure you have Docker Desktop installed on your MacBook

2. Clone your Inception project and navigate to the 42dev directory:
   ```bash
   cd Inception/42dev
   ```

3. Build and start the development environment:
   ```bash
   docker compose up -d
   ```

4. Enter the development container:
   ```bash
   docker exec -it 42dev bash
   ```

5. Inside the container, your Inception project is mounted at `/home/dev42/inception`

## Testing Your Project

Inside the container:
1. Navigate to your project:
   ```bash
   cd inception
   ```

2. Run your project as normal:
   ```bash
   make
   ```

3. Access your WordPress site at:
   ```
   https://mafurnic.42.fr:8443
   ```

## Key Differences from MacBook Environment

1. No sudo access
2. Can't use port 443 (using 8443 instead)
3. Rootless Docker operation
4. Limited user permissions

## Stopping the Environment

From your MacBook:
```bash
cd Inception/42dev
docker compose down
```

## Notes

- The environment uses Docker-in-Docker to provide a similar experience to 42 school
- Your project files are mounted from your host machine, so you can edit them with your preferred editor on your MacBook
- Changes made to the project files will be immediately reflected in the container 