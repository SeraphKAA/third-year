#include <iostream>
#include <string>

using namespace std;



class Base1
{
    int i;
public:
    friend class Derived;

    Base1() : i(0) {}
    Base1(int val) : i(val) {}
    void put(int i)
    {
        this->i = i;
    }
    int get()
    {
        return i;
    }

};

#define capacity 20

class Base2
{
    string name[capacity];

public:
    friend class Derived;

    Base2()
    {
        for (int i = 0; i < 20; i++)
        {
            name[i] = "Пусто";
        }
    }

    void put(string one_name)
    {
        //strcpy(name, one_name);

        for (int i = 0; i < 20; i++)
        {
            if (name[i] == "Пусто")
            {
                name[i] = one_name;
                return;
            }
        }
    }
    string* get()
    {
        return name;
    }
};

class Derived
{
    char ch;
    Base1 base1 = Base1();
    Base2 base2 = Base2();
public:
    
    Derived(): ch('V') {}
    Derived(char ch, string name, int i): ch(ch)
    {
        base1.put(i);
        base2.put(name);
    }


    void put(char ch) 
    {
        this->ch = ch;
    }

    char get()
    {
        return ch;
    }

    friend ostream& operator << (ostream& os, Derived obj)
    {
        os << "Значение i: " << obj.base1.get() << endl;
        os << "Значение name: " << endl;
        string* temp = obj.base2.get();
        for (int i = 0; i < capacity; i++) 
        {
            os << temp[i] << endl;

        }

        os << "Значение ch: " << obj.get() << endl;
        return os;
    }
};



int main()
{
    setlocale(LC_ALL, "RUS");

    // #9
    //Base2 a = Base2();

    //string* b = a.get();
    //a.put("asdads");
    //a.put("asdads");
    //for (int i = 0; i < capacity; i++)
    //{
    //    cout << b[i] << endl;
    //}
    
    Derived d = Derived();
    cout << d;

    char a;
    string b;
    int c;
    cout << "Напишите сначала символ, слово и целое число" << endl;
    cin >> a >> b >> c;
    Derived d1 = Derived(a, b, c);
    cout << d1;


}

//9. Класс Base1, имеет одно закрытое поле i целого типа.
//Первый конструктор не имеет параметров и обнуляет i.Второй
//имеет один параметр типа int, используемый для инициализации i
//произвольными значениями.Класс имеет две общедоступные
//интерфейсные функции void put(int) и int get(void), которые
//позволяют изменить или прочесть значение i.Класс Base2, имеет
//одно закрытое поле - массив name из 20 элементов.Первый
//конструктор не имеет параметров и инициализирует поле name
//словом "Пусто".Второй имеет один параметр типа char*,
//используемый для инициализации name значениями символьных
//строк.Класс имеет две общедоступные интерфейсные функции
//void put(char*) и char* get(void), которые позволяют изменить или
//прочесть значение name.Класс Derived имеет одно закрытое поле
//ch типа char.Первый конструктор не имеет параметров и
//присваивает ch значение 'V' (от void - пустой).Второй конструктор
//имеет три параметра типов char, char* и int, используемые для
//инициализации соответственно полей ch, name и i.Класс имеет
//две общедоступные интерфейсные функции void put(char) и char
//get(void), которые позволяют изменить или прочесть значение ch.
//Кроме того, в нем объявляется как дружественная операция
//вставки в поток вывода, которая выводит на экран значения i,
//name и ch.
// 
// 
//а).В функции main описать переменную типа Derived без
//инициализации и вывести ее значение с помощью перегруженной
//операции вставки в поток.Выяснить порядок вызова
//конструкторов.
//б).Описать другую переменную класса Derived,
//инициализировав ее явно некоторыми значениями.Вывести
//значение этой переменной на экран и проанализировать порядок
//вызова конструкторов.
//в).В конструкторе класса Derived с параметрами изменить
//порядок вызова конструкторов базовых классов.Проверить, как
//это отразилось на работе программы и почему.
//г).Изменить порядок наследования базовых классов в
//описании класса Derived и проверить, как это отразилось на
//работе программы.