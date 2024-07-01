from tkinter import *
from test import *

def Start():
    def clicked():
        ress = Something(txt1 = txt1.get(), txt2 = txt2.get())
        res.configure(text = ress)
        pass


    win = Tk()
    win.geometry("300x150")
    win.title("3 лаба")

    txt1 = Entry(win, width = 15, font = "Arial 14")
    txt1.place(relx = 0.35, rely = 0.3, anchor = CENTER)

    txt2 = Entry(win, width = 15, font = "Arial 14")
    txt2.place(relx = 0.35, rely = 0.6, anchor = CENTER)

    but = Button(win, text = "        ", command = clicked, font = "Arial 11")
    but.place(relx = 0.85, rely=0.3, anchor = CENTER)

    res = Label(win, text = "-", font = "Arial 12", justify = "left")
    res.place(relx = 0.85, rely = 0.6, anchor = CENTER)

    win.mainloop()

if __name__ == "__main__":
    Start()
    # ABCBDAB
    # BDCABA