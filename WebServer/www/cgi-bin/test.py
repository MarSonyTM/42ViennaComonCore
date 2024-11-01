#!/usr/bin/env python3
import os
import sys

print("Content-Type: text/html\r\n\r")
print("<h1>Python CGI Test</h1>")
print("<p>Method:", os.environ.get('REQUEST_METHOD', ''), "</p>")
print("<p>Query String:", os.environ.get('QUERY_STRING', ''), "</p>")
