using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad3
{
    public class ExampleClass
    {
        private double seconds;

        public double Hours
        {
            get { return seconds / 3600; }
            set
            {
                if (value <= 0)
                    throw new ArgumentOutOfRangeException(nameof(value), "Argument must be greater than 0");
                seconds = value * 3600;
            }
        }

        public string Name { get; set; }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            ExampleClass c = new ExampleClass();
            c.Hours = 1.5;
            Console.WriteLine(c.Hours);
            c.Name = "John";
            Console.WriteLine(c.Name);
            Console.ReadLine();
        }
    }
}
