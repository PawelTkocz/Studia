package com.company;

public abstract class Resources {

    static final Resource[] resource_array = {
            Resource.BRICK,
            Resource.LUMBER,
            Resource.WOOL,
            Resource.ORE,
            Resource.GRAIN,
            Resource.NONE
    };

    public enum Resource {
        BRICK ("Brick"),
        LUMBER ("Lumber"),
        ORE ("Ore"),
        GRAIN ("Grain"),
        WOOL ("Wool"),
        NONE ("Desert");

        private final String resource_name;

        Resource(String s){
            resource_name = s;
        }

        public String toString(){
            return this.resource_name;
        }
    }
}
