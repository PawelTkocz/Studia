package com.company;

public abstract class PawnTypes {

    public enum Pawn{
        ROAD ("road"),
        SETTLEMENT ("settlement"),
        CITY ("city");

        private final String pawn_name;

        Pawn(String s){
            pawn_name = s;
        }

        public String toString(){
            return this.pawn_name;
        }
    }
}
