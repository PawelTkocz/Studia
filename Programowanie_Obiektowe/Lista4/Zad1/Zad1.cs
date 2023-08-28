using System;

interface ListCollection
{
    public void RemoveFirst();
    public void RemoveLast();
    public bool Is_empty();
    public void Write();
}

class L4Zad1
{
    public static void Main()
    {
        Lista<int> list = new Lista<int>();
        for(int i=0; i<10; i++)
        {
            list.push_back(i * i);
        }
        list.Write();
        list.RemoveFirst();
        list.Write();
        list.RemoveLast();
        list.Write();
        Console.WriteLine(list.ToString());
        Console.WriteLine(list[5]);
        Console.WriteLine(list.Length);
        Console.WriteLine(list.Is_empty());
        foreach (int e in list)
        {
            Console.Write("{0} ", e - 1);
        }
    }

}