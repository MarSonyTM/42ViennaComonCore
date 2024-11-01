#!/usr/bin/php-cgi
<?php
echo "Content-Type: text/html\r\n\r\n";
echo "<h1>CGI Test</h1>\n";
echo "<p>Method: " . $_SERVER['REQUEST_METHOD'] . "</p>\n";
echo "<p>Query String: " . $_SERVER['QUERY_STRING'] . "</p>\n";
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    echo "<p>POST Data:</p>\n<pre>";
    print_r($_POST);
    echo "</pre>\n";
}
?>
