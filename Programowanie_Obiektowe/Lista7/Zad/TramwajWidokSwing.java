package com.company;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TramwajWidokSwing extends JComponent{

    public TramwajWidokSwing(Tramwaj t, ObecnyStan obecnyStan, boolean nowy_tramwaj){
        JFrame frame = new JFrame("Edycja tramwaju");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container kontener = frame.getContentPane();
        GridLayout layout = new GridLayout(7, 2);
        kontener.setLayout(layout);
        JLabel liczba_pas_etykieta = new JLabel("Liczba pasazerow");
        kontener.add(liczba_pas_etykieta);
        JTextField liczba_pas = new JTextField(Integer.toString(t.liczba_pasazerow));
        kontener.add(liczba_pas);
        JLabel dlugosc_etykieta = new JLabel("Dlugosc");
        kontener.add(dlugosc_etykieta);
        JTextField dlugosc = new JTextField(Double.toString(t.dlugosc));
        kontener.add(dlugosc);
        JLabel szerokosc_etykieta = new JLabel("Szerokosc");
        kontener.add(szerokosc_etykieta);
        JTextField szerokosc = new JTextField(Double.toString(t.szerokosc));
        kontener.add(szerokosc);
        JLabel obukierunkowy_etykieta = new JLabel("Obukierunkowy (T/N)");
        kontener.add(obukierunkowy_etykieta);
        JTextField obukierunkowy;
        if(t.obukierunkowy)obukierunkowy = new JTextField("T");
        else obukierunkowy = new JTextField("N");
        kontener.add(obukierunkowy);
        JLabel wys_podlogi_etykieta = new JLabel("Wysokosc podlogi");
        kontener.add(wys_podlogi_etykieta);
        JTextField wys_podlogi = new JTextField(Double.toString(t.wysokosc_podlogi));
        kontener.add(wys_podlogi);
        JLabel licz_kasownikow_etykieta = new JLabel("Liczba kasownikow");
        kontener.add(licz_kasownikow_etykieta);
        JTextField licz_kasownikow = new JTextField(Integer.toString(t.liczba_kasownikow));
        kontener.add(licz_kasownikow);
        JButton zapisz = new JButton("Zapisz");
        class MyListener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                t.szerokosc = Double.parseDouble(szerokosc.getText());
                t.dlugosc = Double.parseDouble(dlugosc.getText());
                t.liczba_pasazerow = Integer.parseInt(liczba_pas.getText());
                if(obukierunkowy.getText().equals("T"))t.obukierunkowy = true;
                else t.obukierunkowy = false;
                t.wysokosc_podlogi = Double.parseDouble(wys_podlogi.getText());
                t.liczba_kasownikow = Integer.parseInt(licz_kasownikow.getText());
                if(nowy_tramwaj){
                    obecnyStan.tramwaje_tab[obecnyStan.l_tramwajow]=t;
                    obecnyStan.l_tramwajow++;
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
