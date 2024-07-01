using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;
/*Реализовать генерацию последовательности x<n> = 1/(y^n). Элементы последовательности
генерируются до тех пор, пока не будет выполнено условие |x<n>| <= e, где е – предварительно заданная
точность. При реализации алгоритмов предусмотреть проверку, что y > 1.*/
namespace laba_4_geter
{
    public class MySequence : IEnumerable, IEnumerator
    {
        private double y;
        private double current;
        private int n;
        private double e;
        private double e2;
        private double count;


        public MySequence(double y, double e, double e2)
        {
            if (y <= 1)
                throw new ArgumentException("y must be greater than 1");

            this.y = y;
            this.e = e;
            this.e2 = e2;
            Reset();

        }

        public IEnumerator GetEnumerator()
        {
            return this;
        }

        public bool MoveNext()
        {
            if (Math.Abs(current) > e || count == 0)
            {
                Console.WriteLine($"{Math.Abs(current)} {e}- е, {Math.Abs(current) > e}, {count}");
                n++;
                current = 1 / Math.Pow(y, n);
                count++;

                if (Math.Abs(current) <= e) return true;
                return Math.Abs(current) > e;
            }
            else if (Math.Abs(current) > e2)
            {
                Console.WriteLine($"{Math.Abs(current)} {e2}- е2, {Math.Abs(current) > e2}, {count}");
                n++;
                current = 1 / Math.Pow(y, n);
                count++;
                return Math.Abs(current) > e2;
            }
            else
            {
                Console.WriteLine("Вернул тру");
                return true;
            }
            Console.WriteLine("хз че тут");
        }

        public void Reset()
        {
            current = 0;
            n = 0;
            count = 0;
        }

        public object Current
        {
            get { return current; }
        }
    }





}


