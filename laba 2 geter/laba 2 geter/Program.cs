/*
Реализовать иерархию классов согласно варианту задания. 
Классы должны содержать поля, свойства, обычные и
виртуальные методы. Виртуальные методы должны иметь разную
реализацию в базовых и производных классах. Создать
программу, демонстрирующую работу классов. Выполненная
работа должна включать исходный текст работоспособной
программы и отчет о выполнении лабораторной работы.


Принтер, компьютер, компьютерная техника,
монитор, клавиатура, запоминающее устройство,
материнская плата, процессор, жесткий диск,
съемный диск, аудиоколонки.*/

Start();









void Start() 
{
    Comp comp = new Comp();
    Comp_tech comp_tech = new Comp_tech();
    Zap_Ustr zap_Ustr = new Zap_Ustr();
    Printer printer = new Printer();
    Mon mon = new();
    Klava klava = new();
    Materinka mater = new();
    Proc proc = new Proc();
    HDD hdd = new HDD();
    S_Disk s_Disk = new S_Disk();
    AudioKolonki audiokolonki = new AudioKolonki();

/*
    audiokolonki.check = false;*/
    if (comp.check && comp_tech.check && zap_Ustr.check && printer.check && mon.check && klava.check && mater.check && proc.check && hdd.check && s_Disk.check && audiokolonki.check)
    {
        string temp = "="; for (int i = 0; i < 27; i++) temp += "=";
        Console.WriteLine($"\n{temp}\nВсе классы готовы к работе.\n{temp}\n");
        Main(comp, comp_tech, zap_Ustr, printer, mon, klava, mater, proc, hdd, s_Disk, audiokolonki);
    }
    else Console.Write("Что-то не работает");
}
void Main(Comp comp, Comp_tech comp_tech, Zap_Ustr zap_Ustr, Printer printer, Mon mon, Klava klava, Materinka mater, Proc proc, HDD hdd, S_Disk s_Disk, AudioKolonki audiokolonki)
{
    Console.WriteLine(comp.GetType().Name);
    comp.Print();

    Console.WriteLine(comp_tech.GetType().Name);
    comp_tech.Print();

    Console.WriteLine(zap_Ustr.GetType().Name);
    zap_Ustr.Val += 1;
    Console.WriteLine(zap_Ustr.Val);

    Console.WriteLine(printer.GetType().Name);
    Console.WriteLine(printer.sad_man);

    Console.WriteLine(mon.GetType().Name);
    mon.Print();

    Console.WriteLine(klava.GetType().Name);
    klava.Print();

    Console.WriteLine(mater.GetType().Name);
    mater.Print_secret();

    Console.WriteLine(proc.GetType().Name);
    proc.Print();

    Console.WriteLine(hdd.GetType().Name);
    hdd.Print();

    Console.WriteLine(s_Disk.GetType().Name);
    s_Disk.Print();

    Console.WriteLine(audiokolonki.GetType().Name);
    audiokolonki.Print();
}



public class Comp
{
    public bool check = true;
    public void Print() { Console.WriteLine("Hello, I'm comp or another.\n"); }

    virtual public void Print_secret() { Console.WriteLine("А это Секретка) \n"); }
    
}

public class Comp_tech
{
    public bool check = true;
    public void Print() { Console.WriteLine("Hello, I'm comp teches.\n"); }
}


public class Zap_Ustr : Comp_tech
{ 
    public int Val { get; set; }
}

public class Printer : Comp_tech
{
    public int sad_man = 0;
}

public class Mon : Comp_tech
{
    
}

public class Klava : Comp_tech
{

}

public class Materinka : Comp
{
    override public void Print_secret() { Console.WriteLine("а это секретОчка \n"); }
}

public class Proc : Comp
{
    virtual public void Print_secret2() { Console.WriteLine("А это Секретка вторая)) \n"); }
}

public class HDD : Comp
{

}

public class S_Disk : Comp
{

}

public class AudioKolonki : Comp_tech
{

}