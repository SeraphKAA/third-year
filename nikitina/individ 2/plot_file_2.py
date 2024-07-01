import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from tkinter import *
from tkinter import scrolledtext

def plot(fxy, res):
    X = np.linspace(-5, 5, 100)
    Y = np.linspace(-5, 5, 100)
    X, Y = np.meshgrid(X, Y)
    Z = fxy(X, Y)
        
    fig = plt.figure()
    ax = fig.add_subplot(111, projection = '3d')
    ax.plot_surface(X, Y, Z)



    count = 0
    for i in res:
        count += 1
        ax.scatter(i[0][0], i[0][1], i[1], color='r', s=50)
        ax.text(i[0][0], i[0][1], i[1], f"{count}")

    plt.show()


def print_res(res):
    tk = Tk()
    tk.geometry("400x250")
    tk.title("значения точек экстремумов")

    scr_txt = scrolledtext.ScrolledText(tk, wrap = WORD, width = 40, height = 10, font = ("Times New Roman", 14))
    scr_txt.grid(column = 0, pady = 10, padx = 10)
    text = ""
    for i in res:
        text += str(i[0][0]) + " | " + str(i[0][1]) + " | " + str(i[1]) + '\n'

    scr_txt.insert(INSERT, "x | y | значение u(x, y)\n"  + text)
                           
    tk.mainloop()