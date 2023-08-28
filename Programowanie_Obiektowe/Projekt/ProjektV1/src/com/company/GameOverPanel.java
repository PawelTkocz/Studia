package com.company;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

import static com.company.GraphicsInfo.*;

public class GameOverPanel extends JPanel {
    Game game;
    Frame frame;
    Player winner;
    Player looser;

    public GameOverPanel(Game game, Player winner, Player looser, JFrame frame) {
        this.game =game;
        this.frame = frame;
        this.winner = winner;
        this.looser = looser;
        make_panel();
    }

    void make_panel(){
        this.setLayout(new GridLayout(5, 1));
        JLabel title = new JLabel("Game over", SwingConstants.CENTER);
        title.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 40));
        add_color(title, bg_color);
        this.add(title);

        String message = winner.getColor() + " is the winner!";
        JLabel winner_info = new JLabel(message, SwingConstants.CENTER);
        winner_info.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 30));
        add_color(winner_info, bg_color);
        this.add(winner_info);

        JPanel points_winner = new JPanel();
        points_winner.setLayout(new GridLayout(1, 2));
        JLabel winner_name = new JLabel(winner.getColor(), SwingConstants.CENTER);
        winner_name.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        add_color(winner_name, bg_color);
        points_winner.add(winner_name);
        String points = winner.playerPawns.points() + " points";
        JLabel winner_points_label = new JLabel(points, SwingConstants.CENTER);
        winner_points_label.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        add_color(winner_points_label, bg_color);
        points_winner.add(winner_points_label);
        this.add(points_winner);

        JPanel points_looser = new JPanel();
        points_looser.setLayout(new GridLayout(1, 2));
        JLabel looser_name = new JLabel(looser.getColor(), SwingConstants.CENTER);
        looser_name.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        add_color(looser_name, bg_color);
        points_looser.add(looser_name);
        String points2 = looser.playerPawns.points() + " points";
        JLabel looser_points_label = new JLabel(points2, SwingConstants.CENTER);
        looser_points_label.setFont(new java.awt.Font("Arial Bold", Font.BOLD, 20));
        add_color(looser_points_label, bg_color);
        points_looser.add(looser_points_label);
        this.add(points_looser);

        JButton finish = new JButton("Finish");
        class Finish_listener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        }
        finish.addActionListener(new Finish_listener());
        finish.setBackground(button_color);
        this.add(finish);
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


