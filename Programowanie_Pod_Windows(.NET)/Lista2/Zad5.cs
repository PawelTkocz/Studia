using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad5
{
    public class Grid
    {
        private int[,] tab;
        private int columns;
        public Grid(int rows, int columns)
        {
            tab = new int[rows, columns];
            this.columns = columns;
        }
        public int[] this[int x]
        {
            get
            {
                int[] res = new int[columns];
                for(int i = 0; i < columns; i++)
                {
                    res[i] = tab[x-1, i];
                }
                return res;
            }
        }

        public int this[int x, int y]
        {
            get
            {
                return tab[x-1, y-1];
            }
            set
            {
                tab[x-1, y-1] = value;
            }
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            int cnt = 1;
            Grid grid = new Grid(4, 4);
            for(int i=1; i<=4; i++)
            {
                for(int j=1; j<=4; j++)
                {
                    grid[i, j] = cnt++;
                }
            }
            int elem = grid[1, 4];
            Console.WriteLine(elem);

            int[] rowdata = grid[2];
            for(int i=0; i<rowdata.Length; i++)
            {
                Console.Write(rowdata[i].ToString() + " ");
            }
            Console.ReadLine();
        }
    }
}
