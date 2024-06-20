using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad6
{
    internal class Program
    {
        public static string Get_ip(string line)
        {
            string[] values = line.Split(' ');
            return values[1];
        }
        static void Main(string[] args)
        {
            string docPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            /*
            using (StreamWriter outputFile = new StreamWriter(Path.Combine(docPath, "fileZad6.txt")))
            {
                Random r = new Random();
                for (int i=0; i<1000; i++)
                {
                    int r1 = r.Next(12, 15);
                    int r2 = r.Next(34, 36);
                    int r3 = r.Next(67, 69);
                    int r4 = r.Next(124, 126);
                    outputFile.WriteLine("05:56:12 {0}.{1}.{2}.{3} GET /TheApplication/WebResource.axd 200", r1, r2, r3, r4);
                }
            }
            */

            foreach (var e in
                File.ReadAllLines(Path.Combine(docPath, "fileZad6.txt"))
                    .GroupBy(line => Get_ip(line))
                    .Select(group => new
                    {
                        Ip = group.Key,
                        Count = group.Count()
                    })
                    .OrderByDescending(x => x.Count).Take(3)
            )
            {
                Console.WriteLine("{0} {1}", e.Ip, e.Count);
            }
            Console.ReadLine();
        }
    }
}
