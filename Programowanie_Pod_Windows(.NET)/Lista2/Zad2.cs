using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad2
{
    /*
     W przypadku destruktora odśmiecacz wykona kod zawarty w destruktorze tuż przed usunięciem obiektu, ale moment
     usuwania obiektu jest z punktu widzenia programisty niemożliwy do ustalenia. 
     W przypadku wykorzystania interfejsu IDisposable, programista jawnie wywołuje metodę Dispose() niszczącą zasoby
     przyznane obiektowi

    System.GC.Collect() - wywołuje Garbage Collector ale nie jest zalecane wywoływanie tej metody we własnym kodzie,
    bo to droga metoda, a kod decydujący o tym kiedy wowoływać tę funkcję automatycznie jest dobrze napisany
    */

    public class DestructorClass
    {
        public int number;
        public DestructorClass(int n)
        {
            number = n;
            Console.WriteLine("Utworzono obiekt {0}", n);
        }
        ~DestructorClass()
        {
            Console.WriteLine("Zniszczono obiekt {0}", number);
        }
    }

    public class DisposableClass : IDisposable
    {
        public int number;
        public DisposableClass(int n)
        {
            number = n;
            Console.WriteLine("Utworzono obiekt2 {0}", n);
        }

        public void Dispose()
        {
            Console.WriteLine("Zniszczono obiekt2 {0}", number);
        }

    }
    internal class Program
    {
        static void Main(string[] args)
        {
            for(int i=0; i<10; i++)
            {
                DestructorClass dc = new DestructorClass(i);
            }
            Console.ReadLine();
            DisposableClass[] tab = new DisposableClass[10];
            for (int i = 0; i < 10; i++)
            {
                tab[i] = new DisposableClass(i);
            }
            for(int i=0; i<10; i++)
            {
                tab[i].Dispose();
            }
            Console.ReadLine();
            using (DisposableClass dc = new DisposableClass(0))
            {
                for(int i=0;i<1000000; i++)
                {
                    if (i % 2 == 3)
                        Console.WriteLine("+");
                }
            }
            Console.ReadLine();
        }
    }
}
