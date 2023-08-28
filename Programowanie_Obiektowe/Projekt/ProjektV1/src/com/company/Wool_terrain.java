package com.company;

public class Wool_terrain extends Terrain{

    public Wool_terrain(int x, int y, int number){
        super(x, y);
        this.number = number;
        this.image_path = GraphicsInfo.get_terrain_image_path(Resources.Resource.WOOL);
        this.resource = Resources.Resource.WOOL;
    }
}
