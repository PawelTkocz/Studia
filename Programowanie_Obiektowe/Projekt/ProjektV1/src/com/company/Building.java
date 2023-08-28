package com.company;

public abstract class Building extends Pawn{

    public Building(Player player) {
        super(player);
    }

    public abstract int get_resources();
}
