#!/bin/bash

echo "🔍 Testing Docker containers..."

# Build the containers
echo "Building containers..."
docker-compose build

if [ $? -ne 0 ]; then
    echo "❌ Container build failed"
    exit 1
fi
echo "✅ Containers built successfully"

# Start the containers in detached mode
echo "Starting containers..."
docker-compose up -d

if [ $? -ne 0 ]; then
    echo "❌ Container startup failed"
    exit 1
fi
echo "✅ Containers started successfully"

# Wait for services to be ready
echo "Waiting for services to be ready..."
sleep 10

# Test backend health endpoint
echo "Testing backend health endpoint..."
curl -s http://localhost:3001/health | grep "ok" > /dev/null
if [ $? -ne 0 ]; then
    echo "❌ Backend health check failed"
    docker-compose logs backend
    docker-compose down
    exit 1
fi
echo "✅ Backend health check passed"

# Test frontend accessibility
echo "Testing frontend accessibility..."
curl -s http://localhost:3000 | grep "ft_transcendence" > /dev/null
if [ $? -ne 0 ]; then
    echo "❌ Frontend accessibility check failed"
    docker-compose logs frontend
    docker-compose down
    exit 1
fi
echo "✅ Frontend accessibility check passed"

echo "✨ Container tests completed successfully!"

# Keep containers running for manual testing
echo "Containers are running and ready for manual testing."
echo "Use 'docker-compose down' to stop them when finished."
