#include <iostream>
#include <stdexcept>


using namespace std;



class OutOfRangeException : public exception {
public:
    const char* what() const noexcept {
        return "Значение вышло за предел";
    }
};

class IntegerRange1 {

public:
    int min;
    int max;
    int value;
    IntegerRange1() 
    {
    
    }
    IntegerRange1(int value, int maxValue = INT_MAX) {
        min = 0;
        max = maxValue;
        this->value = value;
    }

    IntegerRange1& operator=(int newValue) {
        if (newValue < min || newValue > max) {
            throw OutOfRangeException();
        }
        value = newValue;
        return *this;
    }
    IntegerRange1 operator+(int other) const {
        if (value + other < min || value + other > max) {
            throw OutOfRangeException();
        }
        IntegerRange1 result(value + other, max);
        return result;
    }

    IntegerRange1 operator-(int other) const {
        if (value - other < min || value - other > max) {
            throw OutOfRangeException();
        }
        IntegerRange1 result(value - other, max);
        return result;
    }
    int getValue() {
        return value;
    }
};


class PositiveInteger {
private:
    int value;
    int minValue;
    int maxValue;

public:
    PositiveInteger(int initialValue = 0, int min = 0, int max = 100) {
        value = initialValue;
        minValue = min;
        maxValue = max;
        if (value < minValue || value > maxValue) {
            throw OutOfRangeException();
        }
    }

    PositiveInteger& operator=(int newValue) {
        if (newValue < minValue || newValue > maxValue) {
            throw OutOfRangeException();
        }
        value = newValue;
        return *this;
    }

    PositiveInteger operator+(int other) const {
        cout << other << endl;
        system("pause");
        if (value + other < minValue || value + other > maxValue) {
            {
                cout << other << endl;
            
                system("pause");

                throw OutOfRangeException(); }
        }
        cout << other << endl;
        system("pause");

        PositiveInteger result(value + other, minValue, maxValue);
        return result;
    }

    PositiveInteger operator-(int other) const {
        if (value - other < minValue || value - other > maxValue) {
            throw OutOfRangeException();
        }
        PositiveInteger result(value - other, minValue, maxValue);
        return result;
    }

    int getValue() const {
        return value;
    }
};

class PositiveInteger1 {
private:
    IntegerRange1 range;
    int maxValue;

public:
    PositiveInteger1(IntegerRange1 range, int maxValue = 100) {

        this->range = range;
        this->maxValue = maxValue;
    }

    void operator=(int newValue) {
        range = newValue;
    }

    PositiveInteger1 operator+(int other) {
        if (range.getValue() + other > maxValue)
            throw OutOfRangeException();
        //range = range + other;
        return range;
    }

    PositiveInteger1 operator-(int other) {
        range = range - other;
        return range;
    }

    int getValue() {
        return range.getValue();
    }
};

class InvalidValueException : public exception {
public:
    const char* what() const throw() {
        return "Ошибка значения";
    }
};


//class PositiveInteger2
//{
//    IntegerRange1 range;
//public:
//    PositiveInteger2(int value, int maxValue = INT_MAX)
//    {
//        this->range.value = value;
//        this->range.max = maxValue;
//        this->range.min = 0;
//
//    }
//    PositiveInteger2(IntegerRange1* range)
//    {
//        this->range = *range;
//    }
//
//    PositiveInteger2& operator=(int newValue)
//    {
//        try 
//        {
//            range = newValue;
//        }
//        catch(...)
//        {
//            throw InvalidValueException();
//        }
//        return *this;
//    }
//    PositiveInteger2 operator+(int other)
//    {
//        try
//        {
//            range = range + other;
//        }
//        catch (...)
//        {
//            throw InvalidValueException();
//        }
//
//        PositiveInteger2 r(this->range);
//        return r;
//    }
//
//
//    int getValue() 
//    {
//        return range.getValue();
//    }
//
//};





void zadanie_4()
{
    PositiveInteger pos(100, 0, 1300);
    cout << pos.getValue() << endl;
    pos = 1220;
    pos = pos + 1322;



}

int main() 
{
    setlocale(LC_ALL, "RUS");
    zadanie_4();
    return 0;
}