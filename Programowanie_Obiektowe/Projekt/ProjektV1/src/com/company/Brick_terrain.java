package com.company;

public class Brick_terrain extends Terrain{

    public Brick_terrain(int x, int y, int number){
        super(x, y);
        this.number = number;
        this.image_path = GraphicsInfo.get_terrain_image_path(Resources.Resource.BRICK);
        this.resource = Resources.Resource.BRICK;
    }
}
