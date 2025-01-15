import subprocess
import time
import os

time.sleep(5)  # short delay for the other scripts to start normally

# Start processes in the same session group
image = subprocess.Popen(["python3.10", "image.py"], preexec_fn=os.setpgrp)
mouse = subprocess.Popen(["python3.10", "mouse.py"], preexec_fn=os.setpgrp)
hook = subprocess.Popen(["python3.10", "btns.py"], preexec_fn=os.setpgrp)

# Allow btns.py to handle termination
try:
    while True:
        time.sleep(1)  # Keep main.py alive
except KeyboardInterrupt:
    pass

