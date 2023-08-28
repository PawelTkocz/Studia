using System;
using System.Text;

class IntStream
{
    public int number;

    public int next()
    {
        if (this.eos()==false) return number++;
        return number;
    }

    public bool eos()
    {
        if (number == Int32.MaxValue) return true;
        return false;
    }

    public void reset()
    {
        number = 0;
    }
}

class PrimeStream : IntStream
{
    public const int MaxArraySize = Int32.MaxValue-100;
    private bool[] isprime;
    private int next_prime;
    public PrimeStream()
    {
        isprime = new bool[MaxArraySize];
        next_prime = 1;
    }

    public int next()
    {
        if (this.eos()==false) return next_prime;
        return 0;
    }

    public bool eos()
    {
        for (int i = next_prime+1; i <= Math.Sqrt(MaxArraySize); i++)
        {
            if (isprime[i] == false)
            {
                next_prime = i;
                for (int j = i * i; (j < MaxArraySize && j>=0); j += i)
                    isprime[j] = true;
                return false;
            }
        }
        return true;
    }

    public void reset()
    {
        next_prime = 1;
    }

}

class RandomStream : IntStream
{
    public int next()
    {
        Random rand = new Random();
        return rand.Next();
    }

    public bool eos()
    {
        return false;
    }
}

class RandomWordStream
{
    PrimeStream ps;
    RandomStream rs;

    public RandomWordStream()
    {
        ps = new PrimeStream();
        rs = new RandomStream();
    }

    public string next()
    {
        int len = ps.next();
        StringBuilder str_build = new StringBuilder();
        for (int i = 0; i < len; i++)
        {
            int rnd = rs.next();
            char letter = Convert.ToChar(rnd%26 + 65);
            str_build.Append(letter);
        }
        return str_build.ToString();
    }

    public bool eos()
    {
        return ps.eos() || rs.eos();
    }

    public void reset()
    {
        ps.reset();
        rs.reset();
    }

}

class Zadanie1
{
    public static void Main()
    {
        IntStream ints = new IntStream();
        for (int i = 0; i < 20; i++)
        {
            Console.WriteLine(ints.next());
        }
        ints.reset();
        Console.WriteLine(ints.next());
        Console.WriteLine();

        PrimeStream ps = new PrimeStream();
        for (int i = 0; i < 20; i++)
        {
            Console.WriteLine(ps.next());
        }
        ps.reset();
        Console.WriteLine(ps.next());
        Console.WriteLine();

        RandomStream rs = new RandomStream();
        for (int i = 0; i < 20; i++)
        {
            Console.WriteLine(rs.next());
        }
        Console.WriteLine();

        RandomWordStream rws = new RandomWordStream();
        for (int i = 0; i < 20; i++)
        {
            Console.WriteLine(rws.next());
        }
        rws.reset();
        Console.WriteLine(rws.next());

    }
}