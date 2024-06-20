using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad1
{
    //static dla klas - sprawia, że nie można tworzyć instancji klasy oraz dziedziczyć z niej
    #region
    static class StaticClass
    {
        public static void SayHi()
        {
            Console.WriteLine("HI");
        }
    }
    //StaticClass sc = new StaticClass() - wywoła błąd
    #endregion

    //static dla składowych klas - sprawia, że pole jest współdzielone między wszystkie instancje klasy
    #region
    public class StaticFieldClass
    {
        public static int counter = 0;
        public StaticFieldClass()
        {
            counter++;
        }
    }
    #endregion

    //sealed dla klas - zabezpiecza klasę przed dziedziczneniem z niej
    #region
    sealed class SealedClass
    {

    }
    /*
    ten fragment kodu wywoła błąd
    class B : SealedClass
    {

    }
    */
    #endregion

    //abstract dla klas - wskazuje że klasa jest przeznaczona tylko do bycia klasą bazową innej klasy, a nie
    //                    do tworzenia własnych instancji
    #region
    abstract class Shape
    {
        public abstract int GetArea();
    }
    class Square : Shape
    {
        public override int GetArea()
        {
            return 10;
        }
    }
    //Shape s = new Shape() - wywoła błąd, bo Shape jest klasą abstrakcyjną
    #endregion

    //abstract dla składowych klas (metod) - deklaruje funkcję, której implementację zapewni klasa dziedzicząca z funkcji

    //virtual i override dla składowych klas (metod) - virtual deklaruje metodę, której implementacja może zostać 
    //zmieniona przez klasę dziedziczącą, natomiast do zmiany tej implementacji należy skorzystać ze słowa override
    #region
    public class Figure
    {
        public virtual void NumberOfAngles()
        {
            Console.WriteLine("Zero or more");
        }
    }

    public class Triangle : Figure
    {
        public override void NumberOfAngles()
        {
            Console.WriteLine("Three");
        }
    }
    #endregion

    //partial - pozwala rozbić definicję klasy
    #region
    partial class PartialClass
    {
        public int cnt = 13;
    }
    #endregion

    //readonly pole klasy - pole staje się tylko do odczytu, nie można modyfikowac jego wartości 
    //(jedynie w momencie deklaracji wartości pola lub w konstruktorze klasy)
    #region
    public class Car
    {
        public readonly int year;
        public Car(int year)
        {
            this.year = year;
        }
        public void ChangeYear()
        {
            //this.year = 1999; - wywoła błąd
        }
    }
    #endregion

    //in, ref, out na liście parametrów metody - pozwalają przekazywać do metod referencje do zmiennych
    //in - przekazana zmienna nie może zostać zmodyfikowana (przekazanie referecji zwiększa wydajność)
    //ref - przekazujemy referencję na zmienną (musi być zainicjowana przed przekazaniem do funkcji)
    //out - ref z tą różnicą, że zmienna nie musi być zainicjowana przed przekazniem do funcji, ale musi
    //      zostać zainicjowana w jej środku
    #region
    public static class ReferencesClass
    {
        public static void IncrementOneRef(ref int a)
        {
            a++;
        }

        public static void IncrementOneOut(out int a)
        {
            a = 13;
            a++;
        }

        public static void InMethod(in int a)
        {
            //a++ - wywoła błąd
            if (a == 12)
                Console.WriteLine("a=12");
        }
    }
    #endregion

    //params na liście parametrów metody - pozwala przekazać do metody zmienną liczbę argumentów, które zostają
    //zinterpretowane jako tablica elementów
    #region
    public static class ParamsClass
    {
        public static int Sum(params int[] numbers)
        {
            return numbers.Sum();
        }
    }
    #endregion

    internal class Program
    {
        static void Main(string[] args)
        {
            StaticClass.SayHi();
            StaticFieldClass a = new StaticFieldClass();
            StaticFieldClass b = new StaticFieldClass();
            Console.WriteLine(StaticFieldClass.counter);
            Figure f = new Figure();
            f.NumberOfAngles();
            Triangle t = new Triangle();
            t.NumberOfAngles();
            PartialClass p = new PartialClass();
            p.PrintCnt();
            Car c = new Car(2000);
            //c.year = 1987; - wywoła błąd
            int v1 = 10;
            int v2;
            int v3 = 12;
            ReferencesClass.InMethod(in v3);
            ReferencesClass.IncrementOneRef(ref v1);
            Console.WriteLine(v1);
            ReferencesClass.IncrementOneOut(out v2);
            Console.WriteLine(v2);
            Console.WriteLine(ParamsClass.Sum(1, 2, 3, 4, 5));
            Console.ReadLine();
        }
    }
}
