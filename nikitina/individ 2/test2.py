import sys
import matplotlib.pyplot as plt
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QLineEdit, QPushButton, \
QTableWidget, QTableWidgetItem, QScrollArea
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
from PyQt5.QtGui import *
from PyQt5.QtCore import Qt
from math import *
import numpy as np
from sympy import *


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        # Создаем графические элементы интерфейса
        self.setWindowTitle("Наибольшее и наименьшее значение")  # заголовок окна
        self.move(150, 150)  # положение окна
        self.resize(400, 200)  # размер окна

        self.lbl_func = QLabel("Функция f(x):")
        self.le_func = QLineEdit()
        self.rez_text = QLabel('<b>ОТВЕТ</b>')
        self.lblX0 = QLabel('Введите ограничения:')
        self.txtX0 = QLineEdit()
        self.txtX1 = QLineEdit()
        self.txtX2 = QLineEdit()
        self.rez_button = QPushButton("Решить")
        self.lbl_result_h1 = QLabel()
        self.lbl_result_h2 = QLabel()
        self.lbl_result_n = QLabel()
        self.lbl_result_m = QLabel()


        # Создаем макеты для размещения элементов интерфейса
        self.main_layout = QVBoxLayout()
        self.head_layout = QVBoxLayout()
        self.func_layout = QHBoxLayout()
        self.limit_layout = QHBoxLayout()

        # Добавляем элементы в левую часть экрана
        self.func_layout.addWidget(self.lbl_func)
        self.func_layout.addWidget(self.le_func)
        self.limit_layout.addWidget(self.lblX0)
        self.limit_layout.addWidget(self.txtX0)
        self.limit_layout.addWidget(self.txtX1)
        self.limit_layout.addWidget(self.txtX2)
        self.head_layout.addLayout(self.func_layout)
        self.head_layout.addLayout(self.limit_layout)
        self.head_layout.addWidget(self.rez_button)


        # Добавляем макеты в основной макет
        self.main_layout.addLayout(self.head_layout)
        self.main_layout.addWidget(self.rez_text)
        self.main_layout.addWidget(self.lbl_result_h1)
        self.main_layout.addWidget(self.lbl_result_h2)
        self.main_layout.addWidget(self.lbl_result_n)
        self.main_layout.addWidget(self.lbl_result_m)
        self.setLayout(self.main_layout)

        # Назначаем обработчики событий для кнопок
        self.rez_button.clicked.connect(self.rez)


    def rez(self):
        fun_value = []
        func_str = self.le_func.text()
        lim = [self.txtX0.text(), self.txtX1.text(), self.txtX2.text()]
        func = sympify(replace_(func_str))
        toch, changes = limitations(lim)
        oblast = builder_oblast(toch)

        toch = finding_points(func, toch)
        for variable in changes:
            temp = func.subs(variable[0][0], variable[0][1])
            toch = finding_points(temp, toch, variable[0][1])
        belong = []
        for point in toch:
            if belonging_the_area(point[0], oblast):
                belong.append(point)

        for research_point in belong:
            value = function_value(func, research_point)
            fun_value.append(value)

        x_fig = []
        y_fig = []

        x_points = []
        y_points = []

        for toch in range(len(belong)):
            if toch < 3:
                x_fig.append(belong[toch][0][0])
                y_fig.append(belong[toch][0][1])
            else:
                x_points.append(belong[toch][0][0])
                y_points.append(belong[toch][0][1])

        x_fig.append(belong[0][0][0])
        y_fig.append(belong[0][0][1])

        fig = plt.figure()
        ax1 = fig.add_subplot(1, 1, 1)
        ax1.grid()
        ax1.spines['left'].set_position('center')
        ax1.spines['bottom'].set_position('center')
        ax1.spines['top'].set_visible(False)
        ax1.spines['right'].set_visible(False)
        ax1.set_xlim(-5, 5)
        ax1.set_ylim(-5, 5)
        ax1.plot(x_fig, y_fig, color='red')
        ax1.text(x_fig[0], y_fig[0] + 0.3, 'A')
        ax1.text(x_fig[1], y_fig[1] + 0.3, 'B')
        ax1.text(x_fig[2], y_fig[2], 'C')
        ax1.scatter(x_points, y_points, color="green", marker='*')

        ax1.scatter(x_fig[0], y_fig[0], color="green", marker='*')
        ax1.scatter(x_fig[1], y_fig[1], color="green", marker='*')
        ax1.scatter(x_fig[2], y_fig[2], color="green", marker='*')


        plt.show()
        self.lbl_result_h1.setText(f"Точки в области: \n{belong}")
        self.lbl_result_h2.setText(f"Значение функции в соответствующих точках: \n{fun_value}")
        self.lbl_result_n.setText(f"Наибольшое значение = {maximum(fun_value, belong)[0]} в точке {maximum(fun_value, belong)[1]}")
        self.lbl_result_m.setText(f"Наименьшее значение = {minimum(fun_value, belong)[0]} в точке {minimum(fun_value, belong)[1]}")


def limitations(lim):
    x, y = symbols("x y")
    limits = []
    limits_ = []
    extra_limits = []
    extra_limits_ = []
    for i in range(3):
        str_limit = lim[i]
        if str_limit.find('x') != -1 and str_limit.find('y') != -1:
            extra_limits.append(sympify(str_limit))
            print(extra_limits)
            if str_limit.find(">=") != -1:
                extra_limits_.append(sympify(str_limit.replace(">=", "-")))
                print(extra_limits_)
            elif str_limit.find("<=") != -1:
                extra_limits_.append(sympify(str_limit.replace("<=", "-")))
                print(extra_limits_)
        else:
            limits.append(sympify(str_limit))
            if str_limit.find(">=") != -1:
                limits_.append(sympify(str_limit.replace(">=", "-")))
                print(limits_)
            elif str_limit.find("<=") != -1:
                limits_.append(sympify(str_limit.replace("<=", "-")))
                print(limits_)
    limits_for_change = []
    limits_toch = []
    for _ in limits_:
        limits_toch.append(solve(_))
        limits_for_change.append(solve(_, dict=True))
        print(limits_toch)

    if len(extra_limits) != 0:
        for _ in limits_:
            limits_toch.append(solve_poly_system([extra_limits_[0], _], x, y))
            print(limits_toch)
        for _ in extra_limits_:
            limits_for_change.append(solve(extra_limits_[0], y, dict=True))
            print(limits_for_change)

    limits_toch[0].append(limits_toch[1][0])
    limits_toch.pop(1)
    limits_toch[0] = [tuple(limits_toch[0])]
    items = []
    for item in limits_for_change:
        items.append(list(item[0].items()))
        print(items)
    return [limits_toch, items]

def finding_points(expr, points, changed_variable=0):
    x, y = symbols("x y")
    xdiff = diff(expr, x)
    ydiff = diff(expr, y)
    try:
        point = solve_poly_system([xdiff, ydiff], x, y)
        points.append(point)
    except:  # решения на сторонах многоугольника
        if xdiff == 0 and number((str(changed_variable))):
            point = solve(ydiff, y)
            points.append([(changed_variable, point[0])])
        elif ydiff == 0 and number(str(changed_variable)):
            point = solve(xdiff, x)
            points.append([(point[0], changed_variable)])
        elif not str(changed_variable).isdigit():
            pointx = solve(xdiff, x)
            pointy = changed_variable.subs(x, pointx[0])
            points.append([(pointx[0], pointy)])
    print(points)
    return points

def builder_oblast(points):
    points_for_poly = []
    for point in points:
        points_for_poly.append(point[0])
    poly = Polygon(*points_for_poly)
    return poly

def belonging_the_area(znach, oblast):
    if oblast.encloses_point(znach) or oblast.intersection(znach) != []:
        return True
    else:
        return False

def function_value(expr, point):
    x, y = symbols("x y")
    value = expr.subs([(x, point[0][0]), (y, point[0][1])])
    return value

def maximum(values, points):
    value = 0
    point = 0
    for i in range(len(values)):
        if value < values[i]:
            value, point = values[i], points[i]
    return [value, point]

def minimum(values, points):
    value = 0
    point = 0
    for i in range(len(values)):
        if value > values[i]:
            value, point = values[i], points[i]
    return [value, point]

def number(num):
    try:
        float(num)
        return True
    except ValueError:
        return False
    
def replace_(function):
    val = function.replace("^", "**")
    return val

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())