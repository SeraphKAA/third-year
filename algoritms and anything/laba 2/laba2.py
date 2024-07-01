import sys
from tkinter import *

def MatrixChainOrder(p, i, j):
	if i == j:
		return 0
	_min = sys.maxsize
	for k in range(i, j):
		count = (MatrixChainOrder(p, i, k) + MatrixChainOrder(p, k + 1, j) + p[i-1] * p[k] * p[j])
		if count < _min:
			_min = count
			
	return _min


def Start():

	def clicked():
		sl = ("0123456789,")
		text_arr = txt.get()
		for i in text_arr:
			if (i not in sl):
				res.configure(text = "Есть буквы")
				return
		text_arr = text_arr.split(',')
		for i in range (len(text_arr)):
			text_arr[i] = int(text_arr[i])

		result = MatrixChainOrder(text_arr, 1, len(text_arr) - 1)
		res.configure(text = result)
	

	window = Tk()
	window.geometry('300x150')
	window.title("2 лаба")

	txt = Entry(window, width = 15, font = "Arial 14")
	txt.place(relx = 0.35, rely = 0.3, anchor = CENTER)

	but = Button(window, text = "        ", command = clicked, font = "Arial 11")
	but.place(relx = 0.85, rely=0.3, anchor = CENTER)

	txt_res = Label(window, text = "Произведение матриц = ", font = "Arial 12", justify = "left")
	txt_res.place(relx = 0.37, rely = 0.7, anchor = CENTER)
	
	res = Label(window, text = "-", font = "Arial 12", justify = "left")
	res.place(relx = 0.72, rely = 0.7, anchor = CENTER)
	
	window.mainloop()
	

if __name__ == "__main__":
	Start()
	pass
