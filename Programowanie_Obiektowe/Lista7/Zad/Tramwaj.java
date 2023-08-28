package com.company;

public class Tramwaj extends Pojazd{
    boolean obukierunkowy;
    double wysokosc_podlogi;
    int liczba_kasownikow;


    public Tramwaj(int l_pas, double dl, double szer, boolean obukierunkowy, double wysokosc_podlogi, int liczba_kasownikow) {
        super(l_pas, dl, szer);
        this.obukierunkowy = obukierunkowy;
        this.wysokosc_podlogi = wysokosc_podlogi;
        this.liczba_kasownikow = liczba_kasownikow;
    }

    public String toString(){
        String tramwaj;
        if(obukierunkowy)tramwaj = "Obukierunkowy ";
        else tramwaj = "Jednokierunkowy ";
        tramwaj += "tramwaj dlugosci " + dlugosc + " i szerokosci " + szerokosc + "\n";
        tramwaj += "Moze przewiezc " + liczba_pasazerow + " pasazerow.\n";
        tramwaj += "Podloga znajduje sie na wyskosci " + wysokosc_podlogi + " centymetrow, a w srodku znajduje sie ";
        tramwaj += liczba_kasownikow + " kasownikow";
        return tramwaj;
    }

    public void Edycja(ObecnyStan obecnyStan, boolean nowy_tramwaj){
        TramwajWidokSwing edycja = new TramwajWidokSwing(this, obecnyStan, nowy_tramwaj);
    }
}
