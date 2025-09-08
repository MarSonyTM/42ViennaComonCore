#!/bin/bash

echo "🔍 Testing ft_transcendence setup..."

# Check if Docker is installed
echo "Checking Docker installation..."
if ! command -v docker &> /dev/null; then
    echo "❌ Docker is not installed"
    exit 1
else
    echo "✅ Docker is installed"
fi

# Check if Docker Compose is installed
echo "Checking Docker Compose installation..."
if ! command -v docker-compose &> /dev/null; then
    echo "❌ Docker Compose is not installed"
    exit 1
else
    echo "✅ Docker Compose is installed"
fi

# Check if required directories exist
echo "Checking project structure..."
for dir in "frontend" "backend" "database"; do
    if [ -d "$dir" ]; then
        echo "✅ $dir directory exists"
    else
        echo "❌ $dir directory is missing"
        exit 1
    fi
done

# Check if required configuration files exist
echo "Checking configuration files..."
required_files=(
    "docker-compose.yml"
    "frontend/package.json"
    "frontend/tsconfig.json"
    "frontend/Dockerfile"
    "backend/package.json"
    "backend/tsconfig.json"
    "backend/Dockerfile"
)

for file in "${required_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ $file exists"
    else
        echo "❌ $file is missing"
        exit 1
    fi
done

echo "✨ Basic setup verification complete!"
