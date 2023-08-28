package com.company;

public class Main {

    public static void main(String[] args) {
	    List list = new List();
        list.add(5);
        list.add(13);
        list.add(17);
        list.add(29);
        list.add(101);
        System.out.println(list.size());
        System.out.println(list.isEmpty());
        System.out.println(list.contains(17));
        System.out.println(list.contains(18));
        Object[] tab = list.toArray();
        System.out.println(tab[2]);
        System.out.println(list.remove(101));
        System.out.println(list.contains(101));
    }
}
