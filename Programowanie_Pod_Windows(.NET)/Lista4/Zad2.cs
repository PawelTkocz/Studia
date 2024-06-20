using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string docPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            /*
            using (StreamWriter outputFile = new StreamWriter(Path.Combine(docPath, "fileZad2.txt")))
            {
                Random r = new Random();
                for (int i=0; i<100; i++)
                {
                    int rInt = r.Next(0, 200);
                    outputFile.WriteLine(rInt);
                }
            }
            */
            foreach (var e in
                from liczba in File.ReadAllLines(Path.Combine(docPath, "fileZad2.txt"))
                    where int.Parse(liczba) > 100
                        orderby -int.Parse(liczba) 
                            select liczba
                )
            {
                Console.WriteLine(e);
            }

            foreach(var e in
                File.ReadAllLines(Path.Combine(docPath, "fileZad2.txt")).Where(liczba => int.Parse(liczba) > 100).OrderBy(liczba => -int.Parse(liczba))
            )
            {
                Console.WriteLine(e);
            }
            Console.ReadLine();
            //różnica polega na tym, że w jednym przypadku trzeba pisać lambda wyrażenia, a w drugim nie
        }
    }
}
