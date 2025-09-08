# Base image
FROM node:20-alpine

# Set working directory
WORKDIR /app

# Install SQLite and build dependencies
RUN apk add --no-cache python3 make g++ sqlite

# Copy package files
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy project files
COPY . .

# Build TypeScript
RUN npm run build

# Expose port
EXPOSE 3001

# Start command
CMD ["npm", "run", "dev"]
