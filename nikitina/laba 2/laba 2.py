import numpy as np


def get_pivot_position(tableau):
    z = tableau[-1]
    column = next(i for i, x in enumerate(z[:-1]) if x > 0)

    restrictions = []
    for eq in tableau[:-1]:
        el = eq[column]
        restrictions.append(math.inf if el <= 0 else eq[-1] / el)

    row = restrictions.index(min(restrictions))
    return row, column


def pivot_step(tableau, pivot_position):
    new_tableau = [[] for eq in tableau]

    i, j = pivot_position
    pivot_value = tableau[i][j]
    new_tableau[i] = np.array(tableau[i]) / pivot_value

    for eq_i, eq in enumerate(tableau):
        if eq_i != i:
            multiplier = np.array(new_tableau[i]) * tableau[eq_i][j]
            new_tableau[eq_i] = np.array(tableau[eq_i]) - multiplier

    return new_tableau


def is_basic(column):
    return sum(column) == 1 and len([c for c in column if c == 0]) == len(column) - 1


def get_solution(tableau):
    columns = np.array(tableau).T
    solutions = []
    for column in columns[:-1]:
        solution = 0
        if is_basic(column):
            one_index = column.tolist().index(1)
            solution = columns[-1][one_index]
        solutions.append(solution)

    return solutions


def simplex(c, A, b):
    tableau = to_tableau(c, A, b)

    while can_be_improved(tableau):
        pivot_position = get_pivot_position(tableau)
        tableau = pivot_step(tableau, pivot_position)

    return get_solution(tableau)


def to_tableau(c, A, b):
    xb = [eq + [x] for eq, x in zip(A, b)]
    z = c + [0]
    return xb + [z]


def can_be_improved(tableau):
    z = tableau[-1]
    return any(x > 0 for x in z[:-1])


tmp_c = str(input('Введите прибыль через запятую\n-> ')).replace(" ", "").split(',')
c = list(map(int, tmp_c))

tmp_c = str(input('Введите вектор b\n-> ')).replace(" ", "").split(',')
b = list(map(int, tmp_c))
A = []
print("\nВведите матрицу A\nВведи строку x-ов через ','")
for i in range(0, len(b)):
    tmp_c = str(input('-> ')).replace(" ", "").split(',')
    tmpVec = list(map(int, tmp_c))
    A.append(tmpVec)

import math

solution = simplex(c, A, b)
for i in range(0, len(solution)):
    print(f"x{i+1} = {int(solution[i] + (0.5 if solution[i] > 0 else -0.5))}")

sum_F = 0
for i in range(0, len(solution)):
    for j in range(0, len(c)):
        if i == j:
            sum_F += int(solution[i] + (0.5 if solution[i] > 0 else -0.5)) * c[j]
print(f'F = {sum_F}')
