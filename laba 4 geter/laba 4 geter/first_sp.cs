using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
/*Реализовать генерацию последовательности x<n> = 1/(y^n). Элементы последовательности
генерируются до тех пор, пока не будет выполнено условие |x<n>| <= e, где е – предварительно заданная
точность. При реализации алгоритмов предусмотреть проверку, что y > 1.*/
namespace laba_4_geter
{
    public class First_spos
    {
        public void Main(double y, double e, double e2)
        {
            Console.WriteLine("Способ с yield return'ом");
            foreach (double x in GenerateSequence(y, e, e2))
            {
                Console.WriteLine(x);
            }
        }

        static IEnumerable<double> GenerateSequence(double y, double e, double e2)
        {
            if (y <= 1)
            {
                throw new ArgumentException("y должно быть больше 1");
            }

            int n = 0;
            double x = 1;

            while (Math.Abs(x) > e)
            {
                yield return x;
                n++;
                x = 1 / Math.Pow(y, n);
            }
            Console.WriteLine($"{e} - e\n\n[+] е2\n");
            while (Math.Abs(x) > e2)
            {
                yield return x;
                n++;
                x = 1 / Math.Pow(y, n);
            }
            Console.WriteLine($"{e2} - e2");
        }
    }
}
