package com.company;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Player {
    int player_id;
    String color;
    Hand hand;
    PlayerPawns playerPawns;
    City[] cities;
    Settlement[] settlements;
    Road[] roads;
    boolean[] harbours_available;

    public Player(int id){
        this.player_id = id;
        this.color = GraphicsInfo.color1;
        if(player_id == 1)this.color = GraphicsInfo.color2;
        playerPawns = new PlayerPawns();
        cities = new City[4];
        settlements = new Settlement[5];
        roads = new Road[15];
        hand = new Hand();
        harbours_available = new boolean[6];
    }

    public void draw_roads(Graphics g){
        for (Road r : roads) {
            if(r != null) r.draw(g);
        }
    }

    public void draw_cities(Graphics g){
        for (City c : cities) {
            if(c != null)c.draw(g);
        }
    }

    public void draw_settlements(Graphics g){
        for(Settlement s : settlements){
            if(s != null)s.draw(g);
        }
    }

    public void build_city(City city, boolean free){
        cities[playerPawns.cities_on_board] = city;
        playerPawns.settlements_on_board--;
        playerPawns.cities_on_board++;
        if(!free)hand.build_city();
    }

    public void build_road(Road road, boolean free){
        roads[playerPawns.roads_on_board] = road;
        playerPawns.roads_on_board++;
        if(!free)hand.build_road();
    }

    public void build_settlement(Settlement settlement, boolean free, int harbour_id){
        settlements[playerPawns.settlements_on_board] = settlement;
        playerPawns.settlements_on_board++;
        if(!free)hand.build_settlement();
        if(harbour_id!=-1)harbours_available[harbour_id]=true;
    }

    BufferedImage image;

    public void draw_hand(Graphics g){
        int x = Calculate.get_hand_offset_x(player_id);
        int y = Calculate.get_hand_offset_y();
        int card_x;
        int card_number=0;
        int[] resources = hand.get_resources_array();
        for(int i=0; i<5; i++){
            if(resources[i]>0){
                try {
                    image = ImageIO.read(new File(GraphicsInfo.get_card_image_path(Resources.resource_array[i])));
                } catch (IOException e) {
                    System.out.println("Card image not found");
                    System.out.print(GraphicsInfo.get_card_image_path(Resources.resource_array[i]));
                    System.out.print(" could not be found");
                    System.exit(-1);
                }
                card_x = Calculate.get_resource_card_offset(card_number);
                card_number++;
                g.drawImage(image, x+card_x, y, null);
            }
        }
    }

    boolean road_leading_to_building_id(int building_id){
        for(int i=0; i< playerPawns.roads_on_board; i++){
            if(roads[i].building_id_1==building_id || roads[i].building_id_2==building_id)return true;
        }
        return false;
    }

    boolean game_over(){
        return playerPawns.points()>=10;
    }

    String getColor(){
        return color.substring(0, 1).toUpperCase() + color.substring(1);
    }
}
