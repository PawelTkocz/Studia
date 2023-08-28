package com.company;

public class Main {

    public static void main(String[] args) {
        Comparable numbers[] = new Comparable[] {5, 6, 2, 8, 7, 1, 9, 0, 3, 10, 4};
	    MergeSort tab = new MergeSort(numbers);
        tab.start();
        try {
            tab.join();
        } catch(InterruptedException ex) {
            System.out.println(ex);
        }
        tab.ToString();
    }
}