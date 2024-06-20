using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad5
{
    public class Osoba
    {
        public Osoba(string desc)
        {
            string[] values = desc.Split(' ');
            Imie = values[0];
            Nazwisko = values[1];
            Pesel = values[2];
        }

        public string Imie;
        public string Nazwisko;
        public string Pesel;
    }

    public class Konto
    {
        public Konto(string desc)
        {
            string[] values = desc.Split(' ');
            Pesel = values[0];
            NumerKonta = values[1];
        }

        public string Pesel;
        public string NumerKonta;
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            string docPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

            IList<Osoba> ludzie = new List<Osoba>();
            IList<Konto> konta = new List<Konto>();

            foreach (var e in
                from line in File.ReadAllLines(Path.Combine(docPath, "fileZad5a.txt"))
                select new Osoba(line)
            )
            {
                ludzie.Add(e);
            }

            foreach (var e in
                from line in File.ReadAllLines(Path.Combine(docPath, "fileZad5b.txt"))
                select new Konto(line)
            )
            {
                konta.Add(e);
            }

            foreach (var e in
                ludzie.Join(
                    konta,
                    osoba => osoba.Pesel,
                    konto => konto.Pesel,
                    (osoba, konto) => new
                    {
                        imie = osoba.Imie,
                        nazwisko = osoba.Nazwisko,
                        pesel = osoba.Pesel,
                        numerKonta = konto.NumerKonta
                    }
            ))
            {
                Console.WriteLine("{0} {1} {2} {3}", e.imie, e.nazwisko, e.pesel, e.numerKonta);
            }
            Console.ReadLine();
        }
    }
}
