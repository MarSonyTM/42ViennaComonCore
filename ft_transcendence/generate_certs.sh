#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}🔒 Generating SSL certificates...${NC}\n"

# Create certificates directory
mkdir -p ./certs
cd ./certs

# Generate CA private key and certificate
echo "Generating CA certificate..."
openssl genrsa -out ca.key 4096
openssl req -x509 -new -nodes -key ca.key -sha256 -days 365 -out ca.crt \
    -subj "/C=AT/ST=Vienna/L=Vienna/O=42Vienna/OU=CommonCore/CN=ft_transcendence CA"

# Generate server private key
echo "Generating server private key..."
openssl genrsa -out server.key 2048

# Create server certificate signing request (CSR)
echo "Creating server CSR..."
openssl req -new -key server.key -out server.csr \
    -subj "/C=AT/ST=Vienna/L=Vienna/O=42Vienna/OU=CommonCore/CN=localhost"

# Create server certificate configuration
cat > server.ext << EOF
authorityKeyIdentifier=keyid,issuer
basicConstraints=CA:FALSE
keyUsage = digitalSignature, nonRepudiation, keyEncipherment, dataEncipherment
subjectAltName = @alt_names

[alt_names]
DNS.1 = localhost
DNS.2 = frontend
DNS.3 = backend
IP.1 = 127.0.0.1
EOF

# Generate server certificate
echo "Generating server certificate..."
openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial \
    -out server.crt -days 365 -sha256 -extfile server.ext

# Clean up intermediate files
rm server.csr server.ext ca.srl

# Set appropriate permissions
chmod 644 server.crt ca.crt
chmod 600 server.key ca.key

# Verify the certificates
echo -e "\nVerifying certificates..."
openssl verify -CAfile ca.crt server.crt

if [ $? -eq 0 ]; then
    echo -e "\n${GREEN}✅ SSL certificates generated successfully!${NC}"
    echo "Generated files:"
    echo "- ca.key: Certificate Authority private key"
    echo "- ca.crt: Certificate Authority certificate"
    echo "- server.key: Server private key"
    echo "- server.crt: Server certificate"
else
    echo -e "\n${RED}❌ Certificate verification failed${NC}"
    exit 1
fi

