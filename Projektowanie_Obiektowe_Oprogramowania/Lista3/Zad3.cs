using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//Klasy powinny być otwarte na rozszerzenia i zamknięte na modyfikacje dotykające klientów.
//Drukowanie rachunków nie jest otwarte na rozszerzenia. 
//TaxCalculator też nie jest.
//Powinniśmy dać możliwość rozszerzenia tych dwóch funkcjonalności, bez jednoczesnego
//zaburzania działania klasy CashRegister

namespace Before
{
    public class TaxCalculator
    {
        public Decimal CalculateTax(Decimal Price)
        {
            return Price * 0.22m;
        }
    }

    public class Item
    {
        public Decimal Price { get; }
        public string Name { get; }
        public Item(string Name, Decimal Price)
        {
            this.Name = Name;
            this.Price = Price;
        }
    }

    public class CashRegister
    {
        public TaxCalculator taxCalc = new TaxCalculator();

        public Decimal CalculatePrice(Item[] Items)
        {
            Decimal _price = 0;
            foreach (Item item in Items)
                _price += item.Price + taxCalc.CalculateTax(item.Price);

            return _price;
        }

        public void PrintBill(Item[] Items)
        {
            foreach (var item in Items)
            {
                Console.WriteLine("towar {0} : cena {1} + podatek {2}", item.Name, item.Price, taxCalc.CalculateTax(item.Price));
            }
        }
    }
}

namespace After
{
    public interface ITax
    {
        Decimal GetTaxRate(string category);
    }
    public class TaxRate : ITax
    {
        public Decimal GetTaxRate(string category)
        {
            switch (category)
            {
                case "Sport":
                    return 0.12m;
                case "School":
                    return 0.19m;
                case "Food":
                    return 0.21m;
                default:
                    return 0.0m;
            }
        }
    }
    public class TaxCalculator
    {
        public Decimal CalculateTax(Item item, ITax taxRate)
        {
            return item.Price * taxRate.GetTaxRate(item.Category);
        }
    }
    public class Item
    {
        public Decimal Price { get; }
        public string Name { get; }
        public string Category { get; }
        public Item(string Name, Decimal Price, string Category)
        {
            this.Name = Name;
            this.Price = Price;
            this.Category = Category;
        }
    }
    public interface IBillPrinter
    {
        string PrintBill(Item[] Items, ITax taxRate);
    }
    public static class PrintItemList
    {
        public static string PrintItems(Item[] Items, ITax taxRate)
        {
            TaxCalculator taxCalc = new TaxCalculator();
            string Bill = "";
            Decimal _totalPrice = 0.0m;
            foreach (var item in Items)
            {
                Bill += "Towar : " + item.Name + " : cena " + item.Price
                    + " + podatek " + taxCalc.CalculateTax(item, taxRate).ToString("0.00") + "\n";

                _totalPrice += item.Price + taxCalc.CalculateTax(item, taxRate);
            }

            Bill += "Total price:  " + _totalPrice.ToString("0.00"); ;
            return Bill;
        }
    }
    public class AlphabeticalPrinter : IBillPrinter
    {
        public string PrintBill(Item[] Items, ITax taxRate)
        {
            Array.Sort(Items, delegate (Item x, Item y) { return x.Name.CompareTo(y.Name); });
            return PrintItemList.PrintItems(Items, taxRate);
        }
    }
    public class StandardPrinter : IBillPrinter
    {
        public string PrintBill(Item[] Items, ITax taxRate)
        {
            return PrintItemList.PrintItems(Items, taxRate);
        }
    }

    public class CashRegister
    {
        public TaxCalculator taxCalc = new TaxCalculator();

        public Decimal CalculatePrice(Item[] Items, ITax taxRate)
        {
            Decimal _price = 0;
            foreach (Item item in Items)
                _price += item.Price + taxCalc.CalculateTax(item, taxRate);

            return _price;
        }

        public string PrintBill(Item[] items, ITax taxRate, IBillPrinter billPrinter)
        {
            return billPrinter.PrintBill(items, taxRate);
        }
    }
}

namespace Zad3
{
    internal class Program
    {
        static void Main(string[] args)
        {
            

            Before.Item[] beforeItems = new Before.Item[5];
            beforeItems[0] = new Before.Item("Book", 23.11m);
            beforeItems[1] = new Before.Item("Pen", 4.18m);
            beforeItems[2] = new Before.Item("Chair", 120.09m);
            beforeItems[3] = new Before.Item("Laces", 2.98m);
            beforeItems[4] = new Before.Item("Chocolate", 3.53m);

            Before.CashRegister cashRegister = new Before.CashRegister();
            cashRegister.PrintBill(beforeItems);

            Console.WriteLine("");
            After.AlphabeticalPrinter alphabeticalPrinter = new After.AlphabeticalPrinter();
            After.StandardPrinter standardPrinter = new After.StandardPrinter();

            After.Item[] afterItems = new After.Item[5];
            afterItems[0] = new After.Item("Book", 23.11m, "School");
            afterItems[1] = new After.Item("Pen", 4.18m, "School");
            afterItems[2] = new After.Item("Chair", 120.09m, "Other");
            afterItems[3] = new After.Item("Laces", 2.98m, "Sport");
            afterItems[4] = new After.Item("Chocolate", 3.53m, "Food");

            After.CashRegister cashRegisterAfter = new After.CashRegister();
            After.TaxRate taxRate = new After.TaxRate();

            Console.WriteLine(cashRegisterAfter.PrintBill(afterItems, taxRate, standardPrinter));
            Console.WriteLine("");
            Console.WriteLine(cashRegisterAfter.PrintBill(afterItems, taxRate, alphabeticalPrinter));
            Console.ReadLine();
        }
    }
}
