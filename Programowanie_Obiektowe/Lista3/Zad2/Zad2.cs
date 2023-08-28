namespace L3Zad2;
using System;

class MyDictionary<K, V>
{
    Lista<Tuple<K, V>> dict;

    public MyDictionary()
    {
        dict = new Lista<Tuple<K, V>>();
    }

    private List_elem<Tuple<K, V>>? FindKey(K key)
    {
        List_elem<Tuple<K, V>>? cursor = dict.list_begin;
        while (cursor != null)
        {
            if (EqualityComparer<K>.Default.Equals(cursor.val.Item1, key)) return cursor;
            cursor = cursor.next;
        }
        return null;
    }

    public void AddElem(K key, V value)
    {
        if (FindKey(key) == null)
        {
            Tuple<K, V> new_elem = new Tuple<K, V>(key, value);
            dict.push_back(new_elem);
        }
    }

    public V Find(K key)
    {
        List_elem<Tuple<K, V>>? res = FindKey(key);
        if (res != null) return res.val.Item2;
        else throw new Exception("Key not found");
    } 

    public void Remove(K key)
    {
        List_elem<Tuple<K, V>>? res = FindKey(key);
        if(res != null)
        {
            if (res.prev == null) dict.pop_front();
            else if (res.next == null) dict.pop_back();
            else
            {
                res.prev.next = res.next;
                res.next.prev = res.prev;
            }
        }
    }

    public void Write()
    {
        List_elem<Tuple<K, V>>? cursor = dict.list_begin;
        while (cursor != null)
        {
            Console.WriteLine("{0}, {1}", cursor.val.Item1, cursor.val.Item2);
            cursor = cursor.next;
        }
    }
}

class L3Zad2
{
    public static void Main()
    {
        MyDictionary<string, int> map = new MyDictionary<string, int>();
        map.AddElem("one", 1);
        map.AddElem("two", 2);
        map.AddElem("three", 3);
        map.AddElem("four", 4);
        map.AddElem("five", 5);
        map.AddElem("six", 6);
        map.AddElem("seven", 7);
        map.AddElem("eight", 8);
        map.AddElem("nine", 9);
        map.AddElem("ten", 10);
        int a = map.Find("nine") * map.Find("four");
        int b = map.Find("two") * map.Find("three");
        Console.WriteLine("{0}, {1}", a, b);
        map.Remove("five");
        map.Write();
    }
}
