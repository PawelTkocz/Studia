package com.company;

import java.awt.*;

public class GraphicsInfo {
    static final String main_directory = "Graphics/";
    static final String board_directory = "Board_parts/";
    static final String numbers_directory = "Numbers/";
    static final String cards_directory = "Cards/";
    static final String pawns_directory = "Pawns/";
    static final String dice_directory = "Dice/";
    static final String others_directory = "Others/";
    static final String format = ".png";
    static final String color1 = "red";
    static final String color2 = "Blue";
    static final String bg_image_path = main_directory + others_directory + "bg" + format;
    static final String pine_bg_red = main_directory + others_directory + "pine_bg_red" + format;
    static final String pine_bg_blue = main_directory + others_directory + "pine_bg_blue" + format;
    static final String robber_path = main_directory + pawns_directory + "robber" + format;
    static final String building_costs_image_path = main_directory + others_directory +  "building_costs" + format;
    static final String frame_image_path = main_directory + board_directory + "frame" + format;

    static String get_number_image_path(int i){
        return main_directory + numbers_directory + i + format;
    }

    static String get_terrain_image_path(Resources.Resource resource){
        return main_directory + board_directory + resource.toString() + "_terrain" + format;
    }

    static String get_card_image_path(Resources.Resource resource){
        return main_directory + cards_directory + resource.toString() + format;
    }

    static String get_pawn_image_path(int Player_id, PawnTypes.Pawn pawn){
        String final_color = color1;
        if(Player_id==1)final_color = color2;
        return main_directory + pawns_directory + final_color + "_" + pawn.toString() + format;
    }

    static String get_road_image_path(int Player_id, int direction){
        String final_color = color1;
        if(Player_id==1) final_color = color2;
        return main_directory + pawns_directory + final_color + "_" + PawnTypes.Pawn.ROAD + direction + format;
    }

    static String get_dice_image_path(int i){
        return main_directory + dice_directory + "dice" + i + format;
    }

    static final int terrain_width = 130;
    static final int building_width = 45;
    static final int building_height = 50;
    static final int bg_image_height = 814;
    static final int bg_image_width = 1568;
    static final int resource_card_height = 143;
    static final int resource_card_width = 90;
    static final int number_width = 45;
    static final int dice_width = 70;
    static final int button_height = 50;
    static final int button_width = 300;
    static final int building_cost_height = 220;
    static final int pine_bg_width = 294;
    static final int pine_bg_height = 106;
    static final int robber_height = 90;
    static final int robber_width = 40;

    static final Color bg_color = new Color(240, 181, 125);
    static final Color button_color = new Color(234, 150, 72);
    static final Color color_active = new Color(219, 146, 101);
    static final Color color_not_active = new Color(169, 169, 169);
    static final Color color_selected = new Color(207, 109, 48);
}
