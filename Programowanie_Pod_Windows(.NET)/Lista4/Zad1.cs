using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad1
{
    public static class StringExtensions
    {
        public static bool IsPalindrome(this string s)
        {
            string s2 = new string(s.Where(c => !char.IsPunctuation(c) && !char.IsWhiteSpace(c)).ToArray()).ToLower();
            
            string first = s2.Substring(0, s2.Length / 2);
            char[] arr = s2.ToCharArray();
            Array.Reverse(arr);
            string temp = new string(arr);
            string second = temp.Substring(0, temp.Length / 2);
            return first.Equals(second);
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            string s = "Kobyła ma mały bok.";
            bool ispalindrome = s.IsPalindrome();
            Console.WriteLine(ispalindrome);
            Console.ReadLine();
        }
    }
}
