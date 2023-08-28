package com.company;

public class Grain_terrain extends Terrain{

    public Grain_terrain(int x, int y, int number){
        super(x, y);
        this.image_path = GraphicsInfo.get_terrain_image_path(Resources.Resource.GRAIN);
        this.number = number;
        this.resource = Resources.Resource.GRAIN;
    }
}

