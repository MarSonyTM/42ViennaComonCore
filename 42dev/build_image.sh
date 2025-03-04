#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

echo "Building 42school Docker image..."
docker build -t 42school -f $SCRIPT_DIR/Dockerfile.42school $SCRIPT_DIR

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "✅ 42school Docker image built successfully!"
    echo "You can now use '42school' command from anywhere to start the 42 school environment."
    echo "Usage: 42school"
    echo "This will start a container with the current directory mounted to /app."
else
    echo "❌ Build failed. Please check the error messages."
fi 