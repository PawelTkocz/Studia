package com.company;

public class City extends Building {

    public City(Player player, int x, int y, boolean free){
        super(player);
        player.build_city(this, free);
        this.x = x;
        this.y = y;
        x_draw = Calculate.building_x_draw(x);
        y_draw = Calculate.building_y_draw(y);
        image_path = GraphicsInfo.get_pawn_image_path(player.player_id, PawnTypes.Pawn.CITY);
    }

    public int get_resources() {
        return 2;
    }
}
