package com.company;

import java.util.Collection;
import java.util.Iterator;

public class List<E> implements Collection<E> {
    ListElem first;
    int length;

    public List(){
        first = null;
        length=0;
    }

    public void push_front(E val){
        ListElem elem = new ListElem(val);
        elem.next = first;
        first = elem;
        length++;
    }

    public void push_back(E val){
        ListElem elem = new ListElem(val);
        ListElem cursor = first;
        if(cursor == null)first = elem;
        else{
            while(cursor.next != null)cursor = cursor.next;
            cursor.next = elem;
        }
        length++;
    }

    public E pop_front() throws Exception{
        if(length==0) throw new Exception("Empty list");
        E res = (E) first.val;
        first = first.next;
        length--;
        return res;
    }

    public E pop_back() throws Exception{
        if(length==0)throw new Exception("Empty list");
        ListElem cursor = first;
        E res;
        if(cursor.next == null){
            res = (E)cursor.val;
            first = null;
            return res;
        }
        while(cursor.next.next != null)cursor = cursor.next;
        res = (E)cursor.next.val;
        cursor.next = null;
        length--;
        return res;
    }

    @Override
    public int size() {
        return length;
    }

    @Override
    public boolean isEmpty() {
        if(first == null)return true;
        return false;
    }

    @Override
    public boolean contains(Object o) {
        ListElem cursor = first;
        while(cursor != null){
            if(cursor.val == o)return true;
            cursor = cursor.next;
        }
        return false;
    }

    @Override
    public Iterator<E> iterator() {
        return null;
    }

    @Override
    public Object[] toArray() {
        Object[] res = new Object[length];
        ListElem cursor = first;
        int ind = 0;
        while(cursor!=null){
            res[ind] = cursor.val;
            ind++;
            cursor=cursor.next;
        }
        return res;
    }

    @Override
    public <T> T[] toArray(T[] a) {
        return null;
    }

    @Override
    public boolean add(E e) {
        push_front(e);
        return true;
    }

    @Override
    public boolean remove(Object o) {
        if(isEmpty())return false;
        ListElem cursor = first.next;
        ListElem prev = first;
        if(prev.val == o){
            first = cursor;
            length--;
            return true;
        }
        while(cursor != null){
            if(cursor.val == o){
                prev.next = cursor.next;
                length--;
                return true;
            }
            cursor=cursor.next;
            prev = prev.next;
        }
        return false;
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        Object[] col = c.toArray();
        int size = c.size();
        for(int i=0; i<size; i++){
            if(contains(col[i]) == false)return false;
        }
        return true;
    }

    @Override
    public boolean addAll(Collection<? extends E> c) {
        Object[] col = c.toArray();
        int size = c.size();
        for(int i=0; i<size; i++){
            add((E)col[i]);
        }
        return true;
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        Object[] col = c.toArray();
        int size = c.size();
        for(int i=0; i<size; i++){
            remove(col[i]);
        }
        return true;
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        Object[] col = c.toArray();
        int size = c.size();
        for(int i=0; i<size; i++){
            if(contains(col[i])==false)return false;
        }
        return true;
    }

    @Override
    public void clear() {
        length = 0;
        first = null;
    }
}
