import sympy as sp

def find_extremum(u, fxy):
    # Создаем символьные переменные
    x, y, λ = sp.symbols('x y λ')

    # Определяем функцию и уравнение связи
    U = sp.sympify(u)
    Fxy = sp.sympify(fxy)

    # Составляем лагранжиан
    L = U - λ * Fxy

    # Берем частные производные
    dL_dx = sp.diff(L, x)
    dL_dy = sp.diff(L, y)
    dL_dλ = -Fxy

    # Решаем систему уравнений
    solution = sp.solve([dL_dx, dL_dy, dL_dλ], (x, y, λ))

    return solution

u = "4*x*x + 2*x*y + y*y + 3*x - y + 1"
fxy = "2*x + 3*y + 1"

extremum = find_extremum(u, fxy)
print(extremum)