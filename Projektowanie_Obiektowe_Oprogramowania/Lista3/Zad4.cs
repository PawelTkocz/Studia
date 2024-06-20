using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad4
{
    
    public class Square
    {
        public int Width;
        public int Height;

        public Square(int Width, int Height)
        {
            this.SetWidth(Width);
            this.SetHeight(Height);
        }

        public int GetWidth()
        {
            return Width;
        }
        public int GetHeight()
        {
            return Height;
        }
        public virtual void SetWidth(int value)
        {
            Width = value;
            Height = value;
        }
        public virtual void SetHeight(int value)
        {
            Height = value;
            Width = value;
        }
    }

    public class Rectangle : Square
    {
        public override void SetWidth(int value) { this.Width = value; }
        public override void SetHeight(int value) { this.Height = value; }

        public Rectangle(int Width, int Height) : base(Width, Height) { }
    }

    public class AreaCalculator
    {
        public int CalculateArea(Square square)
        {
            return square.GetHeight() * square.GetWidth();
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {

            int w = 4; int h = 5;
            Square rect = new Rectangle(w, h);
            AreaCalculator calculator = new AreaCalculator();

            Console.WriteLine("Area of {0}x{1} rectangle is {2}", w, h, calculator.CalculateArea(rect));
            Console.ReadLine();
        }
    }
}
