package com.company;

public class Desert_terrain extends Terrain{

    public Desert_terrain(int x, int y){
        super(x, y);
        this.image_path = GraphicsInfo.get_terrain_image_path(Resources.Resource.NONE);
        this.desert = true;
        this.robber = true;
        this.resource = Resources.Resource.NONE;
    }
}
