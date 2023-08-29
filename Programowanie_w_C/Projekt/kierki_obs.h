#ifndef KIERKI_OBS_H
#define KIERKI_OBS_H
#include <gtk/gtk.h>

struct karta{
    int id;
    int kolor;//0-pik 1-trefl 2-karo 3-kier
    int wartosc;//2-14
    char obraz[30];
    char obraz2[30];
};

struct stan_gry{
    char nazwy_graczy[4][20];
    int czekaj;
    int szybkosc;
    int historia_gry[20][4];
    int rozegranych_rund;
    int punkty_runda[4];
    int punkty_suma[4];
    int kolej_gracza;
    int przekazywanie;
    int do_przekazania[13];
    int wybranych_kart;
    int karty_graczaA[13];
    int karty_graczaB[13];
    int karty_graczaC[13];
    int karty_graczaD[13];
    int *karty_graczy[4];
    int karty_na_stole[4];
    int kart_na_stole;
    int zagranych_lew;
    int blokada;
    int kolor;
    int rozdane_karty;
    int przekaz_komu;
    struct karta karty[52];
    GtkWidget *buttons[13];
    GtkWidget *przekaz_button;
    GtkWidget *rewersy_graczy[39];
    GtkWidget *stol_karty[4];
    GtkWidget *zebrane_pkt;
    GtkWidget *informacje;
    GtkWidget *gracze_punkty[4];
    GtkWidget *l_punktow[4];
    GtkWidget *do_zamkniecia;
    GtkWidget *wprowadz_imie;
    GtkStyleContext *context;
    GtkCssProvider *provider;
};

struct para{
    int a;
    struct stan_gry *b;
};

void inicjalizuj_stan_gry(struct stan_gry *st_gry);
int koniec_gry(int punkty_suma[4]);
int punktuj_lewe(int karty_na_stole[4], int *punkty, int kolor, struct stan_gry *st_gry);
void ustaw_karty(int *reka);
void rozdaj_karty(int *karty_graczaA, int *karty_graczaB, int *karty_graczaC, int *karty_graczaD);
int kto_zaczyna(int *karty_graczaA, int *karty_graczaB, int *karty_graczaC, int *karty_graczaD);
int wybierz_karte(int *karty_gracza, int kolor, int pierw, int karty_na_stole[4], struct stan_gry *st_gry);
int losuj_przeciwnika();
void zamiana_kart(int *karty_gracza1, int *karty_gracza2, int do_przekazania[13], int *otrzymane_karty, struct stan_gry *st_gry);
void uloz_podium(int *miejsca_graczy, int suma_punktow[4]);

#endif
