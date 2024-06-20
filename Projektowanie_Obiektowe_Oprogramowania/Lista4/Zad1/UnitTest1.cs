using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Threading;
using Zad1;

namespace UnitTests
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void FooSingleton1()
        {
            var singleton = FooSingleton.Instance();
            Assert.IsNotNull(singleton);
        }

        [TestMethod]
        public void FooSingleton2()
        {
            var singleton1 = FooSingleton.Instance();
            var singleton2 = FooSingleton.Instance();

            Assert.AreEqual(singleton1, singleton2);
        }

        [TestMethod]
        public void FooSingleton3()
        {
            FooSingleton? singleton1 = null;
            FooSingleton? singleton2 = null;

            var thread1 = new Thread(() => singleton1 = FooSingleton.Instance());
            var thread2 = new Thread(() => singleton2 = FooSingleton.Instance());

            thread1.Start();
            thread2.Start();

            thread1.Join();
            thread2.Join();

            Assert.IsNotNull(singleton1);
            Assert.AreEqual(singleton1, singleton2);
        }

        [TestMethod]
        public void ThreadSingleton1()
        {
            var singleton = ThreadSingleton.Instance();
            Assert.IsNotNull(singleton);
        }

        [TestMethod]
        public void ThreadSingleton2()
        {
            var singleton1 = ThreadSingleton.Instance();
            var singleton2 = ThreadSingleton.Instance();

            Assert.AreEqual(singleton1, singleton2);
        }

        [TestMethod]
        public void ThreadSingleton3()
        {
            ThreadSingleton? singleton1 = null;
            ThreadSingleton? singleton2 = null;

            var thread1 = new Thread(() => singleton1 = ThreadSingleton.Instance());
            var thread2 = new Thread(() => singleton2 = ThreadSingleton.Instance());

            thread1.Start();
            thread2.Start();

            thread1.Join();
            thread2.Join();

            Assert.AreNotEqual(singleton1, singleton2);
        }

        [TestMethod]
        public void FiveSecondSingleton1()
        {
            var singleton = FiveSecondSingleton.Instance();
            Assert.IsNotNull(singleton);
        }

        [TestMethod]
        public void FiveSecondSingleton2()
        {
            var singleton1 = FiveSecondSingleton.Instance();
            var singleton2 = FiveSecondSingleton.Instance();

            Assert.AreEqual(singleton1, singleton2);
        }

        [TestMethod]
        public void FiveSecondSingleton3()
        {
            var singleton1 = FiveSecondSingleton.Instance();
            Thread.Sleep(5500);
            var singleton2 = FiveSecondSingleton.Instance();

            Assert.AreNotEqual(singleton1, singleton2);
        }
    }
}