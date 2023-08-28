package com.company;

public class Lumber_terrain extends Terrain{
    public Lumber_terrain(int x, int y, int number){
        super(x, y);
        this.image_path = GraphicsInfo.get_terrain_image_path(Resources.Resource.LUMBER);
        this.number = number;
        this.resource = Resources.Resource.LUMBER;
    }
}
