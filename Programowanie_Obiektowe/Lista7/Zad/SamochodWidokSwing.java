package com.company;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SamochodWidokSwing extends JComponent{

    public SamochodWidokSwing(Samochod s, ObecnyStan obecnyStan, boolean nowy_samochod){
        JFrame frame = new JFrame("Edycja samochodu");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container kontener = frame.getContentPane();
        GridLayout layout = new GridLayout(7, 2);
        kontener.setLayout(layout);
        JLabel liczba_pas_etykieta = new JLabel("Liczba pasazerow");
        kontener.add(liczba_pas_etykieta);
        JTextField liczba_pas = new JTextField(Integer.toString(s.liczba_pasazerow));
        kontener.add(liczba_pas);
        JLabel dlugosc_etykieta = new JLabel("Dlugosc");
        kontener.add(dlugosc_etykieta);
        JTextField dlugosc = new JTextField(Double.toString(s.dlugosc));
        kontener.add(dlugosc);
        JLabel szerokosc_etykieta = new JLabel("Szerokosc");
        kontener.add(szerokosc_etykieta);
        JTextField szerokosc = new JTextField(Double.toString(s.szerokosc));
        kontener.add(szerokosc);
        JLabel elektryczny_etykieta = new JLabel("Elektryczny (T/N)");
        kontener.add(elektryczny_etykieta);
        JTextField elektryczny;
        if(s.elektryczny)elektryczny = new JTextField("T");
        else elektryczny = new JTextField("N");
        kontener.add(elektryczny);
        JLabel rocznik_etykieta = new JLabel("Rocznik");
        kontener.add(rocznik_etykieta);
        JTextField rocznik = new JTextField(Integer.toString(s.rocznik));
        kontener.add(rocznik);
        JLabel marka_etykieta = new JLabel("Marka");
        kontener.add(marka_etykieta);
        JTextField marka = new JTextField(s.marka);
        kontener.add(marka);
        JButton zapisz = new JButton("Zapisz");
        class MyListener implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                s.szerokosc = Double.parseDouble(szerokosc.getText());
                s.dlugosc = Double.parseDouble(dlugosc.getText());
                s.liczba_pasazerow = Integer.parseInt(liczba_pas.getText());
                if(elektryczny.getText().equals("T"))s.elektryczny = true;
                else s.elektryczny = false;
                s.rocznik = Integer.parseInt(rocznik.getText());
                s.marka = marka.getText();
                if(nowy_samochod){
                    obecnyStan.samochody_tab[obecnyStan.l_samochodow]=s;
                    obecnyStan.l_samochodow++;
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
