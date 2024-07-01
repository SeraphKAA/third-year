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
            name[i] = "�����";
        }
    }

    void put(string one_name)
    {
        //strcpy(name, one_name);

        for (int i = 0; i < 20; i++)
        {
            if (name[i] == "�����")
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
        os << "�������� i: " << obj.base1.get() << endl;
        os << "�������� name: " << endl;
        string* temp = obj.base2.get();
        for (int i = 0; i < capacity; i++) 
        {
            os << temp[i] << endl;

        }

        os << "�������� ch: " << obj.get() << endl;
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
    cout << "�������� ������� ������, ����� � ����� �����" << endl;
    cin >> a >> b >> c;
    Derived d1 = Derived(a, b, c);
    cout << d1;


}

//9. ����� Base1, ����� ���� �������� ���� i ������ ����.
//������ ����������� �� ����� ���������� � �������� i.������
//����� ���� �������� ���� int, ������������ ��� ������������� i
//������������� ����������.����� ����� ��� �������������
//������������ ������� void put(int) � int get(void), �������
//��������� �������� ��� �������� �������� i.����� Base2, �����
//���� �������� ���� - ������ name �� 20 ���������.������
//����������� �� ����� ���������� � �������������� ���� name
//������ "�����".������ ����� ���� �������� ���� char*,
//������������ ��� ������������� name ���������� ����������
//�����.����� ����� ��� ������������� ������������ �������
//void put(char*) � char* get(void), ������� ��������� �������� ���
//�������� �������� name.����� Derived ����� ���� �������� ����
//ch ���� char.������ ����������� �� ����� ���������� �
//����������� ch �������� 'V' (�� void - ������).������ �����������
//����� ��� ��������� ����� char, char* � int, ������������ ���
//������������� �������������� ����� ch, name � i.����� �����
//��� ������������� ������������ ������� void put(char) � char
//get(void), ������� ��������� �������� ��� �������� �������� ch.
//����� ����, � ��� ����������� ��� ������������� ��������
//������� � ����� ������, ������� ������� �� ����� �������� i,
//name � ch.
// 
// 
//�).� ������� main ������� ���������� ���� Derived ���
//������������� � ������� �� �������� � ������� �������������
//�������� ������� � �����.�������� ������� ������
//�������������.
//�).������� ������ ���������� ������ Derived,
//��������������� �� ���� ���������� ����������.�������
//�������� ���� ���������� �� ����� � ���������������� �������
//������ �������������.
//�).� ������������ ������ Derived � ����������� ��������
//������� ������ ������������� ������� �������.���������, ���
//��� ���������� �� ������ ��������� � ������.
//�).�������� ������� ������������ ������� ������� �
//�������� ������ Derived � ���������, ��� ��� ���������� ��
//������ ���������.