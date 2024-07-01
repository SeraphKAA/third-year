from cvxopt.modeling import variable, op
from prettytable import PrettyTable

x, acc = variable(15, 'x'), 1

c = list(map(int, input('Введите матрицу коэффициентов через запятую\n-> ').split(',')))
z = (c[0] * x[0] + c[1] * x[1] + c[2] * x[2] + c[3] * x[3] + c[4] * x[4] + c[5] * x[5] + c[6] * x[6] + c[7] * x[7] + c[
    8] * x[8] + c[9] * x[9] + c[10] * x[10] + c[11] * x[11] + c[12] * x[12] + c[13] * x[13] + c[14] * x[14])

post = list(map(int, input('Введите запасы груза поставщиков через запятую\n-> ').split(',')))
potr = list(map(int, input('Введите запасы груза для потребителей через запятую\n-> ').split(',')))

mass1 = (x[0] + x[1] + x[2] + x[3] + x[4] <= post[0])
mass2 = (x[5] + x[6] + x[7] + x[8] + x[9] <= post[1])
mass3 = (x[10] + x[11] + x[12] + x[13] + x[14] <= post[2])
mass4 = (x[0] + x[5] + x[10] == potr[0])
mass5 = (x[1] + x[6] + x[11] == potr[1])
mass6 = (x[2] + x[7] + x[12] == potr[2])
mass7 = (x[3] + x[8] + x[13] == potr[3])
mass8 = (x[4] + x[9] + x[14] == potr[4])

x_non_negative = (x >= 0)
problem = op(z, [mass1, mass2, mass3, mass4, mass5, mass6, mass7, mass8, x_non_negative])
problem.solve(solver='glpk')

table = PrettyTable()
table.field_names = ['индекс', 'значение']

for i in x.value:
    table.add_row([acc, i])
    acc += 1
print(f'\nРезультат:\n {table}\nСтоимость доставки: {problem.objective.value()[0]}')
