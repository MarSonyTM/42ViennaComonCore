FROM ubuntu:22.04

# Install required packages
RUN apt-get update && apt-get install -y \
    docker.io \
    docker-compose \
    curl \
    make \
    git \
    && rm -rf /var/lib/apt/lists/*

# Create a non-root user to mimic 42 environment
ARG USERNAME=dev42
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && mkdir -p /home/$USERNAME/data \
    && chown -R $USERNAME:$USERNAME /home/$USERNAME

# Setup Docker in rootless mode
RUN curl -fsSL https://get.docker.com/rootless | sh

# Configure unprivileged ports
RUN echo "net.ipv4.ip_unprivileged_port_start=1024" >> /etc/sysctl.conf

# Switch to the non-root user
USER $USERNAME
WORKDIR /home/$USERNAME

# Set environment variables
ENV XDG_RUNTIME_DIR=/home/$USERNAME/.docker/run
ENV DOCKER_HOST=unix:///home/$USERNAME/.docker/run/docker.sock
ENV PATH=/home/$USERNAME/bin:$PATH

CMD ["bash"] 