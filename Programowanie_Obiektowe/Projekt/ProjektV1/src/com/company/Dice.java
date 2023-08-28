package com.company;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Dice {
    private int value;
    int x;
    int y;
    BufferedImage image;

    public Dice(int v, int id){
        value = v;
        x = Calculate.get_dice_x_position(id);
        y = Calculate.get_dice_y_position();
    }

    public int throw_dice(){
        value = (int)(Math.random()*5+1);
        return value;
    }

    public void draw(Graphics g){
        String dice_path = GraphicsInfo.get_dice_image_path(value);
        try{
            image = ImageIO.read(new File(dice_path));
        } catch (IOException e){
            System.exit(-1);
        }
        g.drawImage(image, x, y, null);
    }
}
