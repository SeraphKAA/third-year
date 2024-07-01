import sympy as sp
from tkinter import *
from plot_file_2 import *
# x*x-2*x-y*y*y+y*y+y-5
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

		for point in extrema:
			temp = formula.subs(x,  point[0])
			res.append((point, temp.subs(y,  point[1])))
		
		f = sp.lambdify((x, y), formula)
		plot(f, res)
		print_res(res)


	window = Tk()
	window.geometry('500x200')
	window.title("2 индивидуальная работа")

	txt = Entry(window, width = 15, font = "Arial 14")
	txt.place(relx = 0.57, rely = 0.3, anchor = CENTER)

	en1 = Entry(window, width = 5, font = "Arial 14")
	en1.place(relx = 0.2, rely = 0.53, anchor = CENTER)

	en2 = Entry(window, width = 5, font = "Arial 14")
	en2.place(relx = 0.4, rely = 0.53, anchor = CENTER)

	en3 = Entry(window, width = 5, font = "Arial 14")
	en3.place(relx = 0.6, rely = 0.53, anchor = CENTER)

	but = Button(window, text = "        ", command = clicked, font = "Arial 11")
	but.place(relx = 0.85, rely=0.3, anchor = CENTER)

	txt_fir = Label(window, text = "Напишите функцию u(x, y)", font = "Arial 12", justify = "left")
	txt_fir.place(relx = 0.21, rely = 0.3, anchor = CENTER)
	
	exc_txt = Label(window, text = "-", font = "Arial 12", justify = "left")
	exc_txt.place(relx = 0.5, rely = 0.8, anchor = CENTER)

	window.mainloop()


if __name__ == "__main__":
    Start()