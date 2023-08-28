package com.company;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public abstract class Terrain {
    int number;
    Resources.Resource resource;
    int x;
    int y;
    int x_draw;
    int y_draw;
    boolean desert;
    String image_path;
    BufferedImage image;
    BufferedImage number_image;
    int[] buildings_around_id;
    boolean robber;

    public Terrain(int x, int y){
        this.x = x;
        this.y = y;
        x_draw = Calculate.get_terrain_x_draw(x);
        y_draw = Calculate.get_terrain_y_draw(y);
        this.desert = false;
        this.robber = false;
    }

    public void calculate_buildings_around_id(int[][] buildings_position){
        buildings_around_id = Calculate.get_buildings_around_id(x, y, buildings_position);
    }

    public void draw(Graphics g){
        try {
            image = ImageIO.read(new File(image_path));
        } catch (IOException e) {
            System.out.println("Terrain image unfound");
            System.out.print(image_path);
            System.out.print(" could not be found");
            System.exit(-1);
        }
        g.drawImage(image, x_draw, y_draw, null);
        if(!desert)draw_number(g);
    }

    public void draw_number(Graphics g){
        String number_path = GraphicsInfo.get_number_image_path(number);
        try{
            number_image = ImageIO.read(new File(number_path));
        } catch (IOException e){
            System.out.println("Number image unfound");
            System.out.print(number_path);
            System.out.println(" could not be found");
            System.exit(-1);
        }
        int x_off = Calculate.get_number_offset_x();
        int y_off = Calculate.get_number_offset_y();
        g.drawImage(number_image, x_draw + x_off, y_draw + y_off, null);
    }

    public void give_resources(Building[] buildings_on_board, int val){
        if(desert || number != val || robber)return;
        for(int i=0; i<6; i++){
            Building b = buildings_on_board[buildings_around_id[i]];
            if(b != null)
                b.player.hand.change_resource_counter(resource ,b.get_resources());
        }
    }
}
