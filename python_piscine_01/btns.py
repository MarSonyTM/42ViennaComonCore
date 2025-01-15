from Xlib.display import Display
from Xlib import X
import contextlib
import os
import signal

# Keycodes for "a" and "i"
KEY_A = 38
KEY_I = 31

disp = Display()
screen = disp.screen()
root = screen.root

@contextlib.contextmanager
def grab():
    # Grab both pointer and keyboard
    root.grab_pointer(owner_events=True,
                      event_mask=0,
                      time=X.CurrentTime,
                      pointer_mode=X.GrabModeAsync,
                      keyboard_mode=X.GrabModeAsync,
                      confine_to=0,
                      cursor=0)
    root.grab_keyboard(owner_events=True,
                       time=X.CurrentTime,
                       pointer_mode=X.GrabModeAsync,
                       keyboard_mode=X.GrabModeAsync)
    try:
        yield
    finally:
        # Ensure the pointer and keyboard are ungrabbed
        disp.ungrab_pointer(time=X.CurrentTime)
        disp.ungrab_keyboard(time=X.CurrentTime)

def terminate_python_processes():
    print("Terminating all Python processes.")
    os.system("pkill -f python3")  # Terminate all Python3 processes
    os.system("pkill -f python")   # Terminate all Python processes

def catlock():
    with grab():  # Grab mouse and keyboard
        sequence = []  # To store pressed keys in order
        while True:
            ev = root.display.next_event()
            if ev.type == X.KeyPress:
                key_code = ev.detail
                if key_code == KEY_A:
                    sequence.append('a')
                elif key_code == KEY_I:
                    sequence.append('i')

                # Check if 'a' and then 'i' are pressed in sequence
                if sequence == ['a', 'i']:
                    print("Release detected: Stopping all processes.")
                    terminate_python_processes()
                    break  # Exit the loop to release the grab

if __name__ == "__main__":
    print("Press 'a' followed by 'i' to release grab and stop all processes.")
    catlock()

