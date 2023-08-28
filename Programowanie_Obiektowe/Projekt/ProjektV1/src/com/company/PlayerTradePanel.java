package com.company;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import static com.company.GraphicsInfo.*;

public class PlayerTradePanel extends JPanel {
    Player player1;
    Player player2;
    Game game;
    JFrame frame;
    JSpinner[] counter1;
    JSpinner[] counter2;

    public PlayerTradePanel(Game game, Player player1, Player player2, JFrame frame) {
        this.player1 = player1;
        this.player2 = player2;
        this.frame = frame;
        this.game =game;
        counter1 = new JSpinner[5];
        counter2 = new JSpinner[5];
        make_panel();
    }

    void make_panel(){
        this.setLayout(new GridLayout(7, 1));
        JPanel upper_panel = new JPanel();
        upper_panel.setLayout(new GridLayout(1, 3));
        JLabel red_offers = new JLabel("Red offers:", SwingConstants.CENTER);
        red_offers.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        add_color(red_offers, bg_color);
        JLabel empty = new JLabel("");
        add_color(empty, bg_color);
        JLabel blue_offers = new JLabel("Blue offers:", SwingConstants.CENTER);
        blue_offers.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        add_color(blue_offers, bg_color);
        upper_panel.add(red_offers);
        upper_panel.add(empty);
        upper_panel.add(blue_offers);
        this.add(upper_panel);

        String[] resources = {"Brick", "Lumber", "Wool", "Ore", "Grain"};
        for(int i=0; i<5; i++){
            JPanel row = new JPanel();
            row.setLayout(new GridLayout(1, 3));
            JLabel resource = new JLabel(resources[i], SwingConstants.CENTER);
            resource.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
            add_color(resource, bg_color);
            JSpinner resource_val_1 = new JSpinner(new SpinnerNumberModel(0, 0, 100, 1));
            JSpinner resource_val_2 = new JSpinner(new SpinnerNumberModel(0, 0, 100, 1));
            counter1[i] = resource_val_1;
            counter2[i] = resource_val_2;
            row.add(resource_val_1);
            row.add(resource);
            row.add(resource_val_2);
            this.add(row);
        }

        JPanel bottom_panel = new JPanel();
        bottom_panel.setLayout(new GridLayout(1, 2));
        JButton confirm = new JButton("Make trade");
        class Confirm_listener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                int brick1 = (int)counter1[0].getValue();
                int lumber1 = (int)counter1[1].getValue();
                int wool1 = (int)counter1[2].getValue();
                int ore1 = (int)counter1[3].getValue();
                int grain1 = (int)counter1[4].getValue();
                int brick2 = (int)counter2[0].getValue();
                int lumber2 = (int)counter2[1].getValue();
                int wool2 = (int)counter2[2].getValue();
                int ore2 = (int)counter2[3].getValue();
                int grain2 = (int)counter2[4].getValue();
                int[] tab1 = {brick1, lumber1, wool1, ore1, grain1};
                int[] tab2 = {brick2, lumber2, wool2, ore2, grain2};
                boolean valid_trade=true;
                for(int i=0; i<5; i++){
                    if(player1.hand.get_number(Resources.resource_array[i]) < tab1[i])valid_trade=false;
                    if(player2.hand.get_number(Resources.resource_array[i]) < tab2[i])valid_trade=false;
                }
                if(valid_trade){
                    for(int i=0; i<5; i++){
                        player1.hand.change_resource_counter(Resources.resource_array[i], -1*tab1[i]);
                        player1.hand.change_resource_counter(Resources.resource_array[i], tab2[i]);
                        player2.hand.change_resource_counter(Resources.resource_array[i], tab1[i]);
                        player2.hand.change_resource_counter(Resources.resource_array[i], -1*tab2[i]);
                    }
                    game.refresh_board();
                }
            }
        }
        confirm.addActionListener(new Confirm_listener());
        confirm.setBackground(button_color);
        JButton finish = new JButton("Finish");
        class Finish_listener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                game.buttons_disabled = false;
                frame.dispose();
                game.refresh_board();
            }
        }
        finish.addActionListener(new Finish_listener());
        finish.setBackground(button_color);
        bottom_panel.add(confirm);
        bottom_panel.add(finish);
        this.add(bottom_panel);
    }

    @Override
    public Dimension getPreferredSize() {
        int w = 450;
        int h = 200;
        return new Dimension(w, h);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
    }

    private void add_color(JLabel label, Color color){
        label.setOpaque(true);
        label.setBackground(color);
    }
}


