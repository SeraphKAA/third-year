import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import sympy as sp
from tkinter import *

def plot(u, con, res):
    x, y = sp.symbols('x y')
    formula = eval(u)
    formula2 = eval(con)

    f = sp.lambdify((x, y), formula)
    f2 = sp.lambdify((x, y), formula2)

    x1 = np.linspace(-5, 5, 100)
    y1 = np.linspace(-5, 5, 100)
    X, Y = np.meshgrid(x1, y1)

    Z = f(X, Y)
    Z2 = f2(X, Y)


    fig = plt.figure()
    ax = fig.add_subplot(111, projection = '3d')
    ax.plot_surface(X, Y, Z, alpha=0.5)
    ax.plot_surface(X, Y, Z2, alpha=0.5)

    ress = res.values(); res1 = []
    for i in ress: res1.append(i)
    ax.scatter(res1[0], res1[1], res1[2], color='r', s=50)

    plt.show()

