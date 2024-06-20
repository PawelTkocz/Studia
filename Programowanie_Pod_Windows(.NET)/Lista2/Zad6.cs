using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad6
{
    public class MyVec
    {
        public int x;
        public int y;

        public MyVec(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        public static MyVec operator +(MyVec v1, MyVec v2)
        {
            return new MyVec(v1.x + v2.x, v1.y + v2.y);
        }

        public static int operator *(MyVec v1, MyVec v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        public override string ToString()
        {
            return String.Format("[{0},{1}]", this.x, this.y);
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            MyVec u = new MyVec(2, 3);
            MyVec v = new MyVec(1, 1);
            Console.WriteLine("{0}+{1}={2}", u, v, u + v);
            Console.WriteLine("{0}*{1}={2}", u, v, u * v);
            Console.ReadLine();
        }
    }
}
