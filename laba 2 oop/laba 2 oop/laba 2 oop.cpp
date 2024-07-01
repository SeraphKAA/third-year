//1. Для решения различных задач используются методы
//Монте - Карло, предполагающие применение массивов случайных
//чисел с большим количеством элементов.Размер массива
//становится известным во время выполнения программы, т.е.
//массив должен создаваться динамически.Создайте две функции
//для решения одной и той же задачи : динамическое создание и
//заполнение случайными числами массива указанного размера.
//Первая функция должна использовать возвращаемое значение
//для передачи пользователю сгенерированного массива, а вторая
//должна передавать массив через один из своих аргументов.
//Стандартная библиотека Си содержит функции int rand() и void
//srand(unsigned) для генерации псевдослучайных чисел
//(прототипы в файле stdlib.h).
//2. Создать класс Person содержащий следующие поля :
//-фамилия и имя человека - произвольная длина
//- профессия человека - произвольная длина
//- возраст человека.
//3. Определить конструктор для инициализации полей
//класса со значениями по умолчанию.Определить конструктор
//копирования, операцию присваивания и деструктор.Написать
//тестовый пример.
//4. Написать интерфейсные функции доступа к полям класса
//(получить / задать значение поля).
//5. Внести в конструкторы, операцию присваивания и
//деструктор выдачу сообщений на экран о том, какая функция
//была вызвана.Модифицировать функцию main следующим
//образом :
//void main(void)
//{
//    cout << "Вход в функцию main()" << endl;
//    ...
//        <тело_main()>
//        ...
//        Управление дистанционного обучения и повышения квалификации
//        Объектно - ориентированное программирование
//        13
//        cout << "Выход из функции main()" << endl;
//}
//6. Задать глобальную функцию Person test(Person s) {
//    return
//        s;
//}
//Вызвать ее в основной программе.Что произошло и
//почему ?
//7. Изменить передачу параметра функции test на передачу
//по ссылке.
//Что изменилось ?
//8. Изменить возврат результата функции test на передачу
//по ссылке.
//Что изменилось ?


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "string.h"

#pragma warning(disable : 4996)

using namespace std;

// Function to dynamically create and fill an array with random numbers
int* generateArray(int size) {
    int* arr = new int[size];
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
    return arr;
}

// Function to fill an array with random numbers passed as an argument
void fillArray(int* arr, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

class Person {
private:
    char* name;
    char* profession;
    int age;

public:
    // Default constructor
    Person() {
        name = new char[1];
        name[0] = '\0';
        profession = new char[1];
        profession[0] = '\0';
        age = 0;
        cout << "Основной конструктор вызван" << endl;
    }

    // Parameterized constructor
    Person(const char* n, const char* p, int a) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        profession = new char[strlen(p) + 1];
        strcpy(profession, p);
        age = a;
        cout << "Параметризированный конструктор вызван" << endl;
    }

    // Copy constructor
    Person(const Person& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        profession = new char[strlen(other.profession) + 1];
        strcpy(profession, other.profession);
        age = other.age;
        cout << "Оператор копирования вызван" << endl;
        if (age < 18)
        {
            age = 18;
        }
    }

    // Assignment operator
    Person& operator=(const Person& other) {
        if (this != &other) {
            delete[] name;
            delete[] profession;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            profession = new char[strlen(other.profession) + 1];
            strcpy(profession, other.profession);
            age = other.age;
            if (age < 18)
            {
                age = 18;
            }
        }
        cout << "Оператор присваивания вызван" << endl;
        return *this;
    }

    // Destructor
    ~Person() {
        delete[] name;
        delete[] profession;
        cout << "Деструктор активирован" << endl;
    }

    // Access functions
    const char* getName() const {
        return name;
    }

    const char* getProfession() const {
        return profession;
    }

    int getAge() const {
        return age;
    }

    void setName(const char* n) {
        delete[] name;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    void setProfession(const char* p) {
        delete[] profession;
        profession = new char[strlen(p) + 1];
        strcpy(profession, p);
    }

    void setAge(int a) {
        age = a;
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    // Test the dynamic array generation functions
    int arraySize;
    cout << "Напишите размерность массива: ";
    cin >> arraySize;

    int* arr1 = generateArray(arraySize);
    cout << "Массив создан с помощью return value:" << endl;
    for (int i = 0; i < arraySize; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    delete[] arr1;

    int* arr2 = new int[arraySize];
    fillArray(arr2, arraySize);
    cout << "Массив создан с помощью argument:" << endl;
    for (int i = 0; i < arraySize; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl << endl;
    delete[] arr2;



    // Test the Person class
    Person p1;
    cout << "Name: " << p1.getName() << endl;
    cout << "Profession: " << p1.getProfession() << endl;
    cout << "Age: " << p1.getAge() << endl << endl;

    Person p2("Kizogyan Arman", "Neuch", 15);
    cout << "Name: " << p2.getName() << endl;
    cout << "Profession: " << p2.getProfession() << endl;
    cout << "Age: " << p2.getAge() << endl << endl;

    p1 = p2;
    cout << "Name: " << p1.getName() << endl;
    cout << "Profession: " << p1.getProfession() << endl;
    cout << "Age: " << p1.getAge() << endl;

    cout << "Выход из функции main()" << endl;
}
//конструктор копирования от 18 лет минимум