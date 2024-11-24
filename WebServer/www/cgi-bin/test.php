<?php
header("Content-Type: text/plain");
echo "CGI Test Successful\n";
echo "Method: " . $_SERVER['REQUEST_METHOD'] . "\n";
echo "Query: " . $_SERVER['QUERY_STRING'] . "\n";
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    echo "POST Data: " . file_get_contents('php://input') . "\n";
}
?>
