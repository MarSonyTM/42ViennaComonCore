from PIL import Image, ImageTk
import tkinter as tk

def show_image_fullscreen(image_path):
    root = tk.Tk()
    root.attributes('-fullscreen', True)
    root.bind('<Escape>', lambda e: root.destroy())

    img = Image.open(image_path)
    img = ImageTk.PhotoImage(img)

    panel = tk.Label(root, image=img)
    panel.pack(side='top', fill='both', expand='yes')

    root.mainloop()

show_image_fullscreen('screen.jpg')
