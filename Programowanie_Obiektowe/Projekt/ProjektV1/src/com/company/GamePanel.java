package com.company;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.*;

import static com.company.GraphicsInfo.*;

public class GamePanel extends JPanel implements MouseListener {
    Game game;
    BufferedImage image;

    JButton build_road;
    JButton build_settlement;
    JButton build_city;
    JButton end_turn;
    JButton trade_opponent;
    JButton trade_4_1;
    JButton trade_harbour;
    JLabel[] resource_counter1;
    JLabel[] resource_counter2;
    JLabel[] pawns_left_counter1;
    JLabel[] pawns_left_counter2;
    JLabel whose_turn;

    public GamePanel(Game game) {
        this.setLayout(null);
        this.game = game;
        this.addMouseListener(this);
        add_buttons();
        resource_counter1 = new JLabel[5];
        resource_counter2 = new JLabel[5];
        pawns_left_counter1 = new JLabel[3];
        pawns_left_counter2 = new JLabel[3];
        add_resource_counter(0);
        add_resource_counter(1);
        add_pawn_counter(0);
        add_pawn_counter(1);
        add_turn_info();
    }

    @Override
    public Dimension getPreferredSize() {
        int w = game.background_image.getWidth();
        int h = game.background_image.getHeight();
        return new Dimension(w, h);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (game.background_image != null) {
            g.drawImage(game.background_image, 0, 0, null);
        }
        draw_dices(g);
        draw_building_costs(g);
        draw_pawns_left(g, 0);
        draw_pawns_left(g, 1);

        game.board.draw(g);
        game.playerA.draw_hand(g);
        game.playerB.draw_hand(g);
        game.playerA.draw_roads(g);
        game.playerB.draw_roads(g);
        game.playerA.draw_cities(g);
        game.playerB.draw_cities(g);
        game.playerA.draw_settlements(g);
        game.playerB.draw_settlements(g);
        game.board.robber.draw(g);
        actualize_buttons();
        actualize_resources_counters();
        actualize_pawn_counters();
        actualize_turn_info();
    }

    void draw_dices(Graphics g){
        game.dice1.draw(g);
        game.dice2.draw(g);
    }

    void add_pawn_counter(int id){
        JPanel pawns_left_counter = new JPanel();
        pawns_left_counter.setOpaque(false);
        GridLayout gridLayout = new GridLayout(1, 3);
        pawns_left_counter.setLayout(gridLayout);

        JLabel settlement_counter = new JLabel("", SwingConstants.CENTER);
        settlement_counter.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 50));
        settlement_counter.setForeground(Color.black);
        JLabel city_counter = new JLabel("", SwingConstants.CENTER);
        city_counter.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 50));
        city_counter.setForeground(Color.black);
        JLabel road_counter = new JLabel("", SwingConstants.CENTER);
        road_counter.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 50));
        road_counter.setForeground(Color.black);

        pawns_left_counter.add(settlement_counter);
        pawns_left_counter.add(city_counter);
        pawns_left_counter.add(road_counter);
        JLabel[] pawns_left_counter_array;
        if(id==0){
            pawns_left_counter_array = pawns_left_counter1;
        }
        else pawns_left_counter_array = pawns_left_counter2;
        pawns_left_counter_array[0]=settlement_counter;
        pawns_left_counter_array[1]=city_counter;
        pawns_left_counter_array[2]=road_counter;

        int x=Calculate.get_pawn_counter_offset_x(id);
        int y=Calculate.get_pawn_counter_offset_y();
        int width=Calculate.get_pawn_counter_width();
        int height=Calculate.get_pawn_counter_height();
        pawns_left_counter.setBounds(x, y, width, height);
        this.add(pawns_left_counter);

    }

    void draw_pawns_left(Graphics g, int id){
        String image_path = GraphicsInfo.pine_bg_red;
        if(id==1)image_path = GraphicsInfo.pine_bg_blue;
        try{
            image = ImageIO.read(new File(image_path));
        } catch (IOException e){
            System.exit(-1);
        }
        g.drawImage(image, Calculate.get_pine_bg_x(id), Calculate.get_pine_bg_y(), null);
    }

    void draw_building_costs(Graphics g){
        String image_path = GraphicsInfo.building_costs_image_path;
        try{
            image = ImageIO.read(new File(image_path));
        } catch (IOException e){
            System.exit(-1);
        }
        g.drawImage(image, 10, 10, null);
    }

    void actualize_resources_counters(){
        int[] tab1 = game.playerA.hand.get_resources_array();
        int pom=0;
        for(int i = 0; i<5; i++){
            if(tab1[i]!=0){
                resource_counter1[pom].setText(Integer.toString(tab1[i]));
                pom++;
            }
        }
        for(int i=pom; i<5; i++){
            resource_counter1[i].setText("");
        }
        int[] tab2 = game.playerB.hand.get_resources_array();
        pom=0;
        for(int i = 0; i<5; i++){
            if(tab2[i]!=0){
                resource_counter2[pom].setText(Integer.toString(tab2[i]));
                pom++;
            }
        }
        for(int i=pom; i<5; i++){
            resource_counter2[i].setText("");
        }
    }

    void actualize_pawn_counters(){
        pawns_left_counter1[0].setText(Integer.toString(game.playerA.playerPawns.settlements_left()));
        pawns_left_counter1[1].setText(Integer.toString(game.playerA.playerPawns.cities_left()));
        pawns_left_counter1[2].setText(Integer.toString(game.playerA.playerPawns.roads_left()));
        pawns_left_counter2[0].setText(Integer.toString(game.playerB.playerPawns.settlements_left()));
        pawns_left_counter2[1].setText(Integer.toString(game.playerB.playerPawns.cities_left()));
        pawns_left_counter2[2].setText(Integer.toString(game.playerB.playerPawns.roads_left()));
    }

    void actualize_turn_info(){
        if(game.game_started){
            if(game.playerA_turn)whose_turn.setText("Red's turn");
            else whose_turn.setText("Blue's turn");
        }
        else{
            whose_turn.setText("Throw dices to start the game");
        }
    }

    void actualize_buttons(){
        style_button(end_turn, button_color(game.ready_to_end_turn(), false));
        if(game.game_started){
            style_button(build_road, button_color(game.player_can_build_road(), game.build_road));
            style_button(build_settlement, button_color(game.player_can_build_settlement(), game.build_settlement));
            style_button(build_city, button_color(game.player_can_build_city(), game.build_city));
            style_button(trade_opponent, button_color(true, false));
            style_button(trade_4_1, button_color(game.player_can_trade_4_1(), false));
            style_button(trade_harbour, button_color(game.player_can_trade_harbour(), false));
        }
        else{
            style_button(build_road, button_color(false, false));
            style_button(build_settlement, button_color(false, false));
            style_button(build_city, button_color(false, false));
            style_button(trade_opponent, button_color(false, false));
            style_button(trade_4_1, button_color(false, false));
            style_button(trade_harbour, button_color(false, false));
        }
    }

    private void add_turn_info(){
        whose_turn = new JLabel("", SwingConstants.CENTER);
        whose_turn.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 40));
        whose_turn.setForeground(Color.black);
        int x=Calculate.get_turn_info_offset_x();
        int y=Calculate.get_turn_info_offset_y();
        int width=Calculate.get_turn_info_width();
        int height=Calculate.get_turn_info_height();
        whose_turn.setBounds(x, y, width, height);
        this.add(whose_turn);

    }

    private void add_resource_counter(int id){
        JPanel resource_counter = new JPanel();
        resource_counter.setOpaque(false);
        GridLayout gridLayout = new GridLayout(1, 5);
        gridLayout.setHgap(7);
        resource_counter.setLayout(gridLayout);

        JLabel brick_counter = new JLabel();
        brick_counter.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 60));
        brick_counter.setForeground(Color.black);
        JLabel lumber_counter = new JLabel();
        lumber_counter.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 60));
        lumber_counter.setForeground(Color.black);
        JLabel wool_counter = new JLabel();
        wool_counter.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 60));
        wool_counter.setForeground(Color.black);
        JLabel ore_counter = new JLabel();
        ore_counter.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 60));
        ore_counter.setForeground(Color.black);
        JLabel grain_counter = new JLabel();
        grain_counter.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 60));
        grain_counter.setForeground(Color.black);
        resource_counter.add(brick_counter);
        resource_counter.add(lumber_counter);
        resource_counter.add(wool_counter);
        resource_counter.add(ore_counter);
        resource_counter.add(grain_counter);
        JLabel[] resource_counter_array;
        if(id==0){
            resource_counter_array = resource_counter1;
        }
        else resource_counter_array = resource_counter2;
        resource_counter_array[0]=brick_counter;
        resource_counter_array[1]=lumber_counter;
        resource_counter_array[2]=wool_counter;
        resource_counter_array[3]=ore_counter;
        resource_counter_array[4]=grain_counter;
        int x=Calculate.get_resource_counter_offset_x(id);
        int y=Calculate.get_resource_counter_offset_y();
        int width=Calculate.get_resource_counter_width();
        int height=Calculate.get_resource_counter_height();
        resource_counter.setBounds(x, y, width, height);
        this.add(resource_counter);
    }

    private void add_buttons(){
        JPanel buttons = new JPanel();
        buttons.setOpaque(false);
        buttons.setLayout(new GridLayout(6, 1));
        build_road = new JButton("Build road");
        build_settlement = new JButton("Build settlement");
        build_city = new JButton("Build city");
        trade_opponent = new JButton("Trade with opponent");
        trade_4_1 = new JButton("Trade 4:1");
        trade_harbour = new JButton("Trade with harbour");
        class Build_road_listener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                if(game.build_road==true){
                    game.build_road = false;
                    build_road.setBackground(color_active);
                }
                else if(game.buttons_disabled==false && game.player_can_build_road()){
                    if(game.game_started){
                        game.build_road = true;
                        game.build_settlement = false;
                        game.build_city = false;
                        actualize_buttons();
                    }
                }
            }
        }
        build_road.addActionListener(new Build_road_listener());

        class Build_settlement_listener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                if(game.build_settlement==true){
                    game.build_settlement = false;
                    build_settlement.setBackground(color_active);
                }
                else if(game.buttons_disabled==false && game.player_can_build_settlement()){
                    if(game.game_started){
                        game.build_settlement = true;
                        game.build_city = false;
                        game.build_road = false;
                        actualize_buttons();
                    }
                }
            }
        }
        build_settlement.addActionListener(new Build_settlement_listener());

        class Build_city_listener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                if(game.build_city==true){
                    game.build_city = false;
                    build_city.setBackground(color_active);
                }
                else if(game.buttons_disabled==false && game.player_can_build_city()){
                    if(game.game_started){
                        game.build_city = true;
                        game.build_settlement = false;
                        game.build_road = false;
                        actualize_buttons();
                    }
                }
            }
        }
        build_city.addActionListener(new Build_city_listener());

        class Trade_opponent_listener implements ActionListener{
            public void actionPerformed(ActionEvent e){
                if(!game.buttons_disabled && game.game_started)game.player_trade();
            }
        }
        trade_opponent.addActionListener(new Trade_opponent_listener());

        class Trade_4_1_listener implements ActionListener{
            public void actionPerformed(ActionEvent e){
                if(!game.buttons_disabled && game.player_can_trade_4_1() && game.game_started)game.trade_4_1();
            }
        }
        trade_4_1.addActionListener(new Trade_4_1_listener());

        class Trade_harbour_listener implements ActionListener{
            public void actionPerformed(ActionEvent e){
                if(!game.buttons_disabled && game.player_can_trade_harbour() && game.game_started)game.trade_harbour();
            }
        }
        trade_harbour.addActionListener(new Trade_harbour_listener());

        buttons.add(build_road);
        buttons.add(build_settlement);
        buttons.add(build_city);
        buttons.add(trade_opponent);
        buttons.add(trade_4_1);
        buttons.add(trade_harbour);
        int width = GraphicsInfo.button_width;
        int height = GraphicsInfo.button_height * 6;
        buttons.setBounds(Calculate.get_buttons_x(), Calculate.get_buttons_y(), width, height);
        this.add(buttons);

        end_turn = new JButton("Throw dices");
        class End_turn_listener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                if(game.buttons_disabled==false && game.ready_to_end_turn()){
                    game.build_road=false;
                    game.build_settlement=false;
                    game.build_city=false;
                    game.throw_dices();
                }
            }
        }
        end_turn.addActionListener(new End_turn_listener());
        width = GraphicsInfo.button_width/3*2;
        height = GraphicsInfo.button_height/3*2;
        end_turn.setBounds(Calculate.get_end_turn_x(), Calculate.get_end_turn_y(), width, height);
        this.add(end_turn);
    }

    void style_button(JButton b, Color c){
        b.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        b.setBackground(c);
        b.setForeground(Color.black);
        b.setBorder(BorderFactory.createLineBorder(Color.black, 3));
        b.setFocusPainted(false);
    }

    Color button_color(boolean can_afford, boolean selected){
        if(game.buttons_disabled)return color_not_active;
        if(!can_afford)return color_not_active;
        else if(selected) return color_selected;
        else return color_active;
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        game.mouse_clicked(e.getX(), e.getY());
    }

    @Override
    public void mousePressed(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }
}

