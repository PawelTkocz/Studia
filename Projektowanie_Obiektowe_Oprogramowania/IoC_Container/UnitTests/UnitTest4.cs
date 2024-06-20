using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Zad1;
using System.Reflection;

namespace UnitTests
{
    public class A
    {
        public B b;
        public A(B b)
        {
            this.b = b;
        }
    }
    public class B { }

    public class X
    {
        public Y d;
        public string s;
        public X(Y d, string s) {
            this.d = d;
            this.s = s;
        }
    }
    public class Y { }


    public class D
    {
        public E e;
        public IC c;

        public D(E e, IC c)
        {
            this.e = e;
            this.c = c;
        }
    }

    public class E { }
    public interface IC { }
    public class C : IC { }

    public class F
    {
        public E e1;
        public E? e2;
        public C? c;

        //[System.Reflection.De]
        public F(E e1, C c)
        {
            this.e1 = e1;
            this.e2 = null;
            this.c = c;
        }
        public F(E e1, E e2)
        {
            this.e1 = e1;
            this.e2 = e2;
        }
    }

    public class Rec1 : IWorker
    {
        public Rec1 r;
        public Rec1(Rec1 r)
        {
            this.r = r;
        }

        public int DoWork()
        {
            throw new NotImplementedException();
        }
    }

    public class Rec2
    {
        public Rec2(Rec3 r3) { }
    }

    public class Rec3
    {
        public Rec3(Rec2 r2) { }
    }

    public class DepConstTest
    {
        public E e1;
        public E? e2;

        [DependencyConstructor]
        public DepConstTest(E e1)
        {
            this.e1 = e1;
            e2 = null;
        }
        public DepConstTest(E e1, E e2)
        {
            this.e1 = e1;
            this.e2 = e2;
        }
    }

    public class DepConstTest2
    {
        public E? e;
        public A? a;

        [DependencyConstructor]
        public DepConstTest2(E e)
        {
            this.e = e;
            this.a = null;
        }

        [DependencyConstructor]
        public DepConstTest2(A a)
        {
            this.e = null;
            this.a = a;
        }

        public DepConstTest2(A a, E e)
        {
            this.e = e;
            this.a = a;
        }
    }

    [TestClass]
    public class UnitTest4
    {
        [TestMethod]
        public void Test1()
        {
            SimpleContainer c = new SimpleContainer();
            A a = c.Resolve<A>();
            Assert.IsNotNull(a.b);
        }

        [TestMethod]
        [ExpectedException(typeof(Exception),
        "No parameterless constructor for type.")]
        public void Test2()
        {
            SimpleContainer c = new SimpleContainer();
            X x = c.Resolve<X>();
        }

        [TestMethod]
        public void Test3()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterInstance("ala ma kota");
            X x = c.Resolve<X>();
            Assert.IsNotNull(x.d);
            Assert.AreEqual(x.s, "ala ma kota");
        }

        [TestMethod]
        public void Test4()
        {
            SimpleContainer container = new SimpleContainer();
            container.RegisterType<IC, C>(false);
            D d = container.Resolve<D>();
            Assert.IsNotNull(d.e);
            Assert.IsNotNull(d.c);
        }

        [TestMethod]
        [ExpectedException(typeof(Exception),
        "More than one possible contructor to resolve.")]
        public void Test5()
        {
            SimpleContainer c = new SimpleContainer();
            F f = c.Resolve<F>();
        }

        [TestMethod]
        [ExpectedException(typeof(Exception),
        "Cycle detected during recursive dependency injection.")]
        public void Test6()
        {
            SimpleContainer c = new SimpleContainer();
            Rec1 r = c.Resolve<Rec1>();
        }

        [TestMethod]
        [ExpectedException(typeof(Exception),
        "Cycle detected during recursive dependency injection.")]
        public void Test7()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<IWorker, Rec1>(true);
            IWorker r = c.Resolve<IWorker>();
        }

        [TestMethod]
        [ExpectedException(typeof(Exception),
        "Cycle detected during recursive dependency injection.")]
        public void Test8()
        {
            SimpleContainer c = new SimpleContainer();
            Rec2 r = c.Resolve<Rec2>();
        }

        [TestMethod]
        public void Test9()
        {
            SimpleContainer c = new SimpleContainer();
            DepConstTest dct = c.Resolve<DepConstTest>();
            Assert.IsNull(dct.e2);
            Assert.IsNotNull(dct.e1);
        }

        [TestMethod]
        public void Test10()
        {
            SimpleContainer c = new SimpleContainer();
            DepConstTest2 dct = c.Resolve<DepConstTest2>();
            Assert.IsNotNull(dct.e);
            Assert.IsNotNull(dct.a);
        }
    }
}
