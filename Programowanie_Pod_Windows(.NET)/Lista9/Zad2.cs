using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Zad1
{
    internal class Program
    {
        public static int NumberOfChairs = 5;
        public static int AllClientsNumber = 10;
        public static Semaphore barber_semaphore = new Semaphore(0, 1);
        public static Semaphore customer_semaphore = new Semaphore(0, AllClientsNumber);
        public static Mutex mutex = new Mutex();
        public static Queue<int> queue = new Queue<int>();
        static void Main(string[] args)
        {
            Thread barberThread = new Thread(Barber);
            barberThread.Start();
            for (int i = 1; i <= AllClientsNumber; i++)
            {
                Thread t = new Thread(new ParameterizedThreadStart(Client));
                t.Start(i);
            }
            Console.ReadLine();
        }

        private static void Barber()
        {
            while(true){
                customer_semaphore.WaitOne();
                mutex.WaitOne();
                int client = -1;
                if (queue.Count > 0)
                    client = queue.Dequeue();
                barber_semaphore.Release();
                mutex.ReleaseMutex();
                //cut hair
                Console.WriteLine("Barber is cutting hair for client {0}", client);
                Thread.Sleep(1000);
                Console.WriteLine("Barber finished cutting hair for client {0}", client);
            }
        }

        private static void Client(object number)
        {
            Random rnd = new Random();
            Thread.Sleep(rnd.Next(1, 5) * 1000);
            
            mutex.WaitOne();
            if(queue.Count < NumberOfChairs)
            {
                queue.Enqueue((int)number);
                Console.WriteLine("Client {0} is waiting in the waiting room", number);
                customer_semaphore.Release();
                mutex.ReleaseMutex();
                barber_semaphore.WaitOne();
            }
            else
            {
                Console.WriteLine("Client {0} is leaving - the waiting room is full", number);
                mutex.ReleaseMutex();
            }
        }
    }
}
