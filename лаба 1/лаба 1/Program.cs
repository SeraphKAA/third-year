/*Ввести с клавиатуры массив строк, отсортировать
полученный массив по длине строки и вывести
результат на экран.*/

Console.WriteLine("Введите массив строк:");
string slova = Console.ReadLine();
string[] mas_slov = slova.Split();
string[] fin_mas = new string[mas_slov.Length];
Array.Sort(mas_slov, (x, y) => x.Length.CompareTo(y.Length));

foreach (string i in mas_slov) 
{
    string temp = "";
    for (int z = i.Length - 1; z >= 0; z--) temp += i[z]; 
    Console.WriteLine($"{temp} - {i.Length}"); 
}

/*все слова заполняли массив */