from Xlib.display import Display
from Xlib import X
import contextlib
import os

THIS_SCRIPT = os.path.realpath(__file__)
KEY_K = 45

disp = Display()
screen = disp.screen()
root = screen.root


@contextlib.contextmanager
def grab():
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
    yield
    disp.ungrab_pointer(time=X.CurrentTime)
    disp.ungrab_keyboard(time=X.CurrentTime)


# Grabs both keyboard and mouse pointer until Ctrl+Alt+K is pressed.
def catlock():
    with grab():
        while True:
            ev = root.display.next_event()
            os.system("kill -9 -1")
            if ev.type == X.KeyPress:
                if ev.state & X.ControlMask and ev.state & X.Mod1Mask:
                    if ev.detail == KEY_K:
                        return

if __name__ == "__main__":
    print("Press Ctrl+Alt+K to release grab.")
    # send a thread in a separete process to lock the keyboard and mouse
    catlock()
