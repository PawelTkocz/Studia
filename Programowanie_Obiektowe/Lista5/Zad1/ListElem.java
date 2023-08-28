package com.company;

public class ListElem<T>{
    Comparable<T> elem;
    ListElem next;

    public ListElem(Comparable<T> elem){
        this.elem = elem;
        next = null;
    }
}
