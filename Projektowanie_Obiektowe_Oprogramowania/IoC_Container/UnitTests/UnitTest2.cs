using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Zad1;

namespace UnitTests
{
    public class BaseClass
    {

    }

    public class ChildClass : BaseClass
    {

    }

    [TestClass]
    public class UnitTest2
    {
        [TestMethod]
        public void ImplementInterfaceNotSingleton()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<IWorker, Foo>(false);
            IWorker f1 = c.Resolve<IWorker>();
            IWorker f2 = c.Resolve<IWorker>();
            Assert.IsInstanceOfType(f1, typeof(Foo));
            Assert.AreNotEqual(f1, f2);
        }

        [TestMethod]
        public void ImplementInterfaceSingleton()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<IWorker, Foo>(true);
            IWorker f1 = c.Resolve<IWorker>();
            IWorker f2 = c.Resolve<IWorker>();
            Assert.IsInstanceOfType(f1, typeof(Foo));
            Assert.AreEqual(f1, f2);
        }

        [TestMethod]
        public void ImplementAbstractClassNotSingleton()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<AbstractClass, DerivedClass>(false);
            AbstractClass f1 = c.Resolve<AbstractClass>();
            AbstractClass f2 = c.Resolve<AbstractClass>();
            Assert.IsInstanceOfType(f1, typeof(DerivedClass));
            Assert.AreNotEqual(f1, f2);
        }

        [TestMethod]
        public void ImplementAbstractClassSingleton()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<AbstractClass, DerivedClass>(true);
            AbstractClass f1 = c.Resolve<AbstractClass>();
            AbstractClass f2 = c.Resolve<AbstractClass>();
            Assert.IsInstanceOfType(f1, typeof(DerivedClass));
            Assert.AreEqual(f1, f2);
        }

        [TestMethod]
        public void ImplementBaseClassNotSingleton()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<BaseClass, ChildClass>(false);
            BaseClass f1 = c.Resolve<BaseClass>();
            BaseClass f2 = c.Resolve<BaseClass>();
            Assert.IsInstanceOfType(f1, typeof(ChildClass));
            Assert.AreNotEqual(f1, f2);
        }

        [TestMethod]
        public void ImplementBaseClassSingleton()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<BaseClass, ChildClass>(true);
            BaseClass f1 = c.Resolve<BaseClass>();
            BaseClass f2 = c.Resolve<BaseClass>();
            Assert.IsInstanceOfType(f1, typeof(ChildClass));
            Assert.AreEqual(f1, f2);
        }

        [TestMethod]
        public void ImplementInterfaceSingletonChanges()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<IWorker, Foo>(true);
            IWorker f1 = c.Resolve<IWorker>();
            c.RegisterType<IWorker, Foo>(false);
            IWorker f2 = c.Resolve<IWorker>();
            c.RegisterType<IWorker, Foo>(true);
            IWorker f3 = c.Resolve<IWorker>();
            Assert.IsInstanceOfType(f1, typeof(Foo));
            Assert.AreNotEqual(f1, f2);
            Assert.AreEqual(f1, f3);
        }

        [TestMethod]
        public void ImplementInterfaceTypeChanges()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<IWorker, Foo>(true);
            IWorker f = c.Resolve<IWorker>();
            c.RegisterType<IWorker, Bar>(false);
            IWorker b = c.Resolve<IWorker>();
            Assert.IsInstanceOfType(f, typeof(Foo));
            Assert.IsInstanceOfType(b, typeof(Bar));
        }

        [TestMethod]
        public void ImplementInterfaceTypeChangesSingleton()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<IWorker, Foo>(true);
            IWorker f = c.Resolve<IWorker>();
            c.RegisterType<IWorker, Bar>(true);
            IWorker b = c.Resolve<IWorker>();
            Assert.IsInstanceOfType(f, typeof(Foo));
            Assert.IsInstanceOfType(b, typeof(Bar));
        }
    }
}
