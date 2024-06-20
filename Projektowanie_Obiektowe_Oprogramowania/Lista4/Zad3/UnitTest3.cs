using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using Zad3;

namespace UnitTestsZad3
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void InvalidCapacity()
        {
            Assert.ThrowsException<ArgumentException>(
                () =>
                {
                    ObjectPool pool = new ObjectPool(0);
                });
        }

        [TestMethod]
        public void ValidCapacity()
        {
            ObjectPool pool = new ObjectPool(1);
            Reusable reusable = pool.AcquireReusable();
            Assert.IsNotNull(reusable);
        }

        [TestMethod]
        public void ReusableCreationBetter()
        {
            var reusable = new BetterReusable();
            int res = reusable.DoWork();
            Console.WriteLine(res);
            Assert.AreEqual(5, res, $"{res}");
        }

        [TestMethod]
        public void CapacityDepleted()
        {
            ObjectPool pool = new ObjectPool(1);
            Reusable reusable = pool.AcquireReusable();
            Assert.ThrowsException<ArgumentException>(
                () =>
                {
                    Reusable reusable2 = pool.AcquireReusable();
                });
        }

        [TestMethod]
        public void CapacityDepletedBetter()
        {
            var reusable1 = new BetterReusable();
            var reusable2 = new BetterReusable();
            var reusable3 = new BetterReusable();
            var reusable4 = new BetterReusable();
            var reusable5 = new BetterReusable();
            Assert.ThrowsException<ArgumentException>(
                () =>
                {
                    var reusable = new BetterReusable();
                });
        }

        [TestMethod]
        public void ReusedObject()
        {
            ObjectPool pool = new ObjectPool(1);
            Reusable reusable = pool.AcquireReusable();
            pool.ReleaseReusable(reusable);
            Reusable reusable2 = pool.AcquireReusable();
            Assert.AreEqual(reusable, reusable2);
        }

        [TestMethod]
        public void ReusedObjectBetter()
        {
            var reusable = new BetterReusable();
            reusable.Release();
            var reusable2 = new BetterReusable();
            Assert.AreEqual(reusable, reusable2);
        }

        [TestMethod]
        public void ReleaseInvalidReusable()
        {
            ObjectPool pool = new ObjectPool(1);
            Reusable reusable = new Reusable();

            Assert.ThrowsException<ArgumentException>(
                () =>
                {
                    pool.ReleaseReusable(reusable);
                });
        }

        [TestMethod]
        public void ReleasedDoWork()
        {
            Assert.ThrowsException<ArgumentException>(
                () =>
                {
                    var reusable = new BetterReusable();
                    reusable.Release();
                    reusable.DoWork();
                });
        }
    }
}