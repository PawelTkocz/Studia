package com.company;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class PojazdWidokSwing extends JComponent {

    public PojazdWidokSwing(Pojazd p, ObecnyStan obecnyStan, boolean nowy_pojazd){
        JFrame frame = new JFrame("Edycja pojazdu");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container kontener = frame.getContentPane();
        GridLayout layout = new GridLayout(4, 2);
        kontener.setLayout(layout);
        JLabel liczba_pas_etykieta = new JLabel("Liczba pasazerow");
        kontener.add(liczba_pas_etykieta);
        JTextField liczba_pas = new JTextField(Integer.toString(p.liczba_pasazerow));
        kontener.add(liczba_pas);
        JLabel dlugosc_etykieta = new JLabel("Dlugosc");
        kontener.add(dlugosc_etykieta);
        JTextField dlugosc = new JTextField(Double.toString(p.dlugosc));
        kontener.add(dlugosc);
        JLabel szerokosc_etykieta = new JLabel("Szerokosc");
        kontener.add(szerokosc_etykieta);
        JTextField szerokosc = new JTextField(Double.toString(p.szerokosc));
        kontener.add(szerokosc);
        JButton zapisz = new JButton("Zapisz");
            class MyListener implements ActionListener
            {
                public void actionPerformed(ActionEvent e) {
                    p.szerokosc = Double.parseDouble(szerokosc.getText());
                    p.dlugosc = Double.parseDouble(dlugosc.getText());
                    p.liczba_pasazerow = Integer.parseInt(liczba_pas.getText());
                    if(nowy_pojazd){
                        obecnyStan.pojazdy_tab[obecnyStan.l_pojazdow] = p;
                        obecnyStan.l_pojazdow++;
                    }
                    frame.dispose();
                    obecnyStan.frame_do_zamkniecia.dispose();
                    obecnyStan.WyswietlObecnyStan();
                }
            }
        zapisz.addActionListener(new MyListener());
        kontener.add(zapisz);
        frame.pack();
        frame.setVisible(true);
    }
}
