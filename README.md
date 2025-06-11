# 42 School Docker Environment

This Dockerfile creates a development environment that matches the 42 school environment specifications.

## System Specifications
- Ubuntu 22.04.5 LTS
- GCC 10.5.0
- Zsh shell
- Common development tools (make, gdb, valgrind, etc.)

## Building the Docker Image

```bash
# Build the image
docker build -t 42school-env .
```

## Running the Container

### Basic Usage
```bash
# Run the container with current directory mounted
docker run -it -v $(pwd):/home/student/project 42school-env
```

### Advanced Usage (with resource limits)
```bash
# Run with memory limits (8GB in this example)
docker run -it \
    --memory=8g \
    --memory-swap=12g \
    -v $(pwd):/home/student/project \
    42school-env
```

## Features
- Ubuntu 22.04.5 LTS (matching school environment)
- GCC 10.5.0
- Essential development tools
- Zsh shell
- Non-root user 'student'
- Valgrind for memory checking
- GDB for debugging

## Notes
- The container uses a non-root user 'student' for safety
- Your current directory is mounted at /home/student/project
- All changes in the mounted directory persist after container shutdown
- The environment closely mirrors the 42 school setup 