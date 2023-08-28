package com.company;

public class MilitaryRank implements Comparable<MilitaryRank> {
    int importance;
    public int compareTo(MilitaryRank o){
        if(this.importance>=o.importance)return 1;
        return -1;
    }
}
