from tkinter import *
class BTreeNode:
    def __init__(self, leaf=False):
        self.leaf = leaf
        self.keys = []
        self.child = []

class BTree:
    def __init__(self, t):
        self.root = BTreeNode(True)
        self.t = t
        self.ex_key = []
    def insert(self, k):
        if k in self.ex_key:
            return
        self.ex_key.append(k)
        root = self.root
        if len(root.keys) == (2 * self.t) - 1:
            temp = BTreeNode()
            self.root = temp
            temp.child.insert(0, root)
            self.__split_child(temp, 0)
            self.__insert_non_full(temp, k)
        elif len(root.keys) == self.t - 1:
            self.__insert_non_full(root, k)
        else:
            self.__insert_non_full(root, k)

    def __insert_non_full(self, x, k):
        i = len(x.keys) - 1
        if x.leaf:
            while i >= 0 and k[0] < x.keys[i][0]:
                i -= 1
            x.keys.insert(i + 1, k)
        else:
            while i >= 0 and k[0] < x.keys[i][0]:
                i -= 1
            i += 1
            if len(x.child[i].keys) == (2 * self.t) - 1:
                self.__split_child(x, i)
                if k[0] > x.keys[i][0]:
                    i += 1
            self.__insert_non_full(x.child[i], k)

    def __split_child(self, x, i):
        t = self.t
        y = x.child[i]
        z = BTreeNode(leaf=y.leaf)
        x.child.insert(i + 1, z)
        x.keys.insert(i, y.keys[t - 1])
        z.keys = y.keys[t: (2 * t) - 1]
        y.keys = y.keys[0: t - 1]
        if not y.leaf:
            z.child = y.child[t: 2 * t]
            y.child = y.child[0: t - 1]

    def print_tree(self, x, l=0):
        print("Level ", l, " ", len(x.keys), end=":")
        for i in x.keys:
            print(i, end=" ")
        print()
        l += 1
        if len(x.child) > 0:
            for i in x.child:
                self.print_tree(i, l)

    def search_key(self, k, x=None):
        if x is not None:
            i = 0
            while i < len(x.keys) and k > x.keys[i][0]:
                i += 1
            if i < len(x.keys) and k == x.keys[i][0]:
                return (x.keys, i)
            elif x.leaf:
                return None
            else:
                return self.search_key(k, x.child[i])
        else:
            return self.search_key(k, self.root)

    def delete(self, x, k):
        t = self.t
        i = 0
        while i < len(x.keys) and k[0] > x.keys[i][0]:
            i += 1
        if x.leaf:
            if i < len(x.keys) and x.keys[i][0] == k[0]:
                x.keys.pop(i)
                return
            return

        if i < len(x.keys) and x.keys[i][0] == k[0]:
            return self.delete_internal_node(x, k, i)
        elif len(x.child[i].keys) >= t:
            self.delete(x.child[i], k)
        else:
            if i != 0 and i + 2 < len(x.child):
                if len(x.child[i - 1].keys) >= t:
                    self.delete_sibling(x, i, i - 1)
                elif len(x.child[i + 1].keys) >= t:
                    self.delete_sibling(x, i, i + 1)
                else:
                    self.delete_merge(x, i, i + 1)
            elif i == 0:
                if len(x.child[i + 1].keys) >= t:
                    self.delete_sibling(x, i, i + 1)
                else:
                    self.delete_merge(x, i, i + 1)
            elif i + 1 == len(x.child):
                if len(x.child[i - 1].keys) >= t:
                    self.delete_sibling(x, i, i - 1)
                else:
                    self.delete_merge(x, i, i - 1)
            self.delete(x.child[i], k)

    def delete_internal_node(self, x, k, i):
        t = self.t
        if x.leaf:
            if x.keys[i][0] == k[0]:
                x.keys.pop(i)
                return
            return

        if len(x.child[i].keys) >= t:
            x.keys[i] = self.delete_predecessor(x.child[i])
            return
        elif len(x.child[i + 1].keys) >= t:
            x.keys[i] = self.delete_successor(x.child[i + 1])
            return
        else:
            self.delete_merge(x, i, i + 1)
            self.delete_internal_node(x.child[i], k, self.t - 1)

    def delete_predecessor(self, x):
        if x.leaf:
            return x.pop()
        n = len(x.keys) - 1
        if len(x.child[n].keys) >= self.t:
            self.delete_sibling(x, n + 1, n)
        else:
            self.delete_merge(x, n, n + 1)
        self.delete_predecessor(x.child[n])

    def delete_successor(self, x):
        if x.leaf:
            return x.keys.pop(0)
        if len(x.child[1].keys) >= self.t:
            self.delete_sibling(x, 0, 1)
        else:
            self.delete_merge(x, 0, 1)
        self.delete_successor(x.child[0])

    def delete_merge(self, x, i, j):
        cnode = x.child[i]

        if j > i:
            rsnode = x.child[j]
            cnode.keys.append(x.keys[i])
            for k in range(len(rsnode.keys)):
                cnode.keys.append(rsnode.keys[k])
                if len(rsnode.child) > 0:
                    cnode.child.append(rsnode.child[k])
            if len(rsnode.child) > 0:
                cnode.child.append(rsnode.child.pop())
            new = cnode
            x.keys.pop(i)
            x.child.pop(j)
        else:
            lsnode = x.child[j]
            lsnode.keys.append(x.keys[j])
            for i in range(len(cnode.keys)):
                lsnode.keys.append(cnode.keys[i])
                if len(lsnode.child) > 0:
                    lsnode.child.append(cnode.child[i])
            if len(lsnode.child) > 0:
                lsnode.child.append(cnode.child.pop())
            new = lsnode
            x.keys.pop(j)
            x.child.pop(i)

        if x == self.root and len(x.keys) == 0:
            self.root = new

    def delete_sibling(self, x, i, j):
        cnode = x.child[i]
        if i < j:
            rsnode = x.child[j]
            cnode.keys.append(x.keys[i])
            x.keys[i] = rsnode.keys[0]
            if len(rsnode.child) > 0:
                cnode.child.append(rsnode.child[0])
                rsnode.child.pop(0)
            rsnode.keys.pop(0)
        else:
            lsnode = x.child[j]
            cnode.keys.insert(0, x.keys[i - 1])
            x.keys[i - 1] = lsnode.keys.pop()
            if len(lsnode.child) > 0:
                cnode.child.insert(0, lsnode.child.pop())

window = Tk()
window.geometry("1000x1000")
window.title("B-дерево")

def create_btree():
    order = int(Por_entry.get())
    global B
    B = BTree(order)
    create_tree["state"] = "disabled"
    Por_entry["state"] = "disabled"
    insert_node_tree.config(state=NORMAL)
    insert_button.config(state=NORMAL)
    show_button.config(state=NORMAL)
    del_key.config(state=NORMAL)
    del_button.config(state=NORMAL)
    finded_key.config(state=NORMAL)
    find_button.config(state=NORMAL)

def insert_node():
    keys = insert_node_tree.get().split()
    for key in keys:
     B.insert((int(key), 2 * int(key)))
    insert_node_tree.delete(0, END)

def display_btree():
    canvas.delete("all")
    B.print_tree(B.root)

def show_btree():
    canvas.delete("all")
    draw_tree(B.root, 500, 50, 200)
def delete_node():
    key = int(insert_node_tree.get())
    B.delete(B.root,[key, key * 2])

def draw_tree(node, x, y, spacing):
    canvas.create_rectangle(x-20, y-10, x+20, y+10, fill="lightblue")
    canvas.create_text(x, y, text=" ".join(str(i[0]) for i in node.keys), fill="black")
    if not node.leaf:
        for i, child in enumerate(node.child):
            child_x = x + (i - len(node.child)//2) * spacing
            child_y = y + 50
            canvas.create_line(x, y+10, child_x, child_y-10)
            draw_tree(child, child_x, child_y, spacing//len(node.child))

def find_key():
    key = int(insert_node_tree.get())
    finded = B.search_key(key)
    if finded == None:
        finded_key.config(text="Ключа не существует")
        return
    finded_key.config(text="Ключ " + str(finded[0][0][0]) + "есть в дереве")

Por_label = Label(window, text="Введите порядок дерева")
Por_entry = Entry(window)

create_tree = Button(window, text="Создать дерево", command=create_btree)

node_tree = Label(window, text="Введите значения ключей")
insert_node_tree = Entry(window,state=DISABLED)

insert_button = Button(window, text="Принять", command=insert_node,state=DISABLED)

del_key = Entry(window,state=DISABLED)
del_button = Button(window,text="Удалить", command=delete_node,state=DISABLED)

find_button = Button(window,text="Найти ключ",command=find_key,state=DISABLED)

show_button = Button(window, text="Show B-дерево", command=show_btree,state=DISABLED)
finded_key = Label(window)

canvas = Canvas(window, width=1000, height=1000)

Por_label.pack()
Por_entry.pack()
create_tree.pack()
node_tree.pack()
insert_node_tree.pack()
insert_button.pack()
del_button.pack()
show_button.pack()
find_button.pack()
finded_key.pack()
canvas.pack()

window.mainloop()
