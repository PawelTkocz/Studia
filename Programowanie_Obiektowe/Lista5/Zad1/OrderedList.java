package com.company;

public class OrderedList<T> {
    ListElem<T> first;

    public void add_element(Comparable<T> elem){
        ListElem new_elem = new ListElem(elem);
        if(first == null) first = new_elem;
        else if(new_elem.elem.compareTo(first.elem)<=0){
            new_elem.next=first;
            first = new_elem;
        }
        else{
            ListElem previous = first;
            ListElem cursor = first.next;
            while(cursor != null && new_elem.elem.compareTo(cursor.elem) > 0){
                previous=cursor;
                cursor = cursor.next;
            }
            new_elem.next = cursor;
            previous.next = new_elem;
        }
    }

    Comparable<T> get_first(){
        return first.elem;
    }

    public String toString(){
        ListElem cursor = first;
        String answer="";
        while(cursor!=null){
            answer = answer + cursor.elem.toString() + " ";
            cursor = cursor.next;
        }
        return answer;
    }
}
