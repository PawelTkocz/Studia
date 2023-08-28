package com.company;

public class PlayerPawns {
    static final int cities_on_start = 4;
    static final int settlements_on_start = 5;
    static final int roads_on_start = 15;

    int cities_on_board;
    int settlements_on_board;
    int roads_on_board;

    public PlayerPawns(){
        cities_on_board = 0;
        settlements_on_board = 0;
        roads_on_board = 0;
    }

    public int cities_left(){
        return cities_on_start - cities_on_board;
    }

    public int settlements_left(){
        return settlements_on_start - settlements_on_board;
    }

    public int roads_left(){
        return roads_on_start - roads_on_board;
    }

    public int points(){
        return cities_on_board * 2 + settlements_on_board;
    }

}
