#!/bin/bash

# Colors
GREEN='\033[0;32m'
NC='\033[0m'

echo -e "${GREEN}Setting up evaluation environment...${NC}"

# 1. Create directory structure
mkdir -p www/{cgi-bin,uploads,errors,test}

# 2. Create test files
# Index file
cat > www/index.html << 'EOF'
<!DOCTYPE html>
<html>
<head><title>WebServ Test</title></head>
<body>
    <h1>Welcome to WebServ</h1>
    <p>This is a test page for subject requirements.</p>
</body>
</html>
EOF

# Error pages
cat > www/errors/404.html << 'EOF'
<!DOCTYPE html>
<html>
<head><title>404 Not Found</title></head>
<body><h1>Custom 404 - Page Not Found</h1></body>
</html>
EOF

cat > www/errors/500.html << 'EOF'
<!DOCTYPE html>
<html>
<head><title>500 Error</title></head>
<body><h1>Custom 500 - Internal Server Error</h1></body>
</html>
EOF

# CGI test script
cat > www/cgi-bin/test.php << 'EOF'
<?php
header("Content-Type: text/plain");
echo "CGI Test Successful\n";
echo "Method: " . $_SERVER['REQUEST_METHOD'] . "\n";
echo "Query: " . $_SERVER['QUERY_STRING'] . "\n";
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    echo "POST Data: " . file_get_contents('php://input') . "\n";
}
?>
EOF

# Test files for different servers
mkdir -p www/test
cat > www/test/index.html << 'EOF'
<!DOCTYPE html>
<html>
<head><title>Test Server</title></head>
<body><h1>This is the test server on port 8081</h1></body>
</html>
EOF

# Set permissions
chmod 755 www/cgi-bin
chmod 755 www/cgi-bin/test.php
chmod 755 www/uploads

echo -e "${GREEN}Environment setup complete!${NC}" 