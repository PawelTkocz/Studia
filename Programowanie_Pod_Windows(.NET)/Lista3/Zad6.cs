using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad6
{
    public class BinaryTreeNode<T>
    {
        public BinaryTreeNode<T> Left { get; set; }
        public BinaryTreeNode<T> Right { get; set; }
        public T value { get; set; }

        public IEnumerable<T> DFS()
        {
            yield return this.value;
            if (this.Left != null)
            {
                foreach (T t in this.Left.DFS())
                {
                    yield return t;
                }

            }
            if (this.Right != null)
            {
                foreach (T t in this.Right.DFS())
                {
                    yield return t;
                }

            }
        }

        public IEnumerable<T> BFS()
        {
            Queue<BinaryTreeNode<T>> queue = new Queue<BinaryTreeNode<T>>();
            queue.Enqueue(this);
            while(queue.Count > 0)
            {
                BinaryTreeNode<T> t = queue.Dequeue();
                yield return t.value;
                if(t.Left != null)
                {
                    queue.Enqueue(t.Left);
                }
                if(t.Right != null)
                {
                    queue.Enqueue(t.Right);
                }
            }
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            BinaryTreeNode<int> root = new BinaryTreeNode<int>
            {
                Left = new BinaryTreeNode<int>
                {
                    Left = new BinaryTreeNode<int>
                    {
                        Left = null,
                        value = 6,
                        Right = null
                    },
                    value = 8,
                    Right = new BinaryTreeNode<int>
                    {
                        Right = null,
                        value = 9,
                        Left = null
                    }
                },
                value = 12,
                Right = new BinaryTreeNode<int>
                {
                    Left = new BinaryTreeNode<int>
                    {
                        Left = null,
                        value = 16,
                        Right = null
                    },
                    value = 18,
                    Right = new BinaryTreeNode<int>
                    {
                        Right = null,
                        value = 24,
                        Left = null
                    }
                }
            };

            Console.WriteLine("BFS");
            foreach(int i in root.BFS())
            {
                Console.WriteLine(i);
            }

            Console.WriteLine("DFS");
            foreach (int i in root.DFS())
            {
                Console.WriteLine(i);
            }
            Console.ReadLine();
        }
    }
}
