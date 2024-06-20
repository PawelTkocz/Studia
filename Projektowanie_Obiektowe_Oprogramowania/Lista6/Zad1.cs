using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad1
{
    public interface ILogger
    {
        void Log(string Message);
    }
    public enum LogType { None, Console, File }

    public class NoneLogger : ILogger { 
        public void Log(string Message) { }
    }
    public class ConsoleLogger : ILogger { 
        public void Log(string Message) { 
            Console.WriteLine(Message);
        }
    }
    public class FileLogger : ILogger
    {
        private StreamWriter file;
        public FileLogger(string filePath)
        {
            if (filePath is null)
                throw new ArgumentException("No file path");

            this.file = new StreamWriter(filePath);
        }

        public void Log(string Message) { 
            file.WriteLine(Message);
            file.Flush();
        }
    }

    public class LoggerFactory
    {
        private static LoggerFactory _instance;
        private static object _lock = new object();
        public static LoggerFactory Instance()
        {
            if (_instance == null)
            {
                lock (_lock)
                {
                    if (_instance == null)
                        _instance = new LoggerFactory();
                }
            }

            return _instance;
        }

        public ILogger GetLogger(LogType LogType, string Parameters = null)
        {
            switch (LogType)
            {
                case LogType.None: return new NoneLogger();
                case LogType.Console: return new ConsoleLogger();
                case LogType.File: return new FileLogger(Parameters);
                default: throw new ArgumentException("LogType not found");
            }
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            ILogger logger1 = LoggerFactory.Instance().GetLogger(LogType.File, "foo.txt");
            logger1.Log("foo bar"); // logowanie do pliku
            ILogger logger2 = LoggerFactory.Instance().GetLogger(LogType.None);
            logger2.Log("qux"); // brak logowania   
            ILogger logger3 = LoggerFactory.Instance().GetLogger(LogType.Console);
            logger3.Log("hello world");
            Console.ReadLine();
        }
    }
}
