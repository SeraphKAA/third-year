from test import *
from tkinter import *
from tkinter import scrolledtext

"""
шишка: 20 32
лосось: 32 10
цирюльникъ: 1000 20
астрахань: 1 1
"""

def abc(str):
	arr = []
	arr = str.split("\n"); arr.pop(-1); arr1 = []
	for i in range(len(arr)):
		arr1.append(arr[i].split(": "))
	
	res = {}
	for i in arr1:
		val = i[1].split(" "); val1 = []
		for j in val:
			val1.append(int(j))
			
		res[i[0]] = tuple(val1)
	
	return res


def activatore(stuff, dict, sa = ""):
	tk = Tk()
	tk.geometry("500x300")
	tk.title("Вывод")

	st = ''; 
	for x in stuff: st+= x + "\n"
	a = scrolledtext.ScrolledText(tk, wrap = WORD, width = 40, height = 6, font = ("Times New Roman", 14))
	a.place(relx = 0.5, rely = 0.4, anchor = CENTER)
	a.insert(INSERT, st)

	b = Label(tk, text = sum([dict[item][0] for item in stuff]), width = 10, font = ("Times New Roman", 14))
	b.place(relx = 0.5, rely = 0.81, anchor = CENTER)
	
	c = Label(tk, text = sum([dict[item][1] for item in stuff]), width = 10, font = ("Times New Roman", 14))
	c.place(relx = 0.5, rely = 0.9, anchor = CENTER)
	
	d = Label(tk, text = sa, width = 10, font = ("Times New Roman", 14))
	d.place(relx = 0.8, rely = 0.81, anchor = CENTER)


def Start():

	def clicked():
		text_arr = txt.get("1.0", END)
		a = txt1.get()
		dict = abc(text_arr)
		print(dict)
		for i, j in dict.items():
			if(len(j) > 2):
				res.configure(text = "Вы ввели неправильную характеристику")
				return 0 
		# print(dict)
		if(a == ""):
			# stuff = get_selected_items_list(stuffdict)
			stuff = get_selected_items_list(dict)
			activatore(stuff, dict)
		else:
			try:
				stuff = get_selected_items_list(dict, int(a))
				activatore(stuff, dict, a)
			except:
				res.configure(text = "Введите целое или число меньше 2000")
				return 0

		# print(stuff)
		# print(sum([dict[item][0] for item in stuff]))
		# print(sum([dict[item][1] for item in stuff]))

		# print(sum([stuffdict[item][0] for item in stuff]))
		# print(sum([stuffdict[item][1] for item in stuff]))
		



	window = Tk()
	window.geometry('500x280')
	window.title("4 лаба")

	txt = scrolledtext.ScrolledText(window, wrap = WORD, width = 40, height = 8, font = ("Times New Roman", 14))
	txt.place(relx = 0.5, rely = 0.4, anchor = CENTER)


	txt1 = Entry(window, width = 5, font = ("Times New Roman", 14))
	txt1.place(relx = 0.1, rely = 0.88, anchor = CENTER)

	but = Button(window, text = "        ", command = clicked, font = "Arial 11")
	but.place(relx = 0.93, rely=0.88, anchor = CENTER)

	
	res = Label(window, text = "-", font = "Arial 12", justify = "left")
	res.place(relx = 0.5, rely = 0.88, anchor = CENTER)
	
	window.mainloop()
	

if __name__ == "__main__":
	# activatore(get_selected_items_list(stuffdict), stuffdict)
	Start()