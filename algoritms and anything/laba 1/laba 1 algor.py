# Алгоритмы сортировки.
# Реализовать программу, которая включает в себя следующие алгоритмы 
# сортировки:       
# вставками;        +
# выбором;          +
# обменом;          +
# быстрая;          +
# деревья;          +
# пирамидальная;    +
# Шелла;            +
# слиянием.         +
# Провести тестирование для последовательности 5000, 10000, 100000, 150000 
# элементов для наилучшего, наихудшего и среднего случая. Сделать выводы о 
# сложности и времени работы алгоритмов. 
# Реализовать лабораторную работу красиво и нестандартно.
from tkinter import *
from tkinter.ttk import Combobox
from random import randint, shuffle
from textwrap import wrap
import time


# =========================================================================== #
def shellSort(arr):
    n = len(arr) # Длина массива
    gap = n // 2 # Шаг для разделения массива на подмассивы
    while gap > 0:
        for i in range(gap, n):
            temp = arr[i] # Текущий элемент
            j = i
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap] # Перемещение элемента вправо
                j -= gap
            arr[j] = temp # Вставка элемента на его правильное место
        gap //= 2 # Уменьшение шага на половину
    
    return arr
# =========================================================================== #

# =========================================================================== #
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr
# =========================================================================== #

# =========================================================================== #
class Node:
    # BST data structure
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

    def insert(self, val):
        if self.val:
            if val < self.val:
                if self.left is None:
                    self.left = Node(val)
                else:
                    self.left.insert(val)
            elif val > self.val:
                if self.right is None:
                    self.right = Node(val)
                else:
                    self.right.insert(val)
        else:
            self.val = val


def inorder(root, res):
    # Recursive traversal
    if root:
        inorder(root.left, res)
        res.append(root.val)
        inorder(root.right, res)


def tree_sort(arr):
    # Build BST
    if len(arr) == 0:
        return arr
    root = Node(arr[0])
    for i in range(1, len(arr)):
        root.insert(arr[i])
    # Traverse BST in order.
    res = []
    inorder(root, res)
    return res
# =========================================================================== #

# =========================================================================== #
def heapify(arr, n, i):
    largest = i # Initialize largest as root
    l = 2 * i + 1   # left = 2*i + 1
    r = 2 * i + 2   # right = 2*i + 2
    # Проверяем существует ли левый дочерний элемент больший, чем корень
    if l < n and arr[i] < arr[l]:
        largest = l
    # Проверяем существует ли правый дочерний элемент больший, чем корень
    if r < n and arr[largest] < arr[r]:
        largest = r
    # Заменяем корень, если нужно
    if largest != i:
        arr[i],arr[largest] = arr[largest],arr[i] # свап
        # Применяем heapify к корню.
        heapify(arr, n, largest)

# Основная функция для сортировки массива заданного размера
def heapSort(arr):
    n = len(arr)
    # Построение max-heap.
    for i in range(n, -1, -1):
        heapify(arr, n, i)
    # Один за другим извлекаем элементы
    for i in range(n-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i] # свап 
        heapify(arr, i, 0)
    
    return arr
# =========================================================================== #

# =========================================================================== #
def partition(array, begin, end):
    pivot_idx = begin
    for i in range(begin+1, end+1):
        if array[i] <= array[begin]:
            pivot_idx += 1
            array[i], array[pivot_idx] = array[pivot_idx], array[i]
    array[pivot_idx], array[begin] = array[begin], array[pivot_idx]
    return pivot_idx

def quick_sort_recursion(array, begin, end):
    if begin >= end:
        return
    pivot_idx = partition(array, begin, end)
    quick_sort_recursion(array, begin, pivot_idx-1)
    quick_sort_recursion(array, pivot_idx+1, end)

def quick_sort(array, begin=0, end=None):
    if end is None:
        end = len(array) - 1
    
    quick_sort_recursion(array, begin, end)
    return array
# =========================================================================== #

# =========================================================================== #
def merge_sort(arr):
    # Последнее разделение массива
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    # Выполняем merge_sort рекурсивно с двух сторон
    left, right = merge_sort(arr[:mid]), merge_sort(arr[mid:])

    # Объединяем стороны вместе
    return merge(left, right, arr.copy())


def merge(left, right, merged):
    
    left_cursor, right_cursor = 0, 0
    while left_cursor < len(left) and right_cursor < len(right):
      
        # Сортируем каждый и помещаем в результат
        if left[left_cursor] <= right[right_cursor]:
            merged[left_cursor+right_cursor]=left[left_cursor]
            left_cursor += 1
        else:
            merged[left_cursor + right_cursor] = right[right_cursor]
            right_cursor += 1
            
    for left_cursor in range(left_cursor, len(left)):
        merged[left_cursor + right_cursor] = left[left_cursor]
        
    for right_cursor in range(right_cursor, len(right)):
        merged[left_cursor + right_cursor] = right[right_cursor]

    return merged
# =========================================================================== #

# =========================================================================== #
def insertion_sort(arr):
    time_starter = time.time()
    for i in range(len(arr)):
        cursor = arr[i]
        pos = i
        
        while pos > 0 and arr[pos - 1] > cursor:
            # Меняем местами число, продвигая по списку
            arr[pos] = arr[pos - 1]
            pos = pos - 1
        # Остановимся и сделаем последний обмен
        arr[pos] = cursor

    return arr
# =========================================================================== #

# =========================================================================== #
def selection_sort(arr):       
    for i in range(len(arr)):
        minimum = i
        for j in range(i + 1, len(arr)):
            # Выбор наименьшего значения
            if arr[j] < arr[minimum]:
                minimum = j

        # Помещаем это перед отсортированным концом массива
        arr[minimum], arr[i] = arr[i], arr[minimum]
            

    return arr
# =========================================================================== #


textbox = "-------"
check = False
def Start():

    def alg(get_mas):
        mas_after = list(); timer = 1
        match combo.get():
            case "сортировка слиянием":
                start_timer = time.time(); mas_after = merge_sort(get_mas.copy()); timer = time.time() - start_timer                                         # сортировка слиянием

            case "сортировка вставками":
                start_timer = time.time(); mas_after = insertion_sort(get_mas.copy()); timer = time.time() - start_timer                                     # сортировка вставками

            case "сортировка выбором":
                start_timer = time.time(); mas_after = selection_sort(get_mas.copy()); timer = time.time() - start_timer                                     # сортировка выбором

            case "сортировка обменом (пузырьком)":
                start_timer = time.time();  mas_after = bubble_sort(get_mas.copy()); timer = time.time() - start_timer                                       # сортировка обменом (пузырьком)

            case "быстрая сортировка":
                start_timer = time.time(); mas_after = quick_sort(get_mas.copy()); timer = time.time() - start_timer                                         # быстрая сортировка

            case "сортировка деревом":
                start_timer = time.time();  mas_after = tree_sort(get_mas.copy()); timer = time.time() - start_timer                                         # сортировка деревом

            case "пирамидальная сортировка":
                start_timer = time.time(); m_copy = get_mas.copy(); mas_after = heapSort(m_copy); timer = time.time() - start_timer                          # пирамидальная сортировка

            case "сортировка Шелла":
                start_timer = time.time();  mas_after = shellSort(get_mas.copy()); timer = time.time() - start_timer                                         # сортировка Шелла
                

        
        # print("\n пирамидальная сортировка"); start_timer = time.time(); m_copy = massiv.copy(); mas_after = heapSort(m_copy); print(m_copy); timer = time.time() - start_timer   # пирамидальная сортировка
        # print("\n быстрая сортировка"); start_timer = time.time(); mas_after = quick_sort(massiv.copy()); timer = time.time() - start_timer                                       # быстрая сортировка
        # print("\n сортировка слиянием"); start_timer = time.time(); mas_after = merge_sort(massiv.copy()); timer = time.time() - start_timer                                      # сортировка слиянием
        # print("\n сортировка вставками"); start_timer = time.time(); mas_after = insertion_sort(massiv.copy()); timer = time.time() - start_timer                                 # сортировка вставками
        # print("\n сортировка выбором"); start_timer = time.time(); mas_after = selection_sort(massiv.copy()); timer = time.time() - start_timer                                   # сортировка выбором
        # print("\n сортировка деревом"); start_timer = time.time();  mas_after = tree_sort(massiv.copy()); timer = time.time() - start_timer                                       # сортировка деревом
        # print("\n сортировка обменом (пузырьком)");  start_timer = time.time();  mas_after = bubble_sort(massiv.copy()); timer = time.time() - start_timer                        # сортировка обменом (пузырьком)
        # print("\n сортировка Шелла"); start_timer = time.time();  mas_after = shellSort(massiv.copy()); timer = time.time() - start_timer                                         # сортировка Шелла
        lb1.configure(text = massiv)
        lb2.configure(text = mas_after)
        lb3.configure(text =  "время работы алгоритма: " + str(round(timer, 5)))
        # window.update()  

        # width = lb1.winfo_width()

        # if width > 400:
        #     char_width = width / len(massiv)
        #     wrapped_text = '\n'.join(wrap(massiv, int(400 / char_width)))
        #     lb1['text'] = wrapped_text
        pass


    def clicked():
        global check, massiv, textbox

        if not check or txt.get() != textbox:
            check = True
            textbox = txt.get()
            massiv = [i for i in range(int(textbox))]
            shuffle(massiv)
            final = list()
            match combo_1.get():
                case "не отсортирован":
                    final = massiv
                
                case "отсортирован на 25%":
                    slice_int = (len(massiv) // 4)
                    first_half = massiv.copy()
                    first_half = first_half[:slice_int]
                    first_half.sort()

                    second_half = massiv.copy()[slice_int:]
                    final = first_half + second_half
                
                case "отсортирован на 50%":
                    slice_int = (len(massiv) // 2)
                    first_half = massiv.copy()
                    first_half = first_half[:slice_int]
                    first_half.sort()

                    second_half = massiv.copy()[slice_int:]
                    final = first_half + second_half
                
                case "отсортирован на 75%":
                    slice_int = (len(massiv) // 4)
                    first_half = massiv.copy()
                    first_half = first_half[slice_int:]
                    first_half.sort()

                    second_half = massiv.copy()[:slice_int]
                    final = first_half + second_half

                case "отсортирован на 100%":
                    final = massiv.copy()
                    final.sort()
        
        # print(check, '\n', massiv)
        alg(final)


    window = Tk()
    window.geometry('800x600')
    window.title("Сортировки")

    lbl = Label(window, text = "Размерность массива = ", font = "Arial 14 bold")
    lbl.place(relx = 0.16, rely = 0.07, anchor = CENTER)

    txt = Entry(window, width = 6, font = "Arial 14")
    txt.place(relx = 0.345, rely = 0.07, anchor = CENTER)

    combo = Combobox(window, font = "Arial 14", state='readonly')  
    combo['values'] = ("сортировка вставками", 
                       "сортировка выбором", 
                       "сортировка обменом (пузырьком)", 
                       "быстрая сортировка", 
                       "сортировка деревом", 
                       "пирамидальная сортировка", 
                       "сортировка Шелла", 
                       "сортировка слиянием")
    combo.current(0)
    combo.place(relx = 0.165, rely = 0.14, anchor = CENTER)

    btn = Button(window, text = "        ", command = clicked, font = "Arial 11")
    btn.place(relx=0.355, rely=0.137, anchor=CENTER)

    lb1 = Label(window, text = "0", font = "Arial 10", bg = "lightgreen", width = 90, anchor="w", justify="left", height = 12)
    lb1.place(relx=0.475, rely=0.35, anchor=CENTER)

    lb2 = Label(window, text = "0", font = "Arial 10",  bg = "lightblue", width = 90, anchor="w", justify="left", height = 12)
    lb2.place(relx=0.475, rely=0.75, anchor=CENTER)

    lb3 = Label(window, text = "время работы алгоритма: -", font = "Arial 10", justify="left")
    lb3.place(relx=0.6, rely=0.137, anchor=CENTER)

    combo_1 = Combobox(window, font = "Arial 14", state='readonly')
    combo_1.place(relx = 0.6, rely = 0.07, anchor = CENTER)
    combo_1["value"] = ("не отсортирован", 
                        "отсортирован на 25%", 
                        "отсортирован на 50%", 
                        "отсортирован на 75%", 
                        "отсортирован на 100%")
    combo_1.current(0)

    window.mainloop()




if (__name__ == "__main__"):
    Start()