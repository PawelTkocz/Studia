using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad2
{
    public interface IShape
    {
        double Area();
    }

    public class Rectangle : IShape
    {
        public int width;
        public int height;

        public Rectangle(int widht, int height)
        {
            this.width = widht;
            this.height = height;
        }

        public double Area()
        {
            return width * height;
        }
    }
    public class Square : IShape
    {
        public int side;
        public Square(int side)
        {
            this.side = side;
        }

        public double Area()
        {
            return side * side;
        }
    }
    public interface IShapeFactoryWorker
    {
        bool AcceptsParameters(string name, object[] parameters);
        IShape Create(object[] parameters);
    }
    public class RectangleFactoryWorker : IShapeFactoryWorker
    {
        public bool AcceptsParameters(string name, object[] parameters)
        {
            return name == "Rectangle" && parameters.Length == 2 && parameters[0] is int && parameters[1] is int;
        }

        public IShape Create(object[] parameters)
        {
            return new Rectangle((int)parameters[0], (int)parameters[1]);
        }
    }
    public class SquareFactoryWorker : IShapeFactoryWorker
    {
        public bool AcceptsParameters(string name, object[] parameters)
        {
            return name == "Square" && parameters.Length == 1 && parameters[0] is int;
        }

        public IShape Create(object[] parameters)
        {
            return new Square((int)parameters[0]);
        }
    }

    public class ShapeFactory
    {
        private List<IShapeFactoryWorker> _workers = new List<IShapeFactoryWorker>();

        public ShapeFactory()
        {
            this._workers.Add(new SquareFactoryWorker());
        }

        public void RegisterWorker(IShapeFactoryWorker worker)
        {
            _workers.Add(worker);
        }

        public IShape CreateShape(string ShapeName, params object[] parameters)
        {
            foreach (var worker in _workers)
            {
                if (worker.AcceptsParameters(ShapeName, parameters))
                    return worker.Create(parameters);
            }

            throw new ArgumentException("Unknown Shape");
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            // klient
            ShapeFactory factory = new ShapeFactory();
            IShape square = factory.CreateShape("Square", 5);
            // rozszerzenie
            factory.RegisterWorker(new RectangleFactoryWorker());
            IShape rect = factory.CreateShape("Rectangle", 3, 5);
            Console.WriteLine("{0} {1}", square.Area(), rect.Area());
            Console.ReadLine();
        }
    }
}
