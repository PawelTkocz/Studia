using System;

class Lista<T> 
{
    public List_elem<T>? list_begin;
    public List_elem<T>? list_end;
    public void push_front(T elem)
    {
        if (elem == null) return;
        List_elem<T> new_elem = new List_elem<T>(elem, null, list_begin);
        if (is_empty())
            list_end = new_elem;
        else
            list_begin.prev = new_elem;
        list_begin = new_elem;
    }

    public void push_back(T elem)
    {
        if (elem == null) return;
        List_elem<T> new_elem = new List_elem<T>(elem, list_end, null);
        if (is_empty())
            list_begin = new_elem;
        else
            list_end.next = new_elem;
        list_end = new_elem;
    }

    public T pop_front()
    {
        List_elem<T> frst = list_begin ?? throw new InvalidOperationException("Can't pop_front empty list");
        if(frst.next == null)
            list_end = null;
        else
            frst.next.prev = null;
        list_begin = frst.next;
        return frst.val;
    }

    public T pop_back()
    {
        List_elem<T> last = list_end ?? throw new InvalidOperationException("Can't pop_back empty list");
        if (last.prev == null)
            list_begin = null;
        else
            last.prev.next = null;
        list_end = last.prev;
        return last.val;
    }

    public bool is_empty()
    {
        if (list_begin == null) return true;
        return false;
    }

    public void Write()
    {
        List_elem<T>? cursor = list_begin;
        while(cursor != null)
        {
            Console.Write("{0}, ", cursor.val);
            cursor = cursor.next;
        }
        Console.WriteLine();
    }
}

class List_elem<T>
{
    public T val;
    public List_elem<T>? prev;
    public List_elem<T>? next;

    public List_elem(T val, List_elem<T>? prev, List_elem<T>? next)
    {
        this.val = val;
        this.prev = prev;
        this.next = next;
    }
}

class L3Zad1
{
    public static void Main()
    {
        Lista<int> lst = new Lista<int>();
        for (int i = 0; i < 20; i++)
        {
            lst.push_front(i);
            lst.push_back(-1 * i);
            lst.Write();
        }
        for (int i = 0; i < 20; i++)
        {
            Console.WriteLine(lst.pop_front());
            Console.WriteLine(lst.pop_back());
        }
        Console.WriteLine(lst.is_empty());
    }
}