# Base image
FROM node:20-alpine

# Set working directory
WORKDIR /app

# Copy package files
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy project files
COPY . .

# Create certs directory
RUN mkdir -p /app/certs

# Build the app
RUN npm run build

# Expose ports
EXPOSE 3000 443

# Start command with HTTPS
CMD ["npm", "run", "dev"]