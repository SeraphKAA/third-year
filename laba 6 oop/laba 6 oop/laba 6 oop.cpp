#include <iostream>
#include <string>

using namespace std;

void ff()
{
    cout << "Na global urovne\n";
}

class base 
{
public:
    int i;
    base(int i, long l, double d)
    {
        this->i = i;
        this->l = l;
        this->d = d;
    }

    void a(int d)
    {
        this->d = d;
    }

    double d_c()
    {
        return d;
    }

    int d_c_pr() 
    {
        cout << "\nd: " << &d << " ";
        return 0;
    }

    void ff()
    {
        cout << typeid(*this).name() << endl;
    }



protected:
    long l;

private:
    double d;
};

class Derived : public base 
{
private:
    float f;

public:

    Derived() : base(0, 0, 0.0), f(0) 
    {
        cout << endl << "i: " << &i << " " << i << "\nl: " << &l << " " << l; d_c_pr(); cout << d_c() << "\nf: " << &f << " " << f << endl << endl;
    }

    Derived(int i, long l, double d, float f) : base(i, l, d), f(f) 
    {
        cout << endl << "i: " << &i << " " << i << "\nl: " << &l << " " << l; d_c_pr(); cout << d_c() << "\nf: " << &f << " " << f << endl << endl;
    }
    float f_c() 
    {
        return f;
    }

protected:
    void ff()
    {
        cout << typeid(*this).name() << endl;
    }
};

class Derived1 : public Derived
{
public:
    void foo() 
    {
        i++;
        l += 1;
        ::ff();
        base::ff();
        this->ff();
        this->print();
    }

    Derived1(int i, long l, double d, float f) : Derived(i, l, d, f) {}

    void print() 
    {
        cout << "fooo:" << endl << "i = " << i << "\nl = " << l << "\nd = " << d_c() << "\nf = " << f_c() << endl << endl;
    }
};






//int main()
//{
//    setlocale(LC_ALL, "RUS");
//    
//    // #1
//    base bases = base(1, 2, 10.2);
//
//    // #2
//    Derived deri = Derived();
//    Derived der = Derived(3, 4, 5.2, 2.2);
//
//    // #3
//    cout << sizeof(bases) << endl;
//    cout << sizeof(der) << endl;
//
//    // #4
//    // #5+
//
//    // #6-8
//    Derived1 derr = Derived1(1, 2, 3.3, 2.6);
//    derr.foo();
//}
