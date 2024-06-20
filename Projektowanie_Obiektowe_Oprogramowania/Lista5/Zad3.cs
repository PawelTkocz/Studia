using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad3
{
    class ComparisonToIComparerAdapter<T> : IComparer
    {
        Comparison<T> comparison;
        public ComparisonToIComparerAdapter(Comparison<T> comparison) { 
            this.comparison = comparison; 
        }
        public int Compare(object x, object y) { 
            return comparison((T)x, (T)y);
        }
    }

    internal class Program
    {
    static int IntComparer(int x, int y)
    {
        return x.CompareTo(y);
    }
    static void Main(string[] args)
        {
            ArrayList a = new ArrayList() { 1, 5, 3, 3, 2, 4, 3 };
            a.Sort(new ComparisonToIComparerAdapter<int>(IntComparer));
            foreach (int i in a)
                Console.WriteLine(i);
            Console.ReadLine();
        }
    }
}
