using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using Zad1;

namespace UnitTests
{
    public abstract class AbstractClass
    {
        public abstract int DoSomeWork();
    }
    public class DerivedClass : AbstractClass
    {
        public override int DoSomeWork()
        {
            return 13;
        }
    }
    public interface IWorker
    {
        int DoWork();
    }
    public class Foo : IWorker
    {
        public int DoWork()
        {
            return 1;
        }
    }

    public class Bar : IWorker
    {
        public int DoWork()
        {
            return 2;
        }
    }

    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void BasicResolveSingleton()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<Foo>(true);
            Foo f1 = c.Resolve<Foo>();
            Foo f2 = c.Resolve<Foo>();
            Assert.IsInstanceOfType(f1, typeof(Foo));
            Assert.AreEqual(f1, f2);
        }

        [TestMethod]
        public void BasicResolveNotSingleton()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<Foo>(false);
            Foo f1 = c.Resolve<Foo>();
            Foo f2 = c.Resolve<Foo>();
            Assert.IsInstanceOfType(f1, typeof(Foo));
            Assert.AreNotEqual(f1, f2);
        }

        [TestMethod]
        public void ResolveNotRegisteredClass()
        {
            SimpleContainer c = new SimpleContainer();
            Foo f1 = c.Resolve<Foo>();
            Foo f2 = c.Resolve<Foo>();
            Assert.IsInstanceOfType(f1, typeof(Foo));
            Assert.AreNotEqual(f1, f2);
        }

        [TestMethod]
        [ExpectedException(typeof(Exception),
        "Can't resolve abstract type, which wasn't previously registered.")]
        public void ResolveNotRegisteredInterface()
        {
            SimpleContainer c = new SimpleContainer();
            IWorker w = c.Resolve<IWorker>();
        }

        [TestMethod]
        [ExpectedException(typeof(Exception),
        "Can't register abstract type.")]
        public void ResolveBadlyRegisteredInterface()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<IWorker>(true);
            IWorker w = c.Resolve<IWorker>();
        }

        [TestMethod]
        [ExpectedException(typeof(Exception),
        "Can't resolve abstract type, which wasn't previously registered.")]
        public void ResolveNotRegisteredAbstractClass()
        {
            SimpleContainer c = new SimpleContainer();
            AbstractClass a = c.Resolve<AbstractClass>();
        }

        [TestMethod]
        [ExpectedException(typeof(Exception),
        "Can't register abstract type.")]
        public void ResolveBadlyRegisteredAbstractClass()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<AbstractClass>(true);
            AbstractClass a = c.Resolve<AbstractClass>();
        }

        [TestMethod]
        public void ResolveOptionsChanges()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<Foo>(true);
            Foo f1 = c.Resolve<Foo>();
            c.RegisterType<Foo>(false);
            Foo f2 = c.Resolve<Foo>();
            c.RegisterType<Foo>(true);
            Foo f3 = c.Resolve<Foo>();
            Assert.IsInstanceOfType(f1, typeof(Foo));
            Assert.AreEqual(f1, f3);
            Assert.AreNotEqual(f1, f2);
        }
    }
}