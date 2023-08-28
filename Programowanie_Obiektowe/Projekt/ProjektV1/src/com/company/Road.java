package com.company;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Road extends Pawn{
    int direction;
    int building_id_1;
    int building_id_2;

    public Road(Player player, int x, int y, int direction, boolean free, int building_id_1, int building_id_2){
        super(player);
        player.build_road(this, free);
        this.x = x;
        this.y = y;
        this.direction = direction;
        this.x_draw = Calculate.road_x_draw(x, direction);
        this.y_draw = Calculate.road_y_draw(y, direction);
        this.building_id_1 = building_id_1;
        this.building_id_2 = building_id_2;
        image_path = GraphicsInfo.get_road_image_path(player.player_id, direction);
    }
}
