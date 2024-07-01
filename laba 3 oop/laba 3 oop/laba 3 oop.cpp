﻿//1. Создайте класс List, представляющий понятие
    //"двунаправленный список".
//2. Создайте класс, реализующий простое текстовое меню.
    //Используйте его для тестирования созданного в предыдущем
    //задании класса List.
//3. Создайте классы стек и очередь на основе класса List с
    //помощью агрегирования.
//4. Создайте классы стек и очередь на основе класса List с
    //помощью наследования.
//5. Сравните реализации стека и очереди и сделайте
    //вывод, какое отношение между классами агрегирование или
    //наследование является правильным при построении очереди и
    //стека на основе списка.

#include <iostream>
#include <List>
#include <stdlib.h>

using namespace std;

struct Node                            //Структура, являющаяся звеном списка
{
    int x;                             //Значение x будет передаваться в список
    Node* Next, * Prev;                //Указатели на адреса следующего и предыдущего элементов списка
};

class List                              //Создаем тип данных Список
{
public:
    Node* Head, * Tail;                 //Указатели на адреса начала списка и его конца
    List() :Head(NULL), Tail(NULL) {};  //Инициализируем адреса как пустые
    ~List();                           //Прототип деструктора
    void Show_Last();                  //Прототип функции отображения списка на экране
    void Show_First();
    void Add(int x);                   //Прототип функции добавления элементов в список
    void Sort();
    void removeMiddleElement();
};

void List::Sort()
{
    if (Head == NULL)                    // Если список пуст, то сортировка не требуется
        return;

    bool swapped;                        // Булевая переменная для отслеживания выполнения обмена элементов
    Node* current;                       // Указатель на текущий элемент
    Node* temp = NULL;                   // Временный указатель для обмена значениями

    do
    {
        swapped = false;                 // Устанавливаем флаг обмена в false
        current = Head;                   // Инициализируем текущий элемент с начала списка

        while (current->Next != NULL)    // Итерируемся по списку
        {
            if (current->x > current->Next->x)     // Если текущий элемент больше следующего элемента
            {
                // Обмен значениями
                temp = current->Next;
                current->Next = temp->Next;

                if (temp->Next != NULL)
                    temp->Next->Prev = current;
                temp->Prev = current->Prev;

                if (current->Prev != NULL)
                    current->Prev->Next = temp;
                else
                    Head = temp;
                current->Prev = temp;
                temp->Next = current;

                swapped = true;          // Устанавливаем флаг обмена в true
            }
            else
            {
                current = current->Next;  // Переходим к следующему элементу
            }
        }
    } while (swapped);                   // Повторяем сортировку, пока обмен происходит

    Tail = current;                      // Устанавливаем конец списка на последний отсортированный элемент
}

List::~List()                           //Деструктор
{
    while (Head)                       //Пока по адресу на начало списка что-то есть
    {
        Tail = Head->Next;             //Резервная копия адреса следующего звена списка
        delete Head;                   //Очистка памяти от первого звена
        Head = Tail;                   //Смена адреса начала на адрес следующего элемента
    }
}

void List::Add(int x)
{
    Node* temp = new Node;               //Выделение памяти под новый элемент структуры
    temp->Next = NULL;                   //Указываем, что изначально по следующему адресу пусто
    temp->x = x;                         //Записываем значение в структуру

    if (Head != NULL)                    //Если список не пуст
    {
        temp->Prev = Tail;               //Указываем адрес на предыдущий элемент в соотв. поле
        Tail->Next = temp;               //Указываем адрес следующего за хвостом элемента
        Tail = temp;                     //Меняем адрес хвоста
    }
    else //Если список пустой
    {
        temp->Prev = NULL;               //Предыдущий элемент указывает в пустоту
        Head = Tail = temp;              //Голова=Хвост=тот элемент, что сейчас добавили
    }
}

void List::Show_First()
{
    //ВЫВОДИМ СПИСОК С НАЧАЛА
    Node* temp = Head;                       //Временно указываем на адрес первого элемента
    while (temp != NULL)              //Пока не встретим пустое значение
    {
        cout << temp->x << " ";        //Выводим каждое считанное значение на экран
        temp = temp->Next;             //Смена адреса на адрес следующего элемента
    }
    cout << "\n";
}

void List::Show_Last()
{
    //ВЫВОДИМ СПИСОК С КОНЦА
    Node* temp = Tail;                   //Временный указатель на адрес последнего элемента

    while (temp != NULL)               //Пока не встретится пустое значение
    {
        cout << temp->x << " ";        //Выводить значение на экран
        temp = temp->Prev;             //Указываем, что нужен адрес предыдущего элемента
    }
    cout << "\n";
}



void List::removeMiddleElement() {
    Node* slowPointer = Head; // указатель, двигающийся на один элемент за раз
    Node* fastPointer = Head; // указатель, двигающийся на два элемента за раз
    Node* prev = NULL; // указатель предыдущего элемента

    // Пройдемся по списку, пока fastPointer не достигнет конца
    while (fastPointer != NULL && fastPointer->Next != NULL) {
        fastPointer = fastPointer->Next->Next; // двигаем быстрый указатель на два элемента
        prev = slowPointer; // сохраняем указатель на предыдущий элемент
        slowPointer = slowPointer->Next; // двигаем медленный указатель на один элемент
    }

    // Проверяем, находится ли slowPointer на центральном элементе
    if (slowPointer != NULL) {
        // Удаляем центральный элемент
        if (prev != NULL) {
            // Если предыдущий элемент существует, перенаправляем его указатель на следующий элемент
            prev->Next = slowPointer->Next;
        }
        else {
            // Если предыдущего элемента нет, то это значит, что центральный элемент является началом списка
            // Перенаправляем указатель на следующий элемент и делаем его новым началом списка
            Head = slowPointer->Next;
        }

        delete slowPointer; // освобождаем память, занятую центральным элементом
    }
}

class interface0 
{
public:
    void Start();
};

void interface0::Start()
{
    List lst;
    int vib;

    while (true)
    {
        system("ClS");
        cout << "Выберите то что вам надо:\n  1. Добавление элемента в список\n  2. Вывод в консоль списка с начала\n" << 
                "  3. Вывод в консоль списка с конца\n  4. сортировка списка\n  5. Окончание работы программы\n";
        cin >> vib;
        
        switch (vib)
        {
        case 1:
            int value;
            cout << "Введите значение: " << endl;
            cin >> value;
            lst.Add(value);
            break;
        
        case 2:
            lst.Show_First();
            system("PAUSE");
            break;

        case 3:
            lst.Show_Last();
            system("PAUSE");
            break;
        
        case 4:
            lst.Sort();
            break;

        case 5:
        default:
            return;
        }

    }
};

class Stack1
{
public: 
    List lst;
    Stack1(List anything)
    {
        this->lst = anything;
    }

    int Pop()             //Метод для извлечения элемента из стека
    {
        if (lst.Head == NULL) //Если стек пустой
        {
            cout << "Стек пуст" << endl;
            return -1;   //Возвращаем значение -1, чтобы показать, что стек пустой
        }
        else
        {
            int x = lst.Head->x;            //Сохраняем значение первого элемента стека
            Node* temp = lst.Head;          //Сохраняем указатель на первый элемент стека
            lst.Head = lst.Head->Next;      //Переустанавливаем голову на следующий элемент
            delete temp;                    //Освобождаем память от предыдущего первого элемента
            return x;                       //Возвращаем сохраненное значение
        }
    }

    void Add(int value) 
    {
        lst.Add(value);
    }

    void Show() 
    {
        lst.Show_First();
    }
    
    void Pop_midl()
    {
        Node* temp = new Node;               //Выделение памяти под новый элемент структуры
        temp->Next = NULL;                   //Указываем, что изначально по следующему адресу пусто                         //Записываем значение в структуру

        if (lst.Head != NULL)                    //Если список не пуст
        {
            temp->Prev = lst.Tail;               //Указываем адрес на предыдущий элемент в соотв. поле
            lst.Tail->Next = temp;               //Указываем адрес следующего за хвостом элемента
            lst.Tail = temp;
    }
};

class Stack2 : public List
{
public:
    void Push(int x)      //Метод для добавления элемента в стек
    {
        Add(x);     //Вызываем метод добавления на первую позицию списка
    }

    int Pop()             //Метод для извлечения элемента из стека
    {
        if (Head == NULL) //Если стек пустой
        {
            cout << "Stack is empty" << endl;
            return -1;   //Возвращаем значение -1, чтобы показать, что стек пустой
        }
        else
        {
            int x = Head->x;        //Сохраняем значение первого элемента стека
            Node* temp = Head;      //Сохраняем указатель на первый элемент стека
            Head = Head->Next;      //Переустанавливаем голову на следующий элемент
            delete temp;            //Освобождаем память от предыдущего первого элемента
            return x;               //Возвращаем сохраненное значение
        }
    }
};

class Queue1 
{
public:
    List lst;
    Queue1(List anything)
    {
        this->lst = anything;
    }

    void Delete_last()
    {
        if (lst.Tail == NULL)                   //Если список пустой
        {
            return;                         //Выходим из метода
        }
        else if (lst.Head == lst.Tail)              //Если список содержит только один элемент
        {
            delete lst.Tail;                    //Освобождаем память от этого элемента
            lst.Head = lst.Tail = NULL;             //Обнуляем указатели на начало и конец списка
        }
        else                                //Если список содержит более одного элемента
        {
            Node* temp = lst.Tail->Prev;        //Временный указатель на предыдущий элемент от конца списка
            delete lst.Tail;                    //Освобождаем память от последнего элемента
            lst.Tail = temp;                    //Указываем новый конец списка
            lst.Tail->Next = NULL;              //Указываем, что новый конец списка указывает на пустое значение
        }
    }

    void Add_first(int value)
    {
        Node* temp = new Node;               //Выделение памяти под новый элемент структуры
        temp->Prev = NULL;                   //Указываем, что изначально по предыдущему адресу пусто
        temp->x = value;                         //Записываем значение в структуру

        if (lst.Head != NULL)                    //Если список не пуст
        {
            temp->Next = lst.Head;               //Устанавливаем указатель на следующий элемент на текущую голову
            lst.Head->Prev = temp;               //Устанавливаем указатель на предыдущий элемент текущей головы на новый элемент
            lst.Head = temp;                     //Меняем адрес головы на новый элемент
        }
        else //Если список пустой
        {
            temp->Next = NULL;               //Следующий элемент указывает в пустоту
            lst.Head = lst.Tail = temp;              //Голова=Хвост=тот элемент, что сейчас добавили
        }
    }

    void Show()
    {
        lst.Show_First();
    }
};

class Queue2 : public List
{
public:
    void Enqueue(int x);            //Прототип функции добавления элемента в очередь
    void Dequeue();                 //Прототип функции удаления элемента из очереди
};

void Queue2::Enqueue(int x)
{
    Node* temp = new Node;               //Выделение памяти под новый элемент структуры
    temp->Prev = NULL;                   //Указываем, что изначально по предыдущему адресу пусто
    temp->x = x;                         //Записываем значение в структуру

    if (Head != NULL)                    //Если список не пуст
    {
        temp->Next = Head;               //Устанавливаем указатель на следующий элемент на текущую голову
        Head->Prev = temp;               //Устанавливаем указатель на предыдущий элемент текущей головы на новый элемент
        Head = temp;                     //Меняем адрес головы на новый элемент
    }
    else //Если список пустой
    {
        temp->Next = NULL;               //Следующий элемент указывает в пустоту
        Head = Tail = temp;              //Голова=Хвост=тот элемент, что сейчас добавили
    }
}

void Queue2::Dequeue()
{
    if (Head != NULL)               //Если список не пуст
    {
        Node* temp = Head;         //Временный указатель на адрес начала списка
        Head = Head->Next;         //Смена адреса начала на адрес следующего элемента
        delete temp;               //Освобождение памяти от временного элемента
    }
}


int main()
{
    setlocale(LC_ALL, "rus");
    system("CLS");
    
    interface0 st;

    st.Start();

    //List lst;

    //Stack1 stp = Stack1(lst);
    //stp.Add(12);
    //stp.Add(34);
    //stp.Add(52);
    //stp.Show();

    //stp.Delete_last();
    //stp.Show();
 

    //Stack2 stp = Stack2();
    //stp.Add(12);
    //stp.Add(34);
    //stp.Add(52);
    //stp.Show_First();

    //stp.Pop();
    //stp.Show_First();


    //Queue1 queue1 = Queue1(lst);
    //queue1.Add_first(12);
    //queue1.Add_first(23);
    //queue1.Add_first(34);
    //queue1.Show();
    //
    //queue1.Delete_last();
    //queue1.Show();

    //Queue2 que = Queue2();
    //que.Enqueue(12);
    //que.Enqueue(2312);
    //que.Enqueue(1242);
    //que.Show_First();

    //que.Dequeue();
    //que.Show_First();

    return 0;

}

// для двунаправленного 