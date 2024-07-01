import sympy as sp
from tkinter import *
from plot_file import *
# x**2 - 2*x - y**3 + y**2 + y - 5
# x**2 - x - y**3 -4*y**2 - 4*y + 3
# x**2 - x -y**3 + 5*y**2 + 8*y - 5

# [(("x", "y"), "значение u(x, y)")]
res = []

def Start():
	def clicked():
		global res
		x, y = sp.symbols('x y')
		func = txt.get()
		try:
			formula = eval(func)
			grad_u = [sp.diff(formula, var) for var in (x, y)]
			extrema = sp.solve(grad_u, (x, y))
		except:
			exc_txt.configure(text = "Неправильная запись функции")
			return
		

		gradient = sp.Matrix([sp.diff(func, x), sp.diff(func, y)])
		stationary_points = sp.solve(gradient, (x, y))
		if len(stationary_points) == 0:
			exc_txt.configure("Функция не имеет экстремумов")
			return

		res = []
		for point in extrema:
			temp = formula.subs(x,  point[0])
			res.append((point, temp.subs(y,  point[1])))
		
		f = sp.lambdify((x, y), formula)
		print(f, res)
		plot(f, res)
		print_res(res)


	window = Tk()
	window.geometry('500x150')
	window.title("1 индивидуальная работа")

	txt = Entry(window, width = 15, font = "Arial 14")
	txt.place(relx = 0.57, rely = 0.3, anchor = CENTER)

	but = Button(window, text = "        ", command = clicked, font = "Arial 11")
	but.place(relx = 0.85, rely=0.3, anchor = CENTER)

	txt_fir = Label(window, text = "Напишите функцию u(x, y)", font = "Arial 12", justify = "left")
	txt_fir.place(relx = 0.21, rely = 0.3, anchor = CENTER)
	
	exc_txt = Label(window, text = "-", font = "Arial 12", justify = "left")
	exc_txt.place(relx = 0.5, rely = 0.7, anchor = CENTER)

	window.mainloop()


if __name__ == "__main__":
    Start()