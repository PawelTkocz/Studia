package com.company;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import static com.company.GraphicsInfo.*;

public class TradeHarbourPanel extends JPanel {
    Player player;
    Game game;
    JFrame frame;

    public TradeHarbourPanel(Game game, Player player, JFrame frame) {
        this.player = player;
        this.frame = frame;
        this.game =game;
        make_panel();
    }

    void make_panel(){
        this.setLayout(new GridLayout(7, 1));

        String[] resources = {"Brick", "Lumber", "Wool", "Ore", "Grain"};
        for(int i=0; i<5; i++){
            String text = resources[i] + " 2:1";
            JButton b = new JButton(text);
            int finalI = i;
            class Listener implements ActionListener
            {
                public void actionPerformed(ActionEvent e) {
                    if(game.player_can_trade(finalI)){
                        frame.dispose();
                        game.trade_2_1(Resources.resource_array[finalI]);
                    }
                }
            }
            b.addActionListener(new Listener());
            b.setBackground(get_color(game.player_can_trade(i)));
            b.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
            this.add(b);
        }

        JButton three_one = new JButton("Trade 3:1");
        class Three_one_listener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                if(game.player_can_trade(5)){
                    frame.dispose();
                    game.trade_3_1();
                }
            }
        }
        three_one.addActionListener(new Three_one_listener());
        three_one.setBackground(get_color(game.player_can_trade(5)));
        three_one.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));

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
        finish.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        this.add(three_one);
        this.add(finish);
    }

    @Override
    public Dimension getPreferredSize() {
        int w = 250;
        int h = 400;
        return new Dimension(w, h);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
    }

    private Color get_color(boolean active){
        if(active)return bg_color;
        else return color_not_active;
    }
}


