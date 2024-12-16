FROM --platform=linux/arm64 ubuntu:20.04

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages for 42 projects
RUN apt-get update && apt-get install -y \
    build-essential \
    make \
    g++ \
    gcc \
    gdb \
    valgrind \
    git \
    vim \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Default command
CMD ["/bin/bash"] 