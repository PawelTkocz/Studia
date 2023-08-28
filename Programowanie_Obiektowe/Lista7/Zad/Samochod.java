package com.company;

public class Samochod extends Pojazd{

    boolean elektryczny;
    int rocznik;
    String marka;


    public Samochod(int l_pas, double dl, double szer, boolean elektryczny, int rocznik, String marka) {
        super(l_pas, dl, szer);
        this.elektryczny=elektryczny;
        this.rocznik = rocznik;
        this.marka = marka;
    }

    public String toString(){
        String auto;
        if(elektryczny)auto = "Elektryczny ";
        else auto = "Spalinowy ";
        auto += "samochod marki " + marka + ", rocznik " + rocznik + "\n";
        auto += "Samochod ma wymiary " + dlugosc + " na " + szerokosc + " i ma " + liczba_pasazerow + " miejsc";
        return auto;
    }

    public void Edycja(ObecnyStan obecnyStan, boolean nowy_samochod){
        SamochodWidokSwing edycja = new SamochodWidokSwing(this, obecnyStan, nowy_samochod);
    }
}
