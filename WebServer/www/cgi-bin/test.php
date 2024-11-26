<?php
header("Content-Type: text/plain");
echo "CGI Test Successful\n";
echo "Method: " . $_SERVER['REQUEST_METHOD'] . "\n";
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $input = file_get_contents('php://input');
    echo "POST Data: " . $input . "\n";
}
?>
