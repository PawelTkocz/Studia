package com.company;

import java.io.*;

public class Pojazd {
    int liczba_pasazerow;
    double dlugosc;
    double szerokosc;

    public Pojazd(int l_pas, double dl, double szer){
        this.liczba_pasazerow=l_pas;
        this.dlugosc=dl;
        this.szerokosc=szer;
    }

    public String toString(){
        String pojazd = liczba_pasazerow + " osobowy pojazd o wymiarach " + dlugosc + " x " + szerokosc;
        return pojazd;
    }

    public void Edycja(ObecnyStan obecnyStan, boolean nowy_pojazd){
        PojazdWidokSwing edycja = new PojazdWidokSwing(this, obecnyStan, nowy_pojazd);
    }
}
