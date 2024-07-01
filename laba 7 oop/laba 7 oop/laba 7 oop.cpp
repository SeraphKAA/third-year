#include <iostream>
#include <stdexcept>


using namespace std;

class Array {
private:
    int* arr;
    int size;
public:
    Array(int size) {
        this->size = size;
        arr = new int[size];
    }
    ~Array() {
        delete[] arr;
    }
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Индекс вышел за предел");
        }
        return arr[index];
    }
};

void zadanie_1() {
    Array arr(5);
    try {
        arr[0] = 10;
        arr[1] = 20;
        arr[2] = 30;
        arr[3] = 40;
        arr[4] = 50;
        arr[5] = 60; // Возникнет исключение
    }
    catch (out_of_range& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}


class OutOfRangeException : public exception {
public:
    const char* what() const noexcept {
        return "Значение вышло за предел";
    }
};

class IntegerRange {
private:
    int min;
    int max;
    int value;
public:
    IntegerRange(int value, int minValue = INT_MIN, int maxValue = INT_MAX) {
        min = minValue;
        max = maxValue;
        this->value = value;
    }
    IntegerRange& operator=(int newValue) {
        if (newValue < min || newValue > max) {
            throw OutOfRangeException();
        }
        value = newValue;
        return *this;
    }
    IntegerRange operator+(int other) const {
        if (value + other < min || value + other > max) {
            throw OutOfRangeException();
        }
        IntegerRange result(value + other, min, max);
        return result;
    }
    IntegerRange operator-(int other) const {
        if (value - other < min || value - other > max) {
            throw OutOfRangeException();
        }
        IntegerRange result(value - other, min, max);
        return result;
    }
    int getValue() const {
        return value;
    }
};

void zadanie_2() {
    IntegerRange range(0, 10);
    try {
        range = 5;
        range = -55; // Возникнет исключение
    }
    catch (OutOfRangeException& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}


//int main() 
//{
//    setlocale(LC_ALL, "RUS");
//    zadanie_2();
//    return 0;
//}