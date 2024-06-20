using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad3
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string docPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

            foreach (var group in
                from surname in File.ReadAllLines(Path.Combine(docPath, "fileZad3.txt"))
                    orderby surname[0]
                        group surname[0] by surname[0]
            )
            {
                Console.WriteLine(group.Key);
            }
            Console.ReadLine();
        }
    }
}
