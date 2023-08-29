#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <time.h>

int liczba;
int zaczeto_gre=0;
clock_t start;
clock_t end;
int koniec_gry=0;
static GtkWidget *label1, *label2, *level, *window, *buttonNie, *buttonTak;
static GtkLevelBar *bar;

static int losuj_liczbe(){
    int a=rand()%100+1;
    return a;
}

static void zakoncz(){
    gtk_widget_hide(level);
    gtk_widget_hide(buttonNie);
    gtk_widget_hide(buttonTak);
    end = clock();
    int czas_gry=(int)(end-start)/CLOCKS_PER_SEC;
    char powiadomienie[30]="Twój czas gry to ";
    char czas[5];
    sprintf(czas, "%d", czas_gry);
    strcat(powiadomienie, czas);
    strcat(powiadomienie, " sekund");
    gtk_label_set_label (GTK_LABEL(label1), "Gratulacje, wygrałeś!");
    gtk_label_set_label (GTK_LABEL(label2), powiadomienie);
    koniec_gry=1;
}

static void dodaj_punkt(){
    int val=gtk_level_bar_get_value(bar);
    if(val!=9)gtk_level_bar_set_value(bar, val+1);
    else{
        zakoncz();
    }
}

static void odejmij_punkty(){
    int val=gtk_level_bar_get_value(bar);
    if(val<6)gtk_level_bar_set_value(bar, 0);
    else gtk_level_bar_set_value(bar, val-5);
}
static void sprawdz_odp(GtkButton *button){
    if(zaczeto_gre==0){
        zaczeto_gre=1;
        start = clock();
    }
    const char *odp=gtk_button_get_label(button);
    int odpowiedz=0;
    if(odp[0]=='T')odpowiedz=1;
    int czy_pierwsza=1;
    if(liczba==1)czy_pierwsza=0;
    for(int i=2; i*i<=liczba; i++)if(liczba%i==0)czy_pierwsza=0;
    if(czy_pierwsza==odpowiedz)dodaj_punkt();
    else odejmij_punkty();
    if(koniec_gry==0){
        liczba=losuj_liczbe();
        char t[4];
        sprintf(t, "%d", liczba);
        gtk_label_set_label (GTK_LABEL(label2), t);
    }
}
int main(int argc,char *argv[]){
    srand(time(NULL));
    gtk_init(&argc, &argv);
    window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"Gra liczby pierwsze");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 30);
    GtkWidget *grid =gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(window), grid);
    label1 =gtk_label_new_with_mnemonic ("Czy wyświetlona liczba jest pierwsza?");
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 4, 1);
    char l[4];
    liczba=losuj_liczbe();
    sprintf(l, "%d", liczba);
    label2 =gtk_label_new_with_mnemonic (l);
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 1, 4, 1);
    level= gtk_level_bar_new ();
    bar = GTK_LEVEL_BAR (level);
    gtk_level_bar_set_mode(bar, GTK_LEVEL_BAR_MODE_DISCRETE);
    gtk_level_bar_set_min_value (bar, 0);
    gtk_level_bar_set_max_value(bar, 10);
    gtk_grid_attach(GTK_GRID(grid), level, 0, 2, 4, 1);
    buttonNie =gtk_button_new_with_label("Nie");
    g_signal_connect(G_OBJECT(buttonNie),"clicked",G_CALLBACK(sprawdz_odp), (gpointer)buttonNie);
    gtk_grid_attach(GTK_GRID(grid), buttonNie, 0, 3, 2, 1);
    buttonTak =gtk_button_new_with_label("Tak");
    g_signal_connect(G_OBJECT(buttonTak),"clicked",G_CALLBACK(sprawdz_odp), (gpointer)buttonTak);
    gtk_grid_attach(GTK_GRID(grid), buttonTak, 2, 3, 2, 1);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
