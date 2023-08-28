package com.company;

public class Robber extends Pawn{

    int terrain_id;

    public Robber(Player player, int x, int y) {
        super(player);
        move(x, y);
        image_path = GraphicsInfo.robber_path;
    }

    public void move(int x, int y){
        this.x = x;
        this.y = y;
        this.x_draw = Calculate.get_robber_x_draw(x);
        this.y_draw = Calculate.get_robber_y_draw(y);
    }
}
