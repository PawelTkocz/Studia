using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad7
{
    internal class Program
    {
        public static List<T> CreateList<T>(params T[] items)
        {
            return new List<T>(items);
        }
        static void Main(string[] args)
        {
            var item = new { Field1 = "The value", Field2 = 5 };
            var item2 = new { Field1 = "Hello", Field2 = "World" };
            var item3 = new { Field1 = "Bye", Field2 = 12 };
            var theList = CreateList(item);
            //theList.Add(item2);
            theList.Add(item3);



            var list =
                new List<object>()
                    .Select(o => new { Field1 = "foo", Field2 = 0 })
                    .ToList();
        }
    }
}
