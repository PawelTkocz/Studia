package com.company;

import static com.company.GraphicsInfo.*;

public class Calculate {

    static final double a = terrain_width/Math.sqrt(3);
    static final int margin = 5;

    static final int[][] x_offsets = {
            {21 , 27},
            {11, 16, 33, 38},
            {3, 7, 22, 28, 43, 47},
            {0, 12, 17, 34, 39, 51},
            {4, 8, 23, 29, 44, 48},
            {1, 13, 18, 35, 40, 52},
            {5, 9, 24, 30, 45, 49},
            {2, 14, 19, 36, 41, 53},
            {6, 10, 25, 31, 46, 50},
            {15, 20, 37, 42},
            {26, 32}
    };

    static final int[][] y_offsets = {
            {0, 1, 2},
            {3, 4, 5, 6},
            {7, 8, 9, 10},
            {11, 12, 13, 14, 15},
            {16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25, 26},
            {27, 28, 29, 30, 31, 32},
            {33, 34, 35, 36, 37},
            {38, 39, 40, 41, 42},
            {43, 44, 45, 46},
            {47, 48, 49, 50},
            {51, 52, 53}
    };

    static final int[][] x_offsets_roads = {
            {33},
            {23, 39},
            {18, 49},
            {10, 24, 40, 54},
            {6, 34, 62},
            {0, 11, 25, 41, 55, 66},
            {19, 50},
            {1, 12, 26, 42, 56, 67},
            {7, 35, 63},
            {2, 13, 27, 43, 57, 68},
            {20, 51},
            {3, 14, 28, 44, 58, 69},
            {8, 36, 64},
            {4, 15, 29, 45, 59, 70},
            {21, 52},
            {5, 16, 30, 46, 60, 71},
            {9, 37, 65},
            {17, 31, 47, 61},
            {22, 53},
            {32, 48},
            {38}
    };

    static final int[][] y_offsets_roads = {
            {0, 1, 2, 3, 4, 5},
            {6, 7, 8, 9},
            {10, 11, 12, 13, 14, 15, 16, 17},
            {18, 19, 20, 21, 22},
            {23, 24, 25, 26, 27, 28, 29, 30, 31, 32},
            {33, 34, 35, 36, 37, 38},
            {39, 40, 41, 42, 43, 44, 45, 46, 47, 48},
            {49, 50, 51, 52, 53},
            {54, 55, 56, 57, 58, 59, 60, 61},
            {62, 63, 64, 65},
            {66, 67, 68, 69, 70, 71}
    };

    static final int[][] road_directions = {
            {1, 3, 5, 11, 13, 15, 17, 24, 26, 28, 30, 32, 39, 41, 43, 45, 47, 54, 56, 58, 60, 66, 68, 70},
            {6, 7, 8, 9, 18, 19, 20, 21, 22, 33, 34, 35, 36, 37, 38, 49, 50, 51, 52, 53, 62, 63, 64, 65},
            {0, 2, 4, 10, 12, 14, 16, 23, 25, 27, 29, 31, 40, 42, 44, 46, 48, 55, 57, 59, 61, 67, 69, 71}
    };

    static final double[] y_offsets2 = {0, 0.5, 1.5, 2, 3, 3.5, 4.5, 5, 6, 6.5, 7.5, 8};

    static int board_placement_x(int bg_image_width){
        return (int)(bg_image_width/2-2.5*terrain_width);
    }

    static int board_placement_y(){
        return terrain_width;
    }

    static int frame_placement_x(int board_placement_x){
        return (int)(board_placement_x - 0.8*terrain_width);
    }

    static int frame_placement_y(int board_placement_y){
        return (board_placement_y - terrain_width/2-margin);
    }

    static int get_x_offset(int id){
        if(id==7)return 1;
        else if(id==3 || id==12)return 2;
        else if(id==0 || id==8|| id==16)return 3;
        else if(id==4 || id==13)return 4;
        else if(id==1 || id==9 || id==17)return 5;
        else if(id==5 || id==14)return 6;
        else if(id==2 || id==10 || id==18)return 7;
        else if(id==6 || id==15)return 8;
        else if(id==11)return 9;
        return 0;
    }

    static double get_y_offset(int c){
        int row=-1;
        if(c>=0 && c<=2)row=0;
        else if(c>=3 && c<=6)row=1;
        else if(c>=7 && c<=11)row=2;
        else if(c>=12 && c<=15)row=3;
        else if(c>=16 && c<=18)row=4;
        return a+row*(1.5 * a);
    }

    static int get_terrain_position_y(int id, int board_y){
        return (int)(board_y + get_y_offset(id));
    }

    static int get_terrain_position_x(int id, int board_x){
        return (board_x + terrain_width/2 * get_x_offset(id));
    }

    static int get_terrain_x_draw(int x){
        return x - terrain_width/2;
    }

    static int get_terrain_y_draw(int y){
        return (int)(y-a);
    }

    static int get_road_position_x(int id, int board_x){
        for(int i=0; i<x_offsets_roads.length; i++){
            for(int j=0; j<x_offsets_roads[i].length; j++){
                if(x_offsets_roads[i][j]==id)return (int)(board_x + i*(double)terrain_width/4);
            }
        }
        return 0;
    }

    static int get_road_position_y(int id, int board_y){
        for(int i=0; i<y_offsets_roads.length; i++){
            for(int j=0; j<y_offsets_roads[i].length; j++){
                if(y_offsets_roads[i][j]==id)return (int)(board_y + (0.25 + i * 0.75)*a);
            }
        }
        return 0;
    }

    static int get_road_direction(int id){
        for(int i=0; i<3; i++){
            for(int j=0; j<road_directions[i].length; j++){
                if(road_directions[i][j]==id)return i+1;
            }
        }
        return 0;
    }

    static int road_x_draw(int x, int direction){
        if(direction==1 || direction==3)return x-terrain_width/4;
        else if(direction==2)return x-8;
        return 0;
    }

    static int road_y_draw(int y, int direction){
        if(direction==1 || direction==3)return (int)(y-a/4 - 5);
        else if(direction == 2)return (int)(y-a/2);
        return 0;
    }

    static int get_building_position_x(int id, int board_placement_x){
        for(int i=0; i<x_offsets.length; i++){
            for(int j=0; j<x_offsets[i].length; j++){
                if(x_offsets[i][j]==id)return board_placement_x + i*terrain_width/2;
            }
        }
        return 0;
    }

    static int get_building_position_y(int id, int board_placement_y){
        for(int i=0; i<y_offsets.length; i++){
            for(int j=0; j<y_offsets[i].length; j++){
                if(y_offsets[i][j]==id)return (int)(board_placement_y + y_offsets2[i]*a);
            }
        }
        return 0;
    }

    static boolean clicked_in_area(int x, int y, int x_b, int y_b){
        double r = a/4;
        if((Math.abs(y-y_b)<r)&&(Math.abs(x-x_b)<r))return true;
        return false;
    }

    static int building_x_draw(int x){
        return x - building_width/2;
    }

    static int building_y_draw(int y){
        return y-(int)(building_height*0.8);
    }

    static int get_hand_offset_x(int id){
        if(id==0)return margin;
        else return (bg_image_width-5*(margin+resource_card_width)-margin);
    }

    static int get_hand_offset_y(){
        return bg_image_height - resource_card_height - 2*margin;
    }

    static int get_resource_card_offset(int id){
        return id*(resource_card_width+7);
    }

    static int get_resource_counter_offset_x(int id){
        return get_hand_offset_x(id);
    }
    static int get_resource_counter_offset_y(){
        return get_hand_offset_y();
    }
    static int get_resource_counter_width(){
        return 5*resource_card_width+28;
    }
    static int get_resource_counter_height(){
        return resource_card_height/2;
    }

    static int get_number_offset_x(){
        return terrain_width/2 - number_width/2;
    }
    static int get_number_offset_y(){
        return (int)(a-number_width/2);
    }

    static int get_dice_x_position(int id){
        return 5*margin+id*(dice_width+margin);
    }

    static int get_dice_y_position(){
        return building_cost_height + button_height/3*2 + 5*margin;
    }

    static int get_buttons_x(){
        return bg_image_width - button_width - margin;
    }

    static int get_buttons_y(){
        return margin;
    }

    static int get_end_turn_x(){
        return 2*margin;
    }

    static int get_end_turn_y(){
        return building_cost_height+5*3;
    }

    static int get_turn_info_offset_x(){
        return bg_image_width/2 - get_turn_info_width()/2;
    }

    static int get_turn_info_offset_y(){
        return 1;
    }

    static int get_turn_info_width(){
        return 5*terrain_width;
    }

    static int get_turn_info_height(){
        return button_height;
    }

    static boolean terrain_clicked_in_area(int x, int y, int x_b, int y_b){
        int r = terrain_width/2-5;
        if((Math.abs(y-y_b)<r)&&(Math.abs(x-x_b)<r))return true;
        return false;
    }

    static int get_pine_bg_x(int id){
        if(id == 0) return margin;
        else return bg_image_width - pine_bg_width - margin;
    }

    static int get_pine_bg_y(){
        return bg_image_height - resource_card_height - 40 - pine_bg_height;
    }

    static int get_pawn_counter_offset_x(int id){
        if(id ==0) return margin * 2;
        else return bg_image_width - pine_bg_width + margin;
    }

    static int get_pawn_counter_offset_y(){
        return get_pine_bg_y() + margin;
    }

    static int get_pawn_counter_width(){
        return pine_bg_width * 5/6 + 2 * margin;
    }

    static int get_pawn_counter_height(){
        return pine_bg_height;
    }

    static int[] get_buildings_around_id( int x, int y, int[][] building_positions){
        int[] res = new int[6];
        res[0] = get_building_id(x, (int)(y-a), building_positions);
        res[1] = get_building_id(x+terrain_width/2, (int)(y-a/2), building_positions);
        res[2] = get_building_id(x + terrain_width/2, (int)(y+a/2), building_positions);
        res[3] = get_building_id(x, (int)(y+a), building_positions);
        res[4] = get_building_id(x-terrain_width/2, (int)(y+a/2), building_positions);
        res[5] = get_building_id(x-terrain_width/2, (int)(y-a/2), building_positions);
        return res;
    }

    static int get_robber_x_draw(int x){
        return x-robber_width;
    }

    static int get_robber_y_draw(int y){
        return y-robber_height/2;
    }

    static int get_building_id(int x, int y, int[][] building_positions){
        for(int i=0; i<building_positions.length; i++){
            if(clicked_in_area(x, y, building_positions[i][0], building_positions[i][1])){
                return i;
            }
        }
        return -1;
    }

    static boolean buildings_not_too_close(int x, int y, Building[] buildings_on_board, int[][] buildings_position){
        int v1 = get_building_id(x, (int)(y-a), buildings_position);
        int v2 = get_building_id(x+terrain_width/2, (int)(y-a/2), buildings_position);
        int v3 = get_building_id(x+terrain_width/2, (int)(y+a/2), buildings_position);
        int v4 = get_building_id(x, (int)(y+a), buildings_position);
        int v5 = get_building_id(x-terrain_width/2, (int)(y+a/2), buildings_position);
        int v6 = get_building_id(x-terrain_width/2, (int)(y-a/2), buildings_position);
        int[] tab = {v1, v2, v3, v4, v5, v6};
        for(int i=0; i<6; i++){
            if(tab[i]!=-1 && buildings_on_board[tab[i]] != null)return false;
        }
        return true;
    }
}

