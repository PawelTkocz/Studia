package com.company;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ObecnyStan extends JComponent {
    final int MaxLength = 10;
    Pojazd[] pojazdy_tab;
    int l_pojazdow;
    Samochod[] samochody_tab;
    int l_samochodow;
    Tramwaj[] tramwaje_tab;
    int l_tramwajow;
    JFrame frame_do_zamkniecia;

    public ObecnyStan(){
        this.pojazdy_tab=new Pojazd[MaxLength];
        this.samochody_tab = new Samochod[MaxLength];
        this.tramwaje_tab = new Tramwaj[MaxLength];
    }

    public void WyswietlObecnyStan(){
        ObecnyStan this_obecny_stan = this;
        JFrame frame = new JFrame("Edycja pojazdow");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container kontener = frame.getContentPane();
        GridLayout layout = new GridLayout(2+MaxLength, 3);
        kontener.setLayout(layout);
        JLabel pojazdy_etykieta = new JLabel("Pojazdy");
        kontener.add(pojazdy_etykieta);
        JLabel samochody_etykieta = new JLabel("Samochody");
        kontener.add(samochody_etykieta);
        JLabel tramwaje_etykieta = new JLabel("Tramwaje");
        kontener.add(tramwaje_etykieta);
        JButton dodaj_pojazd = new JButton("Dodaj pojazd");
        class MyListenerPojazd implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                Pojazd nowy_pojazd = new Pojazd(0, 0, 0);
                frame_do_zamkniecia = frame;
                nowy_pojazd.Edycja(this_obecny_stan, true);
            }
        }
        dodaj_pojazd.addActionListener(new MyListenerPojazd());
        kontener.add(dodaj_pojazd);
        JButton dodaj_samochod = new JButton("Dodaj samochod");
        class MyListenerSamochod implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                Samochod nowy_samochod = new Samochod(0, 0, 0, false, 0, "");
                frame_do_zamkniecia = frame;
                nowy_samochod.Edycja(this_obecny_stan, true);
            }
        }
        dodaj_samochod.addActionListener(new MyListenerSamochod());
        kontener.add(dodaj_samochod);
        JButton dodaj_tramwaj = new JButton("Dodaj tramwaj");
        class MyListenerTramwaj implements ActionListener
        {
            public void actionPerformed(ActionEvent e) {
                Tramwaj nowy_tramwaj = new Tramwaj(0, 0, 0, false, 0, 0);
                frame_do_zamkniecia = frame;
                nowy_tramwaj.Edycja(this_obecny_stan, true);
            }
        }
        dodaj_tramwaj.addActionListener(new MyListenerTramwaj());
        kontener.add(dodaj_tramwaj);
        String[] typy = new String[]{"pojazd", "samochod", "tramwaj"};
        int[] ilosc = new int[]{l_pojazdow, l_samochodow, l_tramwajow};
        for(int i=0; i<3*MaxLength; i++){
            int rodzaj = i%3;
            int indeks = i/3;
            if(indeks<ilosc[rodzaj]){
                String text = "Edytuj " + typy[rodzaj] + " nr " + Integer.toString(indeks+1);
                JButton edytuj = new JButton(text);
                class MyListener implements ActionListener
                {
                    public void actionPerformed(ActionEvent e) {
                        frame_do_zamkniecia = frame;
                        if(rodzaj==0)pojazdy_tab[indeks].Edycja(this_obecny_stan, false);
                        else if(rodzaj==1)samochody_tab[indeks].Edycja(this_obecny_stan, false);
                        else tramwaje_tab[indeks].Edycja(this_obecny_stan, false);
                    }
                }
                edytuj.addActionListener(new MyListener());
                kontener.add(edytuj);
            }
            else{
                JLabel pusty = new JLabel("");
                kontener.add(pusty);
            }
        }

        frame.pack();
        frame.setVisible(true);
    }
}
