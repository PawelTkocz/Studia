package com.company;

public class Main {

    public static void main(String[] args) {
        OrderedList list = new OrderedList();
        PrivateFirstClass pfc = new PrivateFirstClass();
        Corporal crp = new Corporal();
        FirstSergeant fsgt = new FirstSergeant();
        Private pvt = new Private();
        list.add_element(pfc);
        list.add_element(fsgt);
        list.add_element(pvt);
        list.add_element(crp);
        System.out.println(list.get_first().toString());
        System.out.println(list.toString());
    }
}
