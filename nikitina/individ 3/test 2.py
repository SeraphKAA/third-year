from sympy import *
import matplotlib.pyplot as plt
import numpy as np


x, y, lam = symbols("x y lam")

def extremes_func():

    t1 = input("Введите функцию: ")
    t2 = input("Введите условие: ")
    u, f = simplify(t1, evaluate=False), simplify(t2, evaluate=False)
    L = u + lam * f
    Lx = diff(L, x)
    Ly = diff(L, y)
    variables = solve([Lx, Ly, f], [x, y, lam])
    M = {x: variables[x], y: variables[y]}

    Lxx = diff(Lx, x)
    Lyy = diff(Ly, y)
    Lxy = diff(Lx, y)
    fx, fy = diff(f, x), diff(f, y)
    delta = -(Matrix([[0, fx, fy], [fx, Lxx, Lxy], [fy, Lxy, Lyy]]).det())
    print("дельта =",delta)
    u_res = u.subs([(x, M[x]), (y, M[y])])
    if delta > 0:
        print(f"Условный минимум {str(float(u_res))} в точке ({str((M[x]))}, {str((M[y]))})")
    elif delta < 0:
        print(f"Условный максимум {str(float(u_res))} в точке ({str((M[x]))}, {str((M[y]))})")
    else:
        print(f"Нет условного экстремума")
        return
    plot_suface(float(M[x]), float(M[y]), u, f)


def plot_suface(px, py, equation, con):
    equation_lambda = lambdify((x, y), equation)
    con_lambda = lambdify((x, y), con)
    x_vals = np.linspace(-10, 10, 100)
    y_vals = np.linspace(-10, 10, 100)
    X, Y = np.meshgrid(x_vals, y_vals)
    Z = equation_lambda(X, Y)
    Z1 = con_lambda(X, Y)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(X, Y, Z, cmap='inferno_r',alpha = 0.5)
    ax.plot_surface(X, Y, Z1)
    point_x = px
    point_y = py
    point_z = equation_lambda(point_x, point_y)
    ax.scatter(point_x, point_y, point_z, color='red')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    plt.show()



extremes_func()