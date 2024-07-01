import sympy as sp

def extr(u_expr, constraint_expr):
    # Создаем символьные переменные
    x, y, λ = sp.symbols('x y λ')

    # Определяем функцию и уравнение связи
    U = sp.sympify(u_expr)
    Fxy = sp.sympify(constraint_expr)

    # Составляем лагранжиан
    L = U - λ * Fxy

    # Берем частные производные
    dL_dx = sp.diff(L, x)
    dL_dy = sp.diff(L, y)
    dL_dλ = -Fxy

    solution = sp.solve([dL_dx, dL_dy, dL_dλ], (x, y, λ))

    return solution




    # x1, y1 = sp.symbols('x y')

    # # Компиляция введенных выражений
    # u = sp.sympify(u_expr)
    # constraint_eq = sp.sympify(constraint_expr)

    # # Решение системы уравнений
    # solution = sp.solve(constraint_eq, y1)

    # # Подставляем найденное значение y в функцию u
    # u_with_substitution = u.subs(y1, solution[0])

    # # Находим условный экстремум путем нахождения частных производных и решения системы уравнений
    # partial_x = sp.diff(u_with_substitution, x1)
    # partial_y = sp.diff(u_with_substitution, y1)
    # extremum = sp.solve([partial_x, partial_y], (x1, y1))

    # return extremum

