using System;
using System.Collections;

class PrimeEnum : IEnumerator
{
    int val;
    public PrimeEnum()
    {
        val = 1;
    }
    public bool MoveNext()
    {
        int pom = val+1;
        while(pom <= int.MaxValue && pom >= 2)
        {
            bool prime = true;
            for (int i=2; i*i<=pom; i++)
            {
                if (pom % i == 0)
                {
                    prime = false;
                    break;
                }
            }
            if (prime)
            {
                val = pom;
                return true;
            }
            pom++;
        }
        return false;
    }
    public object Current
    {
        get { return val; }
    }
    public void Reset()
    {
        val = 1;
    }
}

class PrimeCollection : IEnumerable
{
    public IEnumerator GetEnumerator()
    {
        return new PrimeEnum();
    }
}
class L4Zad2
{
    public static void Main()
    {
        PrimeCollection pc = new PrimeCollection();
        foreach (int p in pc)
        {
            Console.WriteLine(p);
        }
    }
}
