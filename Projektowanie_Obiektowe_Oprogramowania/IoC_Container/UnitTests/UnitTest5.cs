using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Zad1;

namespace UnitTests
{
    public class TestClass
    {
        public A a;
        public TestClass(A a)
        {
            this.a = a;
        }

        [DependencyProperty]
        public Q? q1 { get; set; }

        [DependencyProperty]
        public Q? q2 { get; private set; }

        public Q? q3 { get; set; }

        [DependencyProperty]
        public Q? q4 { get; set; }
    }

    public class Q
    {
        public A a;
        public Q(A a)
        {
            this.a = a;
        }

        [DependencyProperty]
        public B? b { get; set; }
    }

    [TestClass]
    public class UnitTest5
    {
        [TestMethod]
        public void Test1()
        {
            SimpleContainer c = new SimpleContainer();
            TestClass tc = c.Resolve<TestClass>();
            Assert.IsNotNull(tc.a);
            Assert.IsNotNull(tc.q1);
        }

        [TestMethod]
        public void Test2()
        {
            SimpleContainer c = new SimpleContainer();
            TestClass tc = c.Resolve<TestClass>();
            Assert.IsNull(tc.q2);
        }

        [TestMethod]
        public void Test3()
        {
            SimpleContainer c = new SimpleContainer();
            TestClass tc = c.Resolve<TestClass>();
            Assert.IsNull(tc.q3);
        }

        [TestMethod]
        public void Test4()
        {
            SimpleContainer c = new SimpleContainer();
            c.RegisterType<Q>(true);
            TestClass tc = c.Resolve<TestClass>();
            Assert.IsNotNull(tc.q1);
            Assert.AreEqual(tc.q1, tc.q4);
        }

        [TestMethod]
        public void Test5()
        {
            SimpleContainer c = new SimpleContainer();
            TestClass tc = c.Resolve<TestClass>();
            Assert.IsNotNull(tc.q1);
            Assert.IsNotNull(tc.q1.b);
        }

        [TestMethod]
        public void Test6()
        {
            SimpleContainer c = new SimpleContainer();

            B b = new B();
            A a = new A(b);
            Q q = new Q(a);
            Assert.IsNull(q.b);
            c.BuildUp(q);
            Assert.IsNotNull(q.b);
        }
    }
}
