# Base image
FROM node:20-alpine

# Set working directory
WORKDIR /app

# Install dependencies
RUN apk add --no-cache python3 make g++ sqlite

# Copy package files
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy project files
COPY . .

# Build TypeScript
RUN npm run build

# Expose ports
EXPOSE 3000 3001

# Start command
CMD ["npm", "run", "start"]
