<?php
header("Content-Type: text/html");
echo "\r\n";  // Important: Separate headers from body
echo "<pre>\n";
echo "CGI Test Successful\n";

// For GET requests
if (isset($_SERVER['QUERY_STRING']) && !empty($_SERVER['QUERY_STRING'])) {
    echo "Query: " . $_SERVER['QUERY_STRING'] . "\n";
}

// For POST requests
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $input = file_get_contents('php://input');
    if (!empty($input)) {
        echo "POST Data: " . $input . "\n";
    }
}

// Debug information
echo "\nDebug Info:\n";
echo "REQUEST_METHOD: " . $_SERVER['REQUEST_METHOD'] . "\n";
echo "QUERY_STRING: " . (isset($_SERVER['QUERY_STRING']) ? $_SERVER['QUERY_STRING'] : 'NOT SET') . "\n";
echo "CONTENT_LENGTH: " . (isset($_SERVER['CONTENT_LENGTH']) ? $_SERVER['CONTENT_LENGTH'] : 'NOT SET') . "\n";
echo "SCRIPT_FILENAME: " . (isset($_SERVER['SCRIPT_FILENAME']) ? $_SERVER['SCRIPT_FILENAME'] : 'NOT SET') . "\n";
echo "</pre>";
?>
