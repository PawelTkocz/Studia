using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Zad1;

namespace UnitTests
{
    [TestClass]
    public class UnitTest3
    {
        [TestMethod]
        public void MixingRegisterTypesNotSingleton()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<Foo>(true);
            c.RegisterType<IWorker, Foo>(false);
            Foo f1 = c.Resolve<Foo>();
            Foo f2 = c.Resolve<Foo>();
            Foo f3 = (Foo)c.Resolve<IWorker>();

            Assert.AreEqual(f1, f2);
            Assert.AreNotEqual(f1, f3);
        }

        [TestMethod]
        public void MixingRegisterTypesSingleton()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<Foo>(false);
            c.RegisterType<IWorker, Foo>(true);
            Foo f1 = c.Resolve<Foo>();
            Foo f2 = c.Resolve<Foo>();
            Foo f3 = (Foo)c.Resolve<IWorker>();
            Foo f4 = (Foo)c.Resolve<IWorker>();

            Assert.AreNotEqual(f1, f2);
            Assert.AreEqual(f3, f4);
        }

        [TestMethod]
        public void MixingRegisterTypesOnlySingletons()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<Foo>(true);
            c.RegisterType<IWorker, Foo>(true);
            Foo f1 = c.Resolve<Foo>();
            Foo f2 = (Foo)c.Resolve<IWorker>();

            Assert.AreEqual(f1, f2);
        }

        [TestMethod]
        public void RegisterInstance()
        {
            SimpleContainer c = new SimpleContainer();
            IWorker f1 = new Foo();
            c.RegisterInstance<IWorker>(f1);
            IWorker f2 = c.Resolve<IWorker>();

            Assert.AreEqual(f1, f2);
        }

        [TestMethod]
        public void RegisterInstanceMix1()
        {
            SimpleContainer c = new SimpleContainer();
            IWorker f1 = new Foo();
            c.RegisterInstance<IWorker>(f1);
            c.RegisterType<Foo>(false);
            IWorker f2 = c.Resolve<IWorker>();

            Assert.AreEqual(f1, f2);
        }

        [TestMethod]
        public void RegisterInstanceMix2()
        {
            SimpleContainer c = new SimpleContainer();
            IWorker f1 = new Foo();
            c.RegisterInstance<IWorker>(f1);
            c.RegisterType<IWorker, Foo>(true);
            IWorker f2 = c.Resolve<IWorker>();

            Assert.AreNotEqual(f1, f2);
        }

        [TestMethod]
        public void RegisterInstanceMix3()
        {
            SimpleContainer c = new SimpleContainer();
            IWorker f1 = new Foo();
            c.RegisterInstance<IWorker>(f1);
            c.RegisterType<IWorker, Bar>(true);
            IWorker f2 = c.Resolve<IWorker>();

            Assert.AreNotEqual(f1, f2);
        }
    }
}
