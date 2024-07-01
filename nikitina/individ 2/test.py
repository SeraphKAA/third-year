import numpy as np
from scipy.optimize import minimize

# 4*x*x + 2*x*y - y*y + 2*x + y - 1

# def objective(x):
#     u = 4*x[0]*x[0] + 2*x[0]*x[1] - x[1]*x[1] + 2*x[0] + x[1] + 1
#     return u

# def constraint1(x):
#     return x[0] + 3

# def constraint2(x):
#     return x[1] + 2

# def constraint3(x):
#     return -x[0] - x[1] + 1


# def Start1():
#     u = input("Функция u: ")
#     usl = input("Напишите условия: ").split(", ")

#     func  = eval(u)

#     print(func)

#     print(usl)


# def main():
#     x0 = np.array([0, 0])
#     bnd = ((-3, None), (-2, None))
#     con1 = {'type': 'ineq', 'fun': constraint1}
#     con2 = {'type': 'ineq', 'fun': constraint2}
#     con3 = {'type': 'ineq', 'fun': constraint3}
#     cons = [con1, con2, con3]

#     sol = minimize(objective, x0, method = 'SLSQP', bounds = bnd, constraints = cons)
#     u_min = sol.fun
#     u_max = -u_min

#     print("Minimum value of u(x,y):", u_min)
#     print("Maximum value of u(x,y):", u_max)



# if __name__ == "__main__":
#     Start1()






from sympy import symbols, Interval, Min, Max

# Считываем функцию u(x, y)
x, y = symbols('x y')
# function_str = input("Введите функцию u(x, y): ")
function_str = "4*x*x-x*y+2*y*y+3*x+2*y+4 "
function = eval(function_str)

# Считываем условия области D
# domain_str = input("Введите область D в формате 'x >= a, y >= b, x + y <= c': ")
domain_str = "x >= -3, y >= -2, x + y <= 1"
domain_list = domain_str.split(',')

# Определение переменных x и y


# Создание области D
domain_x = Interval(float(domain_list[0].split('>= ')[-1]), float('inf'))
domain_y = Interval(float(domain_list[1].split('>= ')[-1]), float('inf'))
domain_x_y = Interval(float('-inf'), float(domain_list[2].split('<= ')[-1]))
domain = domain_x.intersect(domain_y).intersect(domain_x_y)

# Разбиваем область domain на элементы
u_min = float('inf')
u_max = float('-inf')

# Определение допустимых значений переменных x и y
x_values = domain_x.as_relational(x).as_set().args
y_values = domain_y.as_relational(y).as_set().args

# Перебор всех комбинаций значений x и y
for x_val in x_values:
    for y_val in y_values:
        point = {x: x_val, y: y_val}
        u_val = function.subs(point)
        
        # Обновление минимального и максимального значения функции
        u_min = min(u_min, u_val)
        u_max = max(u_max, u_val)

# Вывод результатов
print("Минимальное значение функции:", u_min)
print("Максимальное значение функции:", u_max)
# # python3 program.py "-4*x*x-x*y+2*y*y+3*x+2*y+4" "x >= -3, y >= -2, x+y <= 1"