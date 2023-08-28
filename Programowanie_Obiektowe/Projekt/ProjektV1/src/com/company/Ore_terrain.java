package com.company;

public class Ore_terrain extends Terrain{

    public Ore_terrain(int x, int y, int number){
        super(x, y);
        this.number = number;
        this.image_path = GraphicsInfo.get_terrain_image_path(Resources.Resource.ORE);
        this.resource = Resources.Resource.ORE;
    }
}
