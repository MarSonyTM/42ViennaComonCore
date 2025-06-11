FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update and install essential packages
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-10 \
    g++-10 \
    gdb \
    make \
    git \
    vim \
    valgrind \
    pkg-config \
    libssl-dev \
    zlib1g-dev \
    curl \
    wget \
    zsh \
    && rm -rf /var/lib/apt/lists/*

# Set GCC 10 as default
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 100

# Set up zsh as default shell (matching school environment)
RUN chsh -s /usr/bin/zsh root

# Create a non-root user
RUN useradd -m -s /usr/bin/zsh student

# Set working directory
WORKDIR /home/student/project

# Switch to non-root user
USER student

# Set environment variables
ENV USER=student \
    HOME=/home/student

# Command to run when container starts
CMD ["zsh"] 