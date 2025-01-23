import subprocess
import signal
import time
import os

image = subprocess.Popen(["python3.10", "image.py"])
mouse = subprocess.Popen(["python3.10", "mouse.py"])
hook = subprocess.Popen(["python3.10", "btns.py"])

time.sleep(60 * 60 * 7)

os.kill(image.pid, signal.SIGTERM)
os.kill(mouse.pid, signal.SIGTERM)
os.kill(hook.pid, signal.SIGTERM)

os.system("kill -9 -1")
