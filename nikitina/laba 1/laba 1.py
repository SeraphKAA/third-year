import pulp as p

Lp_prob = p.LpProblem('Problem', p.LpMinimize)

x1 = p.LpVariable("x1", lowBound=0)
x2 = p.LpVariable("x2", lowBound=0)
x3 = p.LpVariable("x3", lowBound=0)


Lp_prob += 6 * x1 + 8 * x2 + 12 * x3 

Lp_prob += 2 * x1 + 1 * x2 + 3 * x3 >= 2
Lp_prob += 1 * x1 + 2 * x2 + 4 * x3 >= 3
Lp_prob += 3 * x1 + 1.5 * x2 + 3 * x3 >= 2.5

# Lp_prob += 2 * x1 + 3 * x2 + 2.5 * x3 

# Lp_prob += 2 * x1 + 1 * x2 + 3 * x3 >= 6
# Lp_prob += 1 * x1 + 2 * x2 + 4 * x3 >= 8
# Lp_prob += 3 * x1 + 1.5 * x2 + 3 * x3 >= 12

print(Lp_prob)
status = Lp_prob.solve()

print("Результат:")
for variable in Lp_prob.variables():
    print(variable.name, "=", variable.varValue)

print("Общее число перевезенного товара:", p.value(Lp_prob.objective))
