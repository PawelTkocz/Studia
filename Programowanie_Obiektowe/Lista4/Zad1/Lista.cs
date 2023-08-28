
using System.Collections;

class ListEnum<T> : IEnumerator
{
    List_elem<T> list;
    List_elem<T> current;
    public ListEnum(List_elem<T> elem)
    {
        list = elem;
    }
    public bool MoveNext()
    {
        if (this.current == null) this.current = this.list;
        else this.current = this.current.next;
        return this.current != null;
    }

    public object Current
    {
        get { return current.val; }
    }

    public void Reset()
    {
        this.current = this.list;
    }
}

class Lista<T> : ListCollection, IEnumerable
{
    public List_elem<T>? list_begin;
    public List_elem<T>? list_end;
    int length;

    public IEnumerator GetEnumerator()
    {
        return new ListEnum<T>(list_begin);
    }
    public int Length
    {
        get { return length; }
    }

    public Lista(){
        length = 0;
    }
    public void push_front(T elem)
    {
        if (elem == null) return;
        length++;
        List_elem<T> new_elem = new List_elem<T>(elem, null, list_begin);
        if (Is_empty())
            list_end = new_elem;
        else
            list_begin.prev = new_elem;
        list_begin = new_elem;
    }

    public void push_back(T elem)
    {
        if (elem == null) return;
        length++;
        List_elem<T> new_elem = new List_elem<T>(elem, list_end, null);
        if (Is_empty())
            list_begin = new_elem;
        else
            list_end.next = new_elem;
        list_end = new_elem;
    }

    public T pop_front()
    {
        List_elem<T> frst = list_begin ?? throw new InvalidOperationException("Can't pop_front empty list");
        length--;
        if (frst.next == null)
            list_end = null;
        else
            frst.next.prev = null;
        list_begin = frst.next;
        return frst.val;
    }

    public T pop_back()
    {
        List_elem<T> last = list_end ?? throw new InvalidOperationException("Can't pop_back empty list");
        length--;
        if (last.prev == null)
            list_begin = null;
        else
            last.prev.next = null;
        list_end = last.prev;
        return last.val;
    }

    public void Write()
    {
        List_elem<T>? cursor = list_begin;
        while (cursor != null)
        {
            Console.Write("{0}, ", cursor.val);
            cursor = cursor.next;
        }
        Console.WriteLine();
    }

    public void RemoveFirst()
    {
        List_elem<T> frst = list_begin ?? throw new InvalidOperationException("Can't pop_front empty list");
        length--;
        if (frst.next == null)
            list_end = null;
        else
            frst.next.prev = null;
        list_begin = frst.next;
    }

    public void RemoveLast()
    {
        List_elem<T> last = list_end ?? throw new InvalidOperationException("Can't pop_back empty list");
        length--;
        if (last.prev == null)
            list_begin = null;
        else
            last.prev.next = null;
        list_end = last.prev;
    }

    public bool Is_empty()
    {
        if (list_begin == null) return true;
        return false;
    }

    public override string ToString()
    {
        string result = "";
        List_elem<T>? cursor = list_begin;
        while (cursor != null)
        {
            result += cursor.val.ToString();
            result += " ";
            cursor = cursor.next;
        }
        return result;
    }
    public T this[int indeks]
    {
        get
        {
            return list_begin[indeks];
        }
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
    public T this[int indeks]
    {
        get
        {
            if (indeks == 0) return val;
            return this.next[indeks-1];
        }
    }
}

