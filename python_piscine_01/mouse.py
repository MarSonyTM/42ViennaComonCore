import pyautogui
import threading
import random
pyautogui.FAILSAFE = False
screenSize = pyautogui.size()
def oddMoveMouse():
    pyautogui.moveTo(
        0,
        screenSize[1],
        random.random() * 0.5
    )
    if random.randint(0, 10) == 0:
        pyautogui.click()
def evenMoveMouse():
    pyautogui.moveTo(
        1,
        screenSize[1],
        random.random() * 0.5
    )
def main():
    # for i in range(0, 10):
    while True:
        thread = threading.Thread(target=(oddMoveMouse if random.randint(0, 1) == 0 else evenMoveMouse))
        thread.start()
        thread.join()
main()