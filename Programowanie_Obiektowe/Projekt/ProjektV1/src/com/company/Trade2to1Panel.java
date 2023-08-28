package com.company;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import static com.company.GraphicsInfo.*;

public class Trade2to1Panel extends JPanel {
    Player player;
    Game game;
    JFrame frame;
    Resources.Resource resource;

    public Trade2to1Panel(Game game, Player player, JFrame frame, Resources.Resource resource) {
        this.player = player;
        this.frame = frame;
        this.game =game;
        this.resource = resource;
        make_panel();
    }

    void make_panel(){
        this.setLayout(new GridLayout(3, 1));
        JPanel upper_panel = new JPanel();
        upper_panel.setLayout(new GridLayout(1, 3));
        JLabel two = new JLabel("2", SwingConstants.CENTER);
        two.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        add_color(two, bg_color);
        JLabel empty = new JLabel("");
        add_color(empty, bg_color);
        JLabel one = new JLabel("1", SwingConstants.CENTER);
        one.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        add_color(one, bg_color);
        upper_panel.add(two);
        upper_panel.add(empty);
        upper_panel.add(one);
        this.add(upper_panel);
        JPanel middle_panel = new JPanel();
        middle_panel.setLayout(new GridLayout(1, 3));
        String[] resources = {"Brick", "Lumber", "Wool", "Ore", "Grain"};
        JLabel from = new JLabel(resource.toString(), SwingConstants.CENTER);
        from.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        add_color(from, bg_color);
        JLabel arrow = new JLabel("for", SwingConstants.CENTER);
        arrow.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        add_color(arrow, bg_color);
        JComboBox to = new JComboBox(resources);
        middle_panel.add(from);
        middle_panel.add(arrow);
        middle_panel.add(to);
        this.add(middle_panel);
        JPanel bottom_panel = new JPanel();
        bottom_panel.setLayout(new GridLayout(1, 2));
        JButton confirm = new JButton("Confirm");
        class Confirm_listener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                Resources.Resource to_resource = Resources.resource_array[to.getSelectedIndex()];
                if(player.hand.get_number(resource)>=2){
                    player.hand.change_resource_counter(resource, -2);
                    player.hand.change_resource_counter(to_resource, 1);
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
        int w = 250;
        int h = 100;
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

