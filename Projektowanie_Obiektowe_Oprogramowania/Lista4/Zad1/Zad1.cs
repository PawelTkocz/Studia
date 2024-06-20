using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad1
{
    public class FooSingleton
    {
        private static FooSingleton _instance;
        private static object _lock = new object();

        public static FooSingleton Instance()
        {
            if (_instance == null)
            {
                lock (_lock)
                {
                    if (_instance == null)
                        _instance = new FooSingleton();
                }
            }

            return _instance;
        }
    }

    public sealed class ThreadSingleton
    {
        [ThreadStatic]
        private static ThreadSingleton _instance;

        public static ThreadSingleton Instance()
        {
            if (_instance == null)
                _instance = new ThreadSingleton();

            return _instance;
        }
    }

    public sealed class FiveSecondSingleton
    {
        private static FiveSecondSingleton _instance;
        private static object _lock = new object();

        static DateTime creationTime;

        private FiveSecondSingleton() { 
            creationTime = DateTime.Now;
        }

        static bool HasExpired() { 
            return DateTime.Now >= creationTime.AddSeconds(5); 
        }

        public static FiveSecondSingleton Instance()
        {
            if (_instance == null || HasExpired())
            {
                lock (_lock)
                {
                    if (_instance == null || HasExpired())
                        _instance = new FiveSecondSingleton();
                }
            }

            return _instance;
        }
    }
internal class Program
    {
        static void Main(string[] args)
        {
            
        }
    }
}
