package com.company;

public class MergeSort extends Thread{
    Comparable[] tab;

    public MergeSort(Comparable[] tab){
        this.tab = tab;
    }

    private Comparable[] leftHalf(Comparable[] tab){
        int size=tab.length/2;
        Comparable[] res = new Comparable[size];
        for(int i=0; i<size; i++){
            res[i]=tab[i];
        }
        return res;
    }
    private Comparable[] rightHalf(Comparable[] tab){
        int size = tab.length - (tab.length/2);
        Comparable[] res = new Comparable[size];
        for(int i=0; i<size; i++){
            res[i]=tab[i + (tab.length)/2];
        }
        return res;
    }


    public void mergeSort(){
        if(tab.length == 1)return;
        MergeSort tab1 = new MergeSort(leftHalf(tab));
        MergeSort tab2 = new MergeSort(rightHalf(tab));
        tab1.start();
        tab2.start();
        try {
            tab1.join();
            tab2.join();
        } catch(InterruptedException ex) {
            System.out.println(ex);
        }
        merge(tab1, tab2);
    }

    public void run() {
        mergeSort();
    }

    public void merge(MergeSort tab1, MergeSort tab2){
        int i=0;
        int j=0;
        while(i<tab1.tab.length && j<tab2.tab.length){
            if(tab1.tab[i].compareTo(tab2.tab[j])<0){
                tab[i+j]=tab1.tab[i];
                i++;
            }
            else{
                tab[i+j]=tab2.tab[j];
                j++;
            }
        }
        if(i==tab1.tab.length){
            for(int p=j; p<tab2.tab.length; p++)tab[tab1.tab.length+p]=tab2.tab[p];
        }
        else{
            for(int p=i; p<tab1.tab.length; p++)tab[tab2.tab.length+p]=tab1.tab[p];
        }
    }

    public void ToString(){
        for(int i=0; i<tab.length; i++){
            System.out.print(tab[i]+ " ");
        }
        System.out.println();
    }
}
