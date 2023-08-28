package com.company;

public class ListElem<E> {
    E val;
    ListElem next;

    public ListElem(E val){
        this.val=val;
        next = null;
    }
}
