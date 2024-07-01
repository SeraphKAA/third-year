/*Реализовать генерацию последовательности x<n> = 1/(y^n). Элементы последовательности
генерируются до тех пор, пока не будет выполнено условие |x<n>| <= e, где е – предварительно заданная
точность. При реализации алгоритмов предусмотреть проверку, что y > 1.*/


using laba_4_geter;


void First_sp(double y, double e, double e2)
{
    First_spos first_Spos = new First_spos();
    first_Spos.Main(y, e, e2);
}


void Second_sp(double y, double e, double e2)
{
    MySequence sequence = new MySequence(y, e, e2);
    Console.WriteLine("Способ с интерфейсами IEnumerable и IEnumerator");
    foreach (var x in sequence)
    {
        Console.WriteLine(x);
    }
    Console.WriteLine($"{e} - это е");
}


void Main()
{
    double y = 2;
    double e = 0.001;
    double e2 = 0.0001;

    First_sp(y, e, e2);
    Console.Read();
    Second_sp(y, e, e2);
}


Main();

//отдельный энум который будет просматривать e2 