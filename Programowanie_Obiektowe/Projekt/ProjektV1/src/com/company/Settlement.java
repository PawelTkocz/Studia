package com.company;

public class Settlement extends Building{

    public Settlement(Player player, int x, int y, boolean free, int harbour_id){
        super(player);
        player.build_settlement(this, free, harbour_id);
        image_path = GraphicsInfo.get_pawn_image_path(player.player_id, PawnTypes.Pawn.SETTLEMENT);
        this.x = x;
        this.y = y;
        x_draw = Calculate.building_x_draw(x);
        y_draw = Calculate.building_y_draw(y);
    }

    public int get_resources() {
        return 1;
    }
}
