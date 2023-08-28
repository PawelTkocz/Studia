package com.company;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public abstract class Pawn {
    Player player;
    int x;
    int y;
    int x_draw;
    int y_draw;
    String image_path;
    BufferedImage image;

    public Pawn(Player player){
        this.player = player;
    }

    public void draw(Graphics g){
        try {
            image = ImageIO.read(new File(image_path));
        } catch (IOException e) {
            System.out.println("Pawn image unfound");
            System.out.print(image_path);
            System.out.print(" could not be found");
            System.exit(-1);
        }
        g.drawImage(image, x_draw, y_draw, null);
    }
}
