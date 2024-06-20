using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LogProxy
{
    public interface IFridge
    {
        IEnumerable<string> GetListOfProducts();
        void AddProductsFromList(IEnumerable<string> products);
        bool checkProductsAvailability(IEnumerable<string> products);
    }
    public class Fridge : IFridge
    {
        private List<string> _products = new List<string>();
        public void AddProductsFromList(IEnumerable<string> products)
        {
            string[] tab = products.ToArray(); 
            for(int i=0; i<products.Count(); i++)
            {
                Console.WriteLine("{0}. {1}", i + 1, tab[i]);
                _products.Add(tab[i]);
            }
        }

        public bool checkProductsAvailability(IEnumerable<string> products)
        {
            string[] tab = products.ToArray();
            bool res = true;
            for (int i = 0; i < products.Count(); i++)
            {
                string available = _products.Contains(tab[i]) ? "yes" : "no";
                Console.WriteLine("{0}. {1} - {2}", i + 1, tab[i], available);
                if (available == "no")
                    res = false;
            }
            return res;
        }

        public IEnumerable<string> GetListOfProducts()
        {
            string[] tab = _products.ToArray();
            for (int i = 0; i < tab.Length; i++)
            {
                Console.WriteLine("{0}. {1}", i + 1, tab[i]);
            }
            return _products;
        }
    }

    public class FridgeLog : IFridge
    {
        private Fridge _fridge;
        private StreamWriter writer;

        public FridgeLog()
        {
            _fridge = new Fridge();
            writer = new StreamWriter("logFile.txt");
        }

        public void AddProductsFromList(IEnumerable<string> products)
        {
            writer.WriteLine("----------");
            writer.WriteLine("[{0}]", DateTime.UtcNow);
            writer.WriteLine("AddProductsFromList()");
            string parameters = "";
            foreach (string product in products)
                parameters += product + " ";
            writer.WriteLine("Parameters: {0}", parameters);
            _fridge.AddProductsFromList(products);
            writer.WriteLine("[{0}]", DateTime.UtcNow);
            writer.WriteLine("----------");
            writer.Flush();
        }

        public bool checkProductsAvailability(IEnumerable<string> products)
        {
            writer.WriteLine("----------");
            writer.WriteLine("[{0}]", DateTime.UtcNow);
            writer.WriteLine("CheckProductsAvailability()");
            string parameters = "";
            foreach (string product in products)
                parameters += product + " ";
            writer.WriteLine("Parameters: {0}", parameters);
            bool res = _fridge.checkProductsAvailability(products);
            writer.WriteLine("[{0}]", DateTime.UtcNow);
            writer.WriteLine("Returned value: {0}", res);
            writer.WriteLine("----------");
            writer.Flush();
            return res;
        }

        public IEnumerable<string> GetListOfProducts()
        {
            writer.WriteLine("----------");
            writer.WriteLine("[{0}]", DateTime.UtcNow);
            writer.WriteLine("GetListOfProducts()");
            IEnumerable<string> res = _fridge.GetListOfProducts();
            string res_string = "";
            foreach (string product in res)
                res_string += product + " ";
            writer.WriteLine("[{0}]", DateTime.UtcNow);
            writer.WriteLine("Returned value: {0}", res_string);
            writer.WriteLine("----------");
            writer.Flush();
            return res;
        }
    }

    public class FridgeFactory
    {
        public IFridge GetInstance(bool f)
        {
            if(!f)
                return new Fridge();
            return new FridgeLog();
        }
    }
}

namespace RateLimiterProxy
{

    public class Password
    {
        private int _password;
        public Password()
        {
            _password = 12;
        }

        public virtual bool GuessPassword(int guess)
        {
            return guess == _password;
        }
    }

    public class ProxyPassword : Password
    {
        private DateTime _start;
        private const int _seconds = 3;
        private int _cnt;
        private const int _maxNum = 3;

        public ProxyPassword()
        {
            _cnt = 0;
        }
        public override bool GuessPassword(int guess)
        {
            if (_cnt == 0 || DateTime.UtcNow > _start.AddSeconds(_seconds))
            {
                _cnt = 1;
                _start = DateTime.UtcNow;
                return base.GuessPassword(guess);
            }
            else
            {
                if(_cnt < _maxNum)
                {
                    _cnt++;
                    return base.GuessPassword(guess);
                }
                Console.WriteLine("To many invokes.");
            }
            return false;
        }
    }

    public class PasswordFactory
    {
        public Password GetInstance(bool f)
        {
            if (!f)
                return new Password();
            return new ProxyPassword();
        }
    }
}

namespace Zad5
{

    internal class Program
    {
        static void Main(string[] args)
        {
            /*
            LogProxy.FridgeFactory factory = new LogProxy.FridgeFactory();
            LogProxy.IFridge fridge = factory.GetInstance(false);
            List<string> products = new List<string> { "bread", "butter", "milk", "chocolate" };
            fridge.AddProductsFromList(products);
            List<string> products2 = new List<string> { "egg", "bread", "ham", "butter" };
            fridge.checkProductsAvailability(products2);
            fridge.GetListOfProducts();

            Console.WriteLine();

            LogProxy.IFridge fridge2 = factory.GetInstance(true);
            fridge2.AddProductsFromList(products2);
            fridge2.checkProductsAvailability(products);
            fridge2.GetListOfProducts();
            Console.ReadLine();
            */

            RateLimiterProxy.PasswordFactory factory = new RateLimiterProxy.PasswordFactory();
            RateLimiterProxy.Password password = factory.GetInstance(false);
            for(int i=1; i<13; i++)
            {
                Console.WriteLine("{0}. {1}", i, password.GuessPassword(i));
            }

            RateLimiterProxy.Password password2 = factory.GetInstance(true);
            for (int i = 1; i < 13; i++)
            {
                Console.WriteLine("{0}. {1}", i, password2.GuessPassword(i));
            }

            while (true)
            {
                string a = Console.ReadLine();
                Console.WriteLine(password2.GuessPassword(int.Parse(a)));
            }
        }
    }
}
