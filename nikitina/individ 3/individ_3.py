from tkinter import *
from pog import *
from plot_file import *

# 4*x*x + 2* x* y + y* y+ 3*x - y + 1
# 2*x + 3 *y + 1

def Start():
	def clicked():
		# u = txt.get()
		# constraint_eq = txt2.get()
		u = "2*x*y+2*y*y+4*x-y+6"
		constraint_eq = "2*x+y+4"

		try:
			res = extr(u, constraint_eq)
			
			ress = res.values(); res1 = []
			for i in ress: res1.append(i)

			print(res)
			abc = ""
			if res1[2] >= 0:
				abc = "точка максимума"
			else:
				abc = "точка минимума"

			exc_txt.configure(text = "условный экстремум функции = " + str(res) + "\n" + abc)
			plot(u, constraint_eq, res)
		except:
			exc_txt.configure(text = "Что-то пошло не так, проверьте поля")
		


	window = Tk()
	window.geometry('500x150')
	window.title("3 индивидуальная работа")

	txt = Entry(window, width = 15, font = "Arial 14")
	txt.place(relx = 0.6, rely = 0.3, anchor = CENTER)

	txt2 = Entry(window, width = 15, font = "Arial 14")
	txt2.place(relx = 0.6, rely = 0.53, anchor = CENTER)

	but = Button(window, text = "        ", command = clicked, font = "Arial 11")
	but.place(relx = 0.85, rely=0.3, anchor = CENTER)

	txt_fir = Label(window, text = "Напишите функцию u(x, y)", font = "Arial 12", justify = "left")
	txt_fir.place(relx = 0.21, rely = 0.3, anchor = CENTER)

	txt_sec = Label(window, text = "Напишите уравнение связи", font = "Arial 12", justify = "left")
	txt_sec.place(relx = 0.21, rely = 0.52, anchor = CENTER)
	
	exc_txt = Label(window, text = "-", font = "Arial 12", justify = "left")
	exc_txt.place(relx = 0.5, rely = 0.75, anchor = CENTER)

	window.mainloop()


if __name__ == "__main__":
    Start()