using System;
class BigNum
{
    public const int MaxLen = 100;
    public const int DefaultLen = 80;
    public int[] number;
    bool negative;

    public BigNum()
    {
        number = new int[MaxLen];
        negative = false;
        Random rand = new Random();
        for (int i = MaxLen - DefaultLen; i < MaxLen; i++)
        {
            number[i] = rand.Next(10);
        }
    }
    public BigNum(int n)
    {
        number = new int[MaxLen];
        if(n < 0)
        {
            negative = true;
            n *= -1;
        }
        int i = 0;
        while(n > 0)
        {
            number[MaxLen - 1 - i] = n % 10;
            n/= 10;
            i++;
        }
    }
    private int len()
    {
        for (int i = 0; i < MaxLen; i++)
        {
            if (number[i] != 0)
            {
                return MaxLen - i;
            }
        }
        return 1;
    }

    private bool bigger_abs(BigNum x)
    {
        for(int i=0; i<MaxLen; i++)
        {
            if (this.number[i] > x.number[i]) return true;
            else if (this.number[i] < x.number[i]) return false;
        }
        return false;
    }
    public void Write()
    {
        if (this.negative) Console.Write("-");
        int length = len();
        for (int i = MaxLen-length; i < MaxLen; i++)
        {
            Console.Write(number[i]);
        }
        Console.WriteLine();
    }
    public BigNum Add(BigNum x)
    {
        BigNum res;
        if (x.negative==false && this.negative)
        {
            this.negative = false;
            res = x.Sub(this);
            this.negative = true;
            return res;
        }
        else if (x.negative && this.negative==false)
        {
            x.negative = false;
            res = this.Sub(x);
            x.negative = true;
            return res;
        }
        res = new BigNum(0);
        int rst = 0;
        for (int i = MaxLen-1; i >= 0; i--)
        {
            res.number[i] = (x.number[i] + this.number[i] + rst) % 10;
            rst = (x.number[i] + this.number[i] + rst) / 10;
        }
        if (x.negative && this.negative) res.negative = true;
        if (rst > 0) Console.WriteLine("Przekroczenie zakresu");
        return res;
    }

    public BigNum Sub(BigNum x)
    {
        BigNum res;
        if (x.negative)
        {
            x.negative = false;
            res = this.Add(x);
            x.negative= true;
            return res;
        }
        else if (this.negative)
        {
            this.negative = false;
            res = this.Add(x);
            this.negative = true;
            res.negative = true;
            return res;
        }
        else if (x.bigger_abs(this))
        {
            res = x.Sub(this);
            res.negative = true;
            return res;
        }
        res = new BigNum(0);
        int rst = 0;
        for (int i = MaxLen - 1; i >= 0; i--) 
        {
            res.number[i] = (this.number[i] - x.number[i] - rst);
            rst = 0;
            if(res.number[i] < 0)
            {
                res.number[i] += 10;
                rst = 1;
            } 
        }
        return res;
    }
}
class Zadanie3
{
    public static void Main()
    {
        BigNum a = new BigNum(1234567);
        BigNum b = new BigNum();
        BigNum c = new BigNum();
        a.Write();
        b.Write();
        c.Write();
        BigNum d = a.Add(b);
        BigNum e = c.Add(b);
        BigNum f = a.Sub(c);
        BigNum g = e.Sub(f);
        d.Write();
        e.Write();
        f.Write();
        g.Write();
    }
}