package com.company;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Board {
    BufferedImage frame;
    int board_placement_x;
    int board_placement_y;
    Robber robber;

    Terrain[] board;
    int[][] buildings_positions;
    int[][] roads_positions;
    int[][] terrains_positions;
    int[][] harbours_id_positions = {
            {33, 38},
            {11, 16},
            {42, 46},
            {10, 15},
            {1, 5},
            {0, 3, 26, 32, 47, 49, 51, 52}
    };
    Building[] buildings_on_board;
    Road[] roads_on_board;


    private void generate_standard_board(){
        board[0] = new Ore_terrain(terrains_positions[0][0], terrains_positions[0][1], 10);
        board[1] = new Wool_terrain(terrains_positions[1][0], terrains_positions[1][1], 2);
        board[2] = new Lumber_terrain(terrains_positions[2][0], terrains_positions[2][1], 9);
        board[3] = new Grain_terrain(terrains_positions[3][0], terrains_positions[3][1], 12);
        board[4] = new Brick_terrain(terrains_positions[4][0], terrains_positions[4][1], 6);
        board[5] = new Wool_terrain(terrains_positions[5][0], terrains_positions[5][1], 4);
        board[6] = new Brick_terrain(terrains_positions[6][0], terrains_positions[6][1], 10);
        board[7] = new Grain_terrain(terrains_positions[7][0], terrains_positions[7][1], 9);
        board[8] = new Lumber_terrain(terrains_positions[8][0], terrains_positions[8][1], 11);
        board[9] = new Desert_terrain(terrains_positions[9][0], terrains_positions[9][1]);
        board[10] = new Lumber_terrain(terrains_positions[10][0], terrains_positions[10][1], 3);
        board[11] = new Ore_terrain(terrains_positions[11][0], terrains_positions[11][1], 8);
        board[12] = new Lumber_terrain(terrains_positions[12][0], terrains_positions[12][1], 8);
        board[13] = new Ore_terrain(terrains_positions[13][0], terrains_positions[13][1], 3);
        board[14] = new Grain_terrain(terrains_positions[14][0], terrains_positions[14][1], 4);
        board[15] = new Wool_terrain(terrains_positions[15][0], terrains_positions[15][1], 5);
        board[16] = new Brick_terrain(terrains_positions[16][0], terrains_positions[16][1], 5);
        board[17] = new Grain_terrain(terrains_positions[17][0], terrains_positions[17][1], 6);
        board[18] = new Wool_terrain(terrains_positions[18][0], terrains_positions[18][1], 11);
        for(Terrain t : board){
            t.calculate_buildings_around_id(buildings_positions);
        }
    }

    public Board(int board_placement_x, int board_placement_y){
        buildings_positions = new int[54][2];
        roads_positions = new int[72][2];
        terrains_positions = new int[19][2];
        this.board_placement_x = board_placement_x;
        this.board_placement_y = board_placement_y;
        calculate_buildings_positions();
        calculate_road_positions();
        calculate_terrain_positions();
        board = new Terrain[19];
        generate_standard_board();
        buildings_on_board = new Building[54];
        roads_on_board = new Road[72];
        robber = new Robber(null, terrains_positions[9][0], terrains_positions[9][1]);
        robber.terrain_id = 9;
    }

    private void calculate_terrain_positions(){
        for(int i=0; i<19; i++){
            terrains_positions[i][0] = Calculate.get_terrain_position_x(i, board_placement_x);
            terrains_positions[i][1] = Calculate.get_terrain_position_y(i, board_placement_y);
        }
    }

    private void calculate_buildings_positions(){
        for (int i=0; i<54; i++){
            buildings_positions[i][0] = Calculate.get_building_position_x(i, board_placement_x);
            buildings_positions[i][1] = Calculate.get_building_position_y(i, board_placement_y);
        }
    }

    private void calculate_road_positions(){
        for(int i=0; i<72; i++){
            roads_positions[i][0] = Calculate.get_road_position_x(i, board_placement_x);
            roads_positions[i][1] = Calculate.get_road_position_y(i, board_placement_y);
        }
    }

    void draw(Graphics g) {
        draw_frame(g);
        draw_terrains(g);
    }

    public void draw_terrains(Graphics g){
        for (Terrain t : board) {
            t.draw(g);
        }
    }

    public void draw_frame(Graphics g){
        try {
            frame = ImageIO.read(new File(GraphicsInfo.frame_image_path));
        } catch (IOException e) {
            System.out.println("Frame not found");
            System.out.print(GraphicsInfo.frame_image_path);
            System.out.print(" could not be found");
            System.exit(-1);
        }

        int x = Calculate.frame_placement_x(board_placement_x);
        int y = Calculate.frame_placement_y(board_placement_y);
        g.drawImage(frame, x, y, null);
    }

}
