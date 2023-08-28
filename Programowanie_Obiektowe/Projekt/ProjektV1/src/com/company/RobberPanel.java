package com.company;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import static com.company.GraphicsInfo.*;

public class RobberPanel extends JPanel {
    Player player;
    Game game;
    int cards;
    JFrame frame;
    JSpinner[] spinners;

    public RobberPanel(Game game, Player player, int cards, JFrame frame) {
        this.player = player;
        this.cards = cards;
        this.frame = frame;
        this.game =game;
        spinners = new JSpinner[5];
        make_panel();
    }

    void make_panel(){
        this.setLayout(new GridLayout(8, 1));
        String player_name = player.getColor();
        String title = player_name + ", You've been robbed!";
        String message = "Choose " + cards + " resources to loose.";
        JLabel message_label = new JLabel(message, SwingConstants.CENTER);
        JLabel title_label = new JLabel(title, SwingConstants.CENTER);
        add_color(title_label, bg_color);
        add_color(message_label, bg_color);
        this.add(title_label);
        this.add(message_label);

        String[] resources = {"Brick", "Lumber", "Wool", "Ore", "Grain"};
        for(int i=0; i<5; i++){
            JPanel row = new JPanel();
            row.setLayout(new GridLayout(1, 2));
            String s = resources[i] + ": ";
            JLabel resource = new JLabel(s, SwingConstants.CENTER);
            add_color(resource, bg_color);
            JSpinner resource_val = new JSpinner(new SpinnerNumberModel(0, 0, 100, 1));
            spinners[i] = resource_val;
            row.add(resource);
            row.add(resource_val);
            this.add(row);
        }

        JButton confirm = new JButton("Confirm");
        class Confirm_listener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                int brick = (int)spinners[0].getValue();
                int lumber = (int)spinners[1].getValue();
                int wool = (int)spinners[2].getValue();
                int ore = (int)spinners[3].getValue();
                int grain = (int)spinners[4].getValue();
                if(brick+lumber+wool+ore+grain==cards){
                    boolean v1 = player.hand.get_number(Resources.Resource.BRICK)>=brick;
                    boolean v2 = player.hand.get_number(Resources.Resource.LUMBER)>=lumber;
                    boolean v3 = player.hand.get_number(Resources.Resource.WOOL)>=wool;
                    boolean v4 = player.hand.get_number(Resources.Resource.ORE)>=ore;
                    boolean v5 = player.hand.get_number(Resources.Resource.GRAIN)>=grain;
                    if(v1 && v2 && v3 && v4 && v5){
                        player.hand.change_resource_counter(Resources.Resource.BRICK, -1* brick);
                        player.hand.change_resource_counter(Resources.Resource.LUMBER, -1* lumber);
                        player.hand.change_resource_counter(Resources.Resource.WOOL, -1* wool);
                        player.hand.change_resource_counter(Resources.Resource.ORE, -1* ore);
                        player.hand.change_resource_counter(Resources.Resource.GRAIN, -1 * grain);
                        game.player_ready(player);
                        if(game.both_players_ready()){
                            game.place_robber = true;
                        }
                        game.refresh_board();
                        frame.dispose();
                    }
                }
            }
        }
        confirm.addActionListener(new Confirm_listener());
        confirm.setBackground(button_color);
        this.add(confirm);
    }

    @Override
    public Dimension getPreferredSize() {
        int w = 250;
        int h = 250;
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
