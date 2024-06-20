using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Zad3
{
    public class MyClass
    {
        public async void Foo()
        {
            Console.WriteLine("Raz");
            await TaskExtensions.Delay(2000);
            Console.WriteLine("Dwa");
            await 3000;
            Console.WriteLine(await "https://www.google.com");
        }
    }
    public static class TaskExtensions
    {
        private static HttpClient Client = new HttpClient();
        public static TaskAwaiter GetAwaiter(this int milisec)
        {
            return Delay(milisec).GetAwaiter();
        }

        public static TaskAwaiter<string> GetAwaiter(this string url)
        {
            return Client.GetStringAsync(url).GetAwaiter();
        }
        public static Task Delay(int milisec)
        {
            TaskCompletionSource<object> tcs = new TaskCompletionSource<object>();
            System.Timers.Timer t =  new System.Timers.Timer();
            t.Interval = milisec;
            t.Elapsed += (source, e) =>
            {
                t.Stop();
                t.Dispose();
                tcs.SetResult(null);
            };
            t.Start();
            return tcs.Task;
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            MyClass c = new MyClass();
            c.Foo();
            Console.ReadLine();
        }
    }
}
