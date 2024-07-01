import tkinter as tk
from tkinter import messagebox

class AVLNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1

class AVLTree:
    def __init__(self):
        self.root = None

    def _height(self, node):
        if node is None:
            return 0
        return node.height

    def _balance(self, node):
        if node is None:
            return 0
        return self._height(node.left) - self._height(node.right)

    def _update_height(self, node):
        if node:
            node.height = 1 + max(self._height(node.left), self._height(node.right))

    def _rotate_right(self, y):
        x = y.left
        T2 = x.right

        x.right = y
        y.left = T2

        self._update_height(y)
        self._update_height(x)

        return x

    def _rotate_left(self, x):
        y = x.right
        T2 = y.left

        y.left = x
        x.right = T2

        self._update_height(x)
        self._update_height(y)

        return y

    def insert(self, root, key):
        if root is None:
            return AVLNode(key)
        if key < root.key:
            root.left = self.insert(root.left, key)
        else:
            root.right = self.insert(root.right, key)

        self._update_height(root)

        balance = self._balance(root)

        if balance > 1:
            if key < root.left.key:
                return self._rotate_right(root)
            else:
                root.left = self._rotate_left(root.left)
                return self._rotate_right(root)
        if balance < -1:
            if key > root.right.key:
                return self._rotate_left(root)
            else:
                root.right = self._rotate_right(root.right)
                return self._rotate_left(root)

        return root

    def insert_key(self, key):
        self.root = self.insert(self.root, key)

    def search(self, root, key):
        if root is None:
            return None
        if key == root.key:
            return root
        if key < root.key:
            return self.search(root.left, key)
        return self.search(root.right, key)

    def find_key(self, key):
        return self.search(self.root, key)

    def delete(self, root, key):
        if root is None:
            return root

        if key < root.key:
            root.left = self.delete(root.left, key)
        elif key > root.key:
            root.right = self.delete(root.right, key)
        else:
            if root.left is None:
                return root.right
            elif root.right is None:
                return root.left
            root.key = self._min_value_node(root.right)
            root.right = self.delete(root.right, root.key)

        self._update_height(root)

        balance = self._balance(root)

        if balance > 1:
            if self._balance(root.left) >= 0:
                return self._rotate_right(root)
            else:
                root.left = self._rotate_left(root.left)
                return self._rotate_right(root)
        if balance < -1:
            if self._balance(root.right) <= 0:
                return self._rotate_left(root)
            else:
                root.right = self._rotate_right(root.right)
                return self._rotate_left(root)

        return root

    def delete_key(self, key):
        if self.find_key(key):
            self.root = self.delete(self.root, key)
            return True
        return False

    def _min_value_node(self, node):
        while node.left:
            node = node.left
        return node.key

def visualize_tree(root, canvas, x, y, dx):
    if root:
        canvas.create_oval(x, y, x + 30, y + 30, fill='white')
        canvas.create_text(x + 15, y + 15, text=str(root.key))
        if root.left:
            canvas.create_line(x + 15, y + 30, x - dx + 15, y + 60)
            visualize_tree(root.left, canvas, x - dx, y + 60, dx / 2)
        if root.right:
            canvas.create_line(x + 15, y + 30, x + dx + 15, y + 60)
            visualize_tree(root.right, canvas, x + dx, y + 60, dx / 2)

def insert_button_click():
    try:
        key = int(entry.get()) 
        if avl_tree.find_key(key):
            messagebox.showinfo("Error", "Key already exists")
        else:
            avl_tree.insert_key(key)
            canvas.delete("all")
            visualize_tree(avl_tree.root, canvas, 400, 50, 200)
        entry.delete(0, tk.END)
    except ValueError:
        messagebox.showinfo("Error", "Invalid Key")

def delete_button_click():
    try:
        key = int(entry.get())
        if avl_tree.delete_key(key):
            canvas.delete("all")
            visualize_tree(avl_tree.root, canvas, 400, 50, 200)
        else:
            messagebox.showinfo("Error", "Key not found")
        entry.delete(0, tk.END)
    except ValueError:
        messagebox.showinfo("Error", "Invalid Key")

def find_button_click():
    try:
        key = int(entry.get())
        node = avl_tree.find_key(key)
        if node:
            messagebox.showinfo("Search Result", f"Key {key} found")
        else:
            messagebox.showinfo("Search Result", f"Key {key} not found")
        entry.delete(0, tk.END)
    except ValueError:
        messagebox.showinfo("Error", "Invalid Key")

avl_tree = AVLTree()

root = tk.Tk()
root.title("AVL Tree Visualization")

frame = tk.Frame(root)
frame.pack(pady=10)

label = tk.Label(frame, text="Enter a key:")
label.grid(row=0, column=0)

entry = tk.Entry(frame)
entry.grid(row=0, column=1)

insert_button = tk.Button(frame, text="Insert", command=insert_button_click)
insert_button.grid(row=0, column=2)

delete_button = tk.Button(frame, text="Delete", command=delete_button_click)
delete_button.grid(row=0, column=3)

find_button = tk.Button(frame, text="Find", command=find_button_click)
find_button.grid(row=0, column=4)

canvas = tk.Canvas(root, width=800, height=400)
canvas.pack()

root.mainloop()
