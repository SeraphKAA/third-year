#include <iostream>
#include <string>

using namespace std;

struct Student
{
    string Name;
    string Surname;
    string Patronymic;
    int Year_Birthday;
    string Group;

    Student()
    {
        Name = "-";
        Surname = "-";
        Patronymic = "-";
        Year_Birthday = 2003;
        Group = "-";
    }


    Student(Student& x)
    {
        cout << "\nБлок копирования активирован\n";
        this->Name = x.Name;
        this->Surname = x.Surname;
        this->Patronymic = x.Patronymic;
        this->Year_Birthday = x.Year_Birthday;
        this->Group = x.Group;
    }

    ~Student() 
    {
        cout << "\nДеструктор активирован\n";
    }
};

Student Init()
{
    Student student;

    cout << "\nНапишите имя студента\n";
    cin >> student.Name;
    cout << "\nНапишите фамилию студента\n";
    cin >> student.Surname;
    cout << "\nНапишите отчество студента\n";
    cin >> student.Patronymic;
    cout << "\nНапишите год рождения студента\n";
    cin >> student.Year_Birthday;
    cout << "\nНапишите группу студента\n";
    cin >> student.Group;

    return student;
}

void Print_Student(Student student) 
{
    cout << "Студент: " << student.Name << " " << student.Surname << " " << student.Patronymic 
        << "\nГод рождения: " << student.Year_Birthday 
        << "\nГруппа: " << student.Group << endl;
}

Student Apriory(Student student)
{
    cout << "Что-то\n";
    return student;
}


int main()
{
    setlocale(LC_ALL, "rus");
    Student student;

    cout << "Использовать конструктор инициализации?\n";
    int otv;
    cin >> otv;
    if (otv == 1) student = Init();


    Print_Student(student);
    

    Student student2(student);
    //Student student3 = student;

    Apriory(student);
}
