using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using Zad2;

namespace Zad2Tests
{
    public class Circle : IShape
    {
        public int radius;

        public Circle(int radius)
        {
            this.radius = radius;
        }

        public double Area()
        {
            return 3.14 * radius * radius;
        }
    }

    public class CircleFactoryWorker : IShapeFactoryWorker
    {
        public bool AcceptsParameters(string name, object[] parameters)
        {
            return name == "Circle" && parameters.Length == 1 && parameters[0] is int;
        }

        public IShape Create(object[] parameters)
        {
            return new Circle((int)parameters[0]);
        }
    }

    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void CreationSuccess()
        {
            ShapeFactory factory = new ShapeFactory();
            IShape square = factory.CreateShape("Square", 7);

            Assert.IsNotNull(square);
            Assert.AreEqual(square.Area(), 49);
        }

        [TestMethod]
        public void CreationDifferentShapes()
        {
            ShapeFactory factory = new ShapeFactory();
            IShape square = factory.CreateShape("Square", 7);
            factory.RegisterWorker(new RectangleFactoryWorker());
            IShape rect = factory.CreateShape("Rectangle", 2, 3);

            Assert.IsNotNull(square);
            Assert.AreEqual(square.Area(), 49);
            Assert.IsNotNull(rect);
            Assert.AreEqual(rect.Area(), 6);
        }

        [TestMethod]
        public void InvalidArguments()
        {
            ShapeFactory factory = new ShapeFactory();
            Assert.ThrowsException<ArgumentException>(
                () => factory.CreateShape("Rectangle", 3, "text")
            );
        }

        [TestMethod]
        public void ShapeNotFound()
        {
            ShapeFactory factory = new ShapeFactory();
            Assert.ThrowsException<ArgumentException>(
                            () => factory.CreateShape("Circle", 3)
            );
        }

        [TestMethod]
        public void NewWorker()
        {
            ShapeFactory factory = new ShapeFactory();
            factory.RegisterWorker(new CircleFactoryWorker());

            IShape circle = factory.CreateShape("Circle", 19);

            Assert.IsNotNull(circle);
            Assert.AreEqual(circle.Area(), 19*19*3.14);
        }
    }
}