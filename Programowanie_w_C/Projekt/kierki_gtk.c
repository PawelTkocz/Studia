#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include "kierki_obs.h"
#include "kierki_gtk.h"

void rozpocznij_gre(struct stan_gry *st_gry){
    //funckja wywolywana tylko raz, przy uruchomieniu gry
    //korzystajac z GTK tworzy graficzna czesc gry
    nowa_runda(NULL, st_gry);
    GtkSettings *default_settings = gtk_settings_get_default();
    g_object_set(default_settings, "gtk-button-images", TRUE, NULL);
    GtkCssProvider *provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path (provider, "kierki.css", NULL);
    GtkStyleContext *context=NULL;
    st_gry->provider=provider;
    st_gry->context=context;
    //poniezej tworze potrzebne widgety typu box i grid
    GtkWidget *window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
    context = gtk_widget_get_style_context (window);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_fullscreen(GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window),"Kierki");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 2);
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    GtkWidget *reka=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *glowny=gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(glowny), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(glowny), TRUE);
    GtkWidget *srodek = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *gora = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(gora), TRUE);
    GtkWidget *dol = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(dol), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(dol), TRUE);
    GtkWidget *lewy_gracz = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_set_homogeneous(GTK_BOX(lewy_gracz), 0);
    GtkWidget *prawy_gracz = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *punktacja = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_set_border_width(GTK_CONTAINER(punktacja), 8);
    context = gtk_widget_get_style_context (punktacja);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context,"okienka");
    //tworzenie punktacji znajdujacej sie w prawym gornym rodu
    GtkWidget *tytul_punktacji = gtk_label_new_with_mnemonic ("Punktacja generalna");
    GtkWidget *punkty = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(punkty), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(punkty), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(punkty), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(punkty), TRUE);
    gtk_box_pack_start(GTK_BOX(punktacja), tytul_punktacji, TRUE, TRUE, 0);
    for(int i=0; i<4; i++){
        GtkWidget *gracz=gtk_label_new_with_mnemonic (st_gry->nazwy_graczy[i]);
        st_gry->gracze_punkty[i]=gracz;
        GtkWidget *pkt=gtk_label_new_with_mnemonic ("0");
        st_gry->l_punktow[i]=pkt;
        gtk_grid_attach(GTK_GRID(punkty), gracz, i, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(punkty), pkt, i, 1, 1, 1);
    }
    gtk_box_pack_start(GTK_BOX(punktacja), punkty, TRUE, TRUE, 0);
    gtk_grid_attach(GTK_GRID(gora), punktacja, 0, 0, 3, 1);
    //tworzenie talii rewersow gracza znajdujacego sie na gorze stolu
    GtkWidget *reka_gora = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_homogeneous(GTK_BOX(reka_gora), 0);
    for(int i=0; i<12; i++){
        GtkWidget *image = gtk_image_new_from_file ("karty/rewers2.png");
        gtk_box_pack_start(GTK_BOX(reka_gora), image, FALSE, FALSE, 0);
        st_gry->rewersy_graczy[13+i]=image;
    }
    GtkWidget *image = gtk_image_new_from_file ("karty/rewers.png");
    gtk_box_pack_start(GTK_BOX(reka_gora), image, FALSE, FALSE, 0);
    st_gry->rewersy_graczy[25]=image;
    gtk_grid_attach(GTK_GRID(gora), reka_gora, 3, 0, 4, 1);
    GtkWidget *prawa_gora = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(prawa_gora), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(prawa_gora), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(prawa_gora), 3);
    gtk_grid_set_column_homogeneous(GTK_GRID(prawa_gora), TRUE);
    //tworzenie okienka informacyjnego
    GtkWidget *informacje = gtk_label_new_with_mnemonic ("Podaj swoje imię\naby rozpocząć grę");
    st_gry->informacje=informacje;
    context = gtk_widget_get_style_context (informacje);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_grid_attach(GTK_GRID(prawa_gora), informacje, 0, 1, 6, 4);
    //tworzenie przycisku do zakonczenia gry
    GtkWidget *zakoncz = gtk_button_new_with_label("zakończ grę");
    context = gtk_widget_get_style_context (zakoncz);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context,"zakoncz");
    g_signal_connect(G_OBJECT(zakoncz),"clicked",G_CALLBACK(gtk_main_quit),NULL);
    gtk_grid_attach(GTK_GRID(prawa_gora), zakoncz, 4, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(gora), prawa_gora, 7, 0, 3, 1);
    GtkWidget *stol=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    //tworzenie stolu, miejsca w ktorym beda sie pojawialy karty zagrywane przez graczy
    //oraz przycisk strzalki do zamiany kart
    GtkWidget *k1 = gtk_image_new_from_file ("karty/puste.png");
    gtk_box_pack_start(GTK_BOX(stol), k1, TRUE, TRUE, 0);
    GtkWidget *pion_karty=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *k2 = gtk_image_new_from_file ("karty/puste.png");
    gtk_box_pack_start(GTK_BOX(pion_karty), k2, TRUE, TRUE, 0);
    GtkWidget *przekaz_button = gtk_button_new_with_label("");
    g_signal_connect(G_OBJECT(przekaz_button), "clicked",G_CALLBACK(przekaz_karty), st_gry);
    GtkWidget *img=gtk_image_new_from_file("karty/strzalka2.png");
    gtk_button_set_image(GTK_BUTTON(przekaz_button),(GtkWidget *)img);
    st_gry->przekaz_button=przekaz_button;
    context = gtk_widget_get_style_context (przekaz_button);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_box_pack_start(GTK_BOX(pion_karty), przekaz_button, FALSE, FALSE, 0);
    GtkWidget *k4 = gtk_image_new_from_file ("karty/puste.png");
    gtk_box_pack_start(GTK_BOX(pion_karty), k4, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(stol), pion_karty, TRUE, FALSE, 0);
    GtkWidget *k3 = gtk_image_new_from_file ("karty/puste.png");
    st_gry->stol_karty[0]=k4;
    st_gry->stol_karty[1]=k1;
    st_gry->stol_karty[2]=k2;
    st_gry->stol_karty[3]=k3;
    gtk_box_pack_start(GTK_BOX(stol), k3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(srodek), stol, TRUE, TRUE, 0);
    //tworzenie talii rewersow kart gracza po lewej stronie
    for(int i=0; i<12; i++){
        GtkWidget *image = gtk_image_new_from_file ("karty/rewers3.png");
        gtk_box_pack_start(GTK_BOX(lewy_gracz), image, FALSE, TRUE, 0);
        st_gry->rewersy_graczy[i]=image;
    }
    GtkWidget *image2 = gtk_image_new_from_file ("karty/rewers4.png");
    gtk_box_pack_start(GTK_BOX(lewy_gracz), image2, FALSE, TRUE, 0);
    st_gry->rewersy_graczy[12]=image2;
    GtkWidget *lewa = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(lewa), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(lewa), TRUE);
    gtk_grid_attach(GTK_GRID(lewa), lewy_gracz, 0, 0, 1, 20);
    //tworzenie informacji o punktach zdobytch w obecnie trwajacej rundzie
    //znajdujacego sie w lewym dolnym rogu
    GtkWidget *zebrane_pkt = gtk_label_new_with_mnemonic ("Zebrane punkty: 0");
    st_gry->zebrane_pkt=zebrane_pkt;
    context = gtk_widget_get_style_context (zebrane_pkt);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context,"okienka");
    gtk_grid_attach(GTK_GRID(lewa), zebrane_pkt, 0, 20, 1, 1);
    //tworzenie talli rewersow kart gracza po prawej stronie
    for(int i=0; i<12; i++){
        GtkWidget *image = gtk_image_new_from_file ("karty/rewers3.png");
        gtk_box_pack_start(GTK_BOX(prawy_gracz), image, FALSE, TRUE, 0);
        st_gry->rewersy_graczy[26+i]=image;
    }
    GtkWidget *image3 = gtk_image_new_from_file ("karty/rewers4.png");
    gtk_box_pack_start(GTK_BOX(prawy_gracz), image3, FALSE, TRUE, 0);
    st_gry->rewersy_graczy[38]=image3;
    //tworzenie trzynastu przyciskow, reprezentujacych karty na rece uzytkownika
    for(int i=0; i<13; i++){
        GtkWidget *button = gtk_button_new_with_label("");
        struct para *p=malloc(sizeof(struct para));
        p->a=i;
        p->b=st_gry;
        g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(zagraj_karte), p);
        img=gtk_image_new_from_file(st_gry->karty[st_gry->karty_graczaA[i]].obraz);
        gtk_button_set_image(GTK_BUTTON(button),(GtkWidget *)img);
        gtk_box_pack_start(GTK_BOX(reka), button, FALSE, FALSE, 0);
        st_gry->buttons[i]=button;
    }
    //skladnanie calosci
    gtk_grid_attach(GTK_GRID(glowny), srodek, 0, 0, 1, 4);
    gtk_grid_attach(GTK_GRID(glowny), reka, 0, 4, 1, 2);
    gtk_grid_attach(GTK_GRID(dol), lewa, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(dol), glowny, 1, 0, 7, 1);
    gtk_grid_attach(GTK_GRID(dol), prawy_gracz, 8, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gora, 0, 0, 1, 3);
    gtk_grid_attach(GTK_GRID(grid), dol, 0, 3, 1, 9);
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
    ukryj_karty(st_gry);
    //ukrycie kart w celu przygotowania do wyswietlenia animacji rozdawania
    popros_o_imie(st_gry);
    //oraz wyswietlenie okienka z prosba o podanie imienia
}

void wyswietl_info(struct stan_gry *st_gry, int id){
    //funkcja modyfikuje informacje wyswietlanie w okienku informacyjnym
    //w prawym gornym rogu ekrany
    if(id==0){
        gtk_label_set_label(GTK_LABEL(st_gry->informacje), "");
    }
    if(id==1){
        gtk_label_set_label(GTK_LABEL(st_gry->informacje), "Wybierz trzy karty do przekazania\nNastępnie naciśnij strzałkę");
    }
    if(id==2){
        gtk_label_set_label(GTK_LABEL(st_gry->informacje), "Nie możesz zagrać tej karty\nZagraj kartę odpowiedniego koloru");
    }
    if(id==3){
        gtk_label_set_label(GTK_LABEL(st_gry->informacje), "Zaczynasz!\nZagraj dwójkę trefl");
    }
    if(id==4){
        gtk_label_set_label(GTK_LABEL(st_gry->informacje), "Podaj swoje imię\naby rozpocząć grę");
    }
}

void potwierdz_imie(GtkWidget *widget, struct stan_gry *st_gry){
    //funkcja zajmujaca sie wpisaniem podanego przez uzytkownika imienia do stanu gry
    (void)widget;
    const gchar *imie;
    imie=gtk_entry_get_text(GTK_ENTRY(st_gry->wprowadz_imie));
    gint dl=gtk_entry_get_text_length(GTK_ENTRY(st_gry->wprowadz_imie));
    if(dl>0){
        strcpy(st_gry->nazwy_graczy[0], imie);
        GtkWidget *label=st_gry->gracze_punkty[0];
        gtk_label_set_label(GTK_LABEL(label), imie);
    }
    gtk_widget_destroy(st_gry->do_zamkniecia);
    st_gry->do_zamkniecia=NULL;
    wyswietl_info(st_gry, 1);
    gtk_widget_show(GTK_WIDGET(st_gry->przekaz_button));
}

void popros_o_imie(struct stan_gry *st_gry){
    //funkcja tworzy okienko z prosba o podanie swojego imienia
    GtkStyleContext *context=st_gry->context;
    GtkCssProvider *provider=st_gry->provider;
    GtkWidget *okienko_imie = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(okienko_imie), FALSE);
    context = gtk_widget_get_style_context (okienko_imie);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context,"okienka");
    gtk_window_set_position(GTK_WINDOW(okienko_imie),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(okienko_imie), 30);
    GtkWidget *box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *tytul=gtk_label_new_with_mnemonic("Wprowadź swoje imię:\n");
    GtkWidget *wprowadz_imie=gtk_entry_new();
    gtk_entry_set_alignment (GTK_ENTRY(wprowadz_imie), 0.5);
    gtk_entry_set_max_length(GTK_ENTRY(wprowadz_imie), 7);
    st_gry->wprowadz_imie=wprowadz_imie;
    GtkWidget *zatwierdz = gtk_button_new_with_label("Zatwierdz");
    st_gry->do_zamkniecia=okienko_imie;
    g_signal_connect(G_OBJECT(zatwierdz), "clicked",G_CALLBACK(potwierdz_imie), st_gry);
    context = gtk_widget_get_style_context (zatwierdz);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context,"wybor");
    gtk_box_pack_start(GTK_BOX(box), tytul, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), wprowadz_imie, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), zatwierdz, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(okienko_imie), box);
    wyswietl_info(st_gry, 4);
    gtk_widget_show_all(okienko_imie);
}

void ukryj_karty(struct stan_gry *st_gry){
    //funckja ukrywa rewersy kart wszystkich graczy
    for(int i=0; i<39; i++){
        GtkWidget *im=st_gry->rewersy_graczy[i];
        gtk_widget_hide(GTK_WIDGET(im));
    }
    //oraz reke uzytkownika i przycisk do przekazywania kart
    for(int i=0; i<13; i++){
        gtk_widget_hide(GTK_WIDGET(st_gry->buttons[i]));
    }
    gtk_widget_hide(st_gry->przekaz_button);
}

gboolean animacja_rozdawania(struct stan_gry *st_gry){
    struct karta *karty=st_gry->karty;
    int rozdane_karty=st_gry->rozdane_karty;
    if(rozdane_karty<39){
        GtkWidget *im=st_gry->rewersy_graczy[38-rozdane_karty];
        gtk_widget_show(GTK_WIDGET(im));
    }
    else if(rozdane_karty<52){
        GtkWidget *img=gtk_image_new_from_file(karty[st_gry->karty_graczaA[rozdane_karty-39]].obraz);
        gtk_button_set_image(GTK_BUTTON(st_gry->buttons[rozdane_karty-39]),(GtkWidget *)img);
        gtk_widget_show(GTK_WIDGET(st_gry->buttons[rozdane_karty-39]));
    }
    st_gry->rozdane_karty++;
    rozdane_karty++;
    if(rozdane_karty<52)return TRUE;
    else{
        gtk_widget_hide(GTK_WIDGET(st_gry->stol_karty[0]));
        char przekaz_nazwa[25]="karty/strzalka";
        char numer[2];
        sprintf(numer, "%d", st_gry->przekaz_komu);
        strcat(przekaz_nazwa, numer);
        strcat(przekaz_nazwa, ".png");
        GtkWidget *img=gtk_image_new_from_file(przekaz_nazwa);
        gtk_button_set_image(GTK_BUTTON(st_gry->przekaz_button),(GtkWidget *)img);
        if(st_gry->rozegranych_rund>0){
            gtk_widget_show(st_gry->przekaz_button);
            wyswietl_info(st_gry, 1);
        }
        return FALSE;
    }
}

void ustaw_zebrane_pkt(struct stan_gry *st_gry){
    //funkcja aktualizuje punktacje generalna
    //oraz informacje o punktach zebranych w aktualnej rundzie
    char wiad[20]="Zebrane punkty: 0";
    gtk_label_set_text(GTK_LABEL(st_gry->zebrane_pkt), wiad);
    for(int i=0; i<4; i++){
        sprintf(wiad, "%d", st_gry->punkty_suma[i]);
        gtk_label_set_text(GTK_LABEL(st_gry->l_punktow[i]), wiad);
    }
}

void nowa_runda(GtkWidget *widget, struct stan_gry *st_gry){
    //funkcja modyfikuje stan_gry, ustawiajac odpowiednie parametry do stanu domyslnego
    //w celu rozpoczecia nowej rundy
    (void)widget;
    if(st_gry->do_zamkniecia!=NULL){
        gtk_widget_destroy(st_gry->do_zamkniecia);
        st_gry->do_zamkniecia=NULL;
    }
    rozdaj_karty(st_gry->karty_graczaA, st_gry->karty_graczaB, st_gry->karty_graczaC, st_gry->karty_graczaD);
    st_gry->przekazywanie=1;
    st_gry->rozdane_karty=0;
    for(int i=0; i<4; i++){
        st_gry->punkty_runda[i]=0;
        st_gry->karty_na_stole[i]=-1;
    }
    if(st_gry->rozegranych_rund>0){
        ustaw_zebrane_pkt(st_gry);
        st_gry->przekaz_komu=losuj_przeciwnika();
    }
    //wywolanie animacji rozdawania
    g_timeout_add(20, G_SOURCE_FUNC(animacja_rozdawania), (gpointer)st_gry);
}

void nowa_gra(GtkWidget *widget, struct stan_gry *st_gry){
    //funckja ustawia stan gry na domyslna wartosc
    //i rozpoczyna kolejna gre
    (void)widget;
    gtk_widget_destroy(st_gry->do_zamkniecia);
    st_gry->do_zamkniecia=NULL;
    inicjalizuj_stan_gry(st_gry);
    ustaw_zebrane_pkt(st_gry);
    nowa_runda(NULL, st_gry);
    popros_o_imie(st_gry);
}

void wyswietl_punktacje(GtkWidget *widget, struct stan_gry *st_gry){
    //funckja tworzy okienko z punktacja widoczna na koniec kazdej rundy
    (void)widget;
    GtkStyleContext *context=st_gry->context;
    GtkCssProvider *provider=st_gry->provider;
    int zakoncz=0;
    if(st_gry->do_zamkniecia!=NULL){
        gtk_widget_destroy(st_gry->do_zamkniecia);
        st_gry->do_zamkniecia=NULL;
        zakoncz=1;
    }
    GtkWidget *punktacja_szczegolowa = gtk_window_new(GTK_WINDOW_POPUP);
    context = gtk_widget_get_style_context (punktacja_szczegolowa);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context,"okienka");
    gtk_window_set_position(GTK_WINDOW(punktacja_szczegolowa),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(punktacja_szczegolowa), 30);
    GtkWidget *punkty_szczegol = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(punkty_szczegol), 5);
    gtk_grid_set_row_homogeneous(GTK_GRID(punkty_szczegol), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(punkty_szczegol), 15);
    gtk_grid_set_column_homogeneous(GTK_GRID(punkty_szczegol), TRUE);
    for(int i=0; i<4; i++){
        GtkWidget *gracz=gtk_label_new_with_mnemonic (st_gry->nazwy_graczy[i]);
        gtk_grid_attach(GTK_GRID(punkty_szczegol), gracz, i, 0, 1, 1);
    }
    for(int i=0; i<st_gry->rozegranych_rund; i++){
        for(int j=0; j<4; j++){
            char l_pkt[4];
            sprintf(l_pkt, "%d", st_gry->historia_gry[i][j]);
            GtkWidget *pkt=gtk_label_new_with_mnemonic (l_pkt);
            gtk_grid_attach(GTK_GRID(punkty_szczegol), pkt, j, i+1, 1, 1);
        }
    }
    GtkWidget *zakoncz_pkt = gtk_button_new_with_label("Zakończ grę");
    context = gtk_widget_get_style_context (zakoncz_pkt);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context,"wybor");
    g_signal_connect(G_OBJECT(zakoncz_pkt), "clicked",G_CALLBACK(gtk_main_quit), NULL);
    gtk_grid_attach(GTK_GRID(punkty_szczegol), zakoncz_pkt, 0, st_gry->rozegranych_rund+1, 2, 1);
    //jesli funkcja zostala wywolana na koniec gry, tworzy przycisk z mozliwoscia rozpoczecia nowej gry
    if(zakoncz==0){
        GtkWidget *nast_runda = gtk_button_new_with_label("Rozpocznij nastepną rundę");
        g_signal_connect(G_OBJECT(nast_runda), "clicked",G_CALLBACK(nowa_runda), st_gry);
        gtk_grid_attach(GTK_GRID(punkty_szczegol), nast_runda, 2, st_gry->rozegranych_rund+1, 2, 1);
        context = gtk_widget_get_style_context (nast_runda);
        gtk_style_context_add_class(context,"wybor");
        gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    else{
        GtkWidget *nowa_gra = gtk_button_new_with_label("Rozpocznij nową grę");
        g_signal_connect(G_OBJECT(nowa_gra), "clicked",G_CALLBACK(nowa_gra), st_gry);
        gtk_grid_attach(GTK_GRID(punkty_szczegol), nowa_gra, 2, st_gry->rozegranych_rund+1, 2, 1);
        context = gtk_widget_get_style_context (nowa_gra);
        gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
        gtk_style_context_add_class(context,"wybor");
    }
    st_gry->do_zamkniecia=punktacja_szczegolowa;
    gtk_container_add(GTK_CONTAINER(punktacja_szczegolowa), punkty_szczegol);
    gtk_widget_show_all(punktacja_szczegolowa);
}

void wyswietl_zakonczenie(struct stan_gry *st_gry){
    //funkcja wyswietla okienko zawierajae podsumowanie gry
    //w postaci podium i liczby punktow zdobytej przez kazdego z graczy
    GtkStyleContext *context=st_gry->context;
    GtkCssProvider *provider=st_gry->provider;
    GtkWidget *zakonczenie = gtk_window_new(GTK_WINDOW_POPUP);
    context = gtk_widget_get_style_context (zakonczenie);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context,"okienka");
    gtk_window_set_position(GTK_WINDOW(zakonczenie),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(zakonczenie), 30);
    GtkWidget *miejsca = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(miejsca), 5);
    gtk_grid_set_row_homogeneous(GTK_GRID(miejsca), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(miejsca), 15);
    gtk_grid_set_column_homogeneous(GTK_GRID(miejsca), TRUE);
    GtkWidget *tytul=gtk_label_new_with_mnemonic ("Wyniki gry");
    gtk_grid_attach(GTK_GRID(miejsca), tytul, 0, 0, 2, 1);
    int miejsca_graczy[4];
    uloz_podium(miejsca_graczy, st_gry->punkty_suma);
    for(int i=0; i<4; i++){
        char pozycja[40];
        sprintf(pozycja, "%d", i+1);
        strcat(pozycja, ". ");
        strcat(pozycja, st_gry->nazwy_graczy[miejsca_graczy[i]]);
        GtkWidget *poz=gtk_label_new_with_mnemonic (pozycja);
        gtk_label_set_xalign(GTK_LABEL(poz), 0);
        gtk_grid_attach(GTK_GRID(miejsca), poz, 0, 1+i, 1, 1);
        char liczba_punktow[20];
        sprintf(liczba_punktow, "%d", st_gry->punkty_suma[i]);
        strcat(liczba_punktow, " punktow");
        GtkWidget *pk=gtk_label_new_with_mnemonic (liczba_punktow);
        gtk_grid_attach(GTK_GRID(miejsca), pk, 1, 1+i, 1, 1);
    }
    GtkWidget *zakoncz_pkt = gtk_button_new_with_label("Zakończ grę");
    g_signal_connect(G_OBJECT(zakoncz_pkt), "clicked",G_CALLBACK(gtk_main_quit), NULL);
    context = gtk_widget_get_style_context (zakoncz_pkt);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context,"wybor");
    GtkWidget *szcz_pkt = gtk_button_new_with_label("Zobacz szczegółową punktację");
    g_signal_connect(G_OBJECT(szcz_pkt), "clicked",G_CALLBACK(wyswietl_punktacje), st_gry);
    context = gtk_widget_get_style_context (szcz_pkt);
    gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context,"wybor");
    st_gry->do_zamkniecia=zakonczenie;
    gtk_grid_attach(GTK_GRID(miejsca), zakoncz_pkt, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(miejsca), szcz_pkt, 1, 5, 1, 1);
    gtk_container_add(GTK_CONTAINER(zakonczenie), miejsca);
    gtk_widget_show_all(zakonczenie);
}

gboolean zbierz_karty(struct stan_gry *st_gry){
    //funkcja wywolywana, gdy na stole znajduja sie cztery karty
    //decyduje ktory z graczy je zbiera i przydziela mu karne punkty
    if(st_gry->czekaj==0)return FALSE;
    st_gry->zagranych_lew++;
    st_gry->kolej_gracza=punktuj_lewe(st_gry->karty_na_stole, st_gry->punkty_runda, st_gry->kolor, st_gry);
    for(int i=0; i<4; i++){
        gtk_image_set_from_file ((GtkImage *)st_gry->stol_karty[i], "karty/puste.png");
    }
    st_gry->kolor=-1;
    char wiad[20]="Zebrane punkty: ";
    char pkt[3];
    sprintf(pkt, "%d", st_gry->punkty_runda[0]);
    strcat(wiad, pkt);
    gtk_label_set_text(GTK_LABEL(st_gry->zebrane_pkt), wiad);
    st_gry->kart_na_stole=0;
    st_gry->czekaj=0;
    for(int i=0; i<4; i++)st_gry->karty_na_stole[i]=-1;
    if(st_gry->zagranych_lew==13){
        for(int i=0; i<4; i++){
            st_gry->punkty_suma[i]+=st_gry->punkty_runda[i];
            st_gry->historia_gry[st_gry->rozegranych_rund][i]=st_gry->punkty_suma[i];
        }
        st_gry->zagranych_lew=0;
        st_gry->rozegranych_rund++;
        if(koniec_gry(st_gry->punkty_suma))wyswietl_zakonczenie(st_gry);
        else wyswietl_punktacje(NULL, st_gry);
    }
    else g_timeout_add(st_gry->szybkosc, G_SOURCE_FUNC(wyloz_karte), st_gry);
    return FALSE;
}

gboolean wyloz_karte(struct stan_gry *st_gry){
    //funkcja wyklada na stol karte wybrana przez gracza
    if(st_gry->kart_na_stole==4){
        if(st_gry->czekaj==0){
            g_timeout_add(st_gry->szybkosc*2.4+1, G_SOURCE_FUNC(zbierz_karty), st_gry);
            st_gry->czekaj=1;
        }
        return FALSE;
    }
    else if(st_gry->kolej_gracza==0){
        st_gry->blokada=0;
        return FALSE;
    }
    else{
        int id_karty;
        if(st_gry->kart_na_stole==0 && st_gry->zagranych_lew==0){
                id_karty=wybierz_karte(st_gry->karty_graczy[st_gry->kolej_gracza], st_gry->kolor, 1, st_gry->karty_na_stole, st_gry);
        }
        else id_karty=wybierz_karte(st_gry->karty_graczy[st_gry->kolej_gracza], st_gry->kolor, 0, st_gry->karty_na_stole, st_gry);
        if(st_gry->kart_na_stole==0)st_gry->kolor=st_gry->karty[id_karty].kolor;
        gtk_image_set_from_file ((GtkImage *)st_gry->stol_karty[st_gry->kolej_gracza], st_gry->karty[id_karty].obraz);
        st_gry->karty_na_stole[st_gry->kolej_gracza]=id_karty;
        GtkWidget *im=st_gry->rewersy_graczy[(st_gry->kolej_gracza-1)*13+st_gry->zagranych_lew];
        gtk_widget_hide(GTK_WIDGET(im));
        st_gry->kart_na_stole++;
        st_gry->kolej_gracza=(st_gry->kolej_gracza+1)%4;
        return TRUE;
    }
    return FALSE;
}

gboolean zobacz_karty(struct stan_gry *st_gry){
    //funkcja majaca na celu danie uzytkownikowi mozliwosci obejrzenia kart
    //ktore otrzymal w procesie zamiany na poczatek rundy
    for(int i=0; i<13; i++){
        GtkWidget *img=gtk_image_new_from_file(st_gry->karty[st_gry->karty_graczaA[i]].obraz);
        gtk_button_set_image(GTK_BUTTON(st_gry->buttons[i]),(GtkWidget *)img);
    }
    g_timeout_add(st_gry->szybkosc, G_SOURCE_FUNC(wyloz_karte), st_gry);
    return FALSE;
}

void przekaz_karty(GtkButton *button, struct stan_gry *st_gry){
    //funckja wywolywana w momencie klikniecia przez gracza przycisku strzalki do przekazywania kart
    //jesli wykonanie tej akcji jest dozwolone w danej chwili, fukcja wyswietli graczowi
    //zaaktualizowana reke
    if(st_gry->wybranych_kart!=3)return;
    int otrzymane_karty[3];
    zamiana_kart(st_gry->karty_graczaA, st_gry->karty_graczy[st_gry->przekaz_komu], st_gry->do_przekazania, otrzymane_karty, st_gry);
    st_gry->kolej_gracza=kto_zaczyna(st_gry->karty_graczaA, st_gry->karty_graczaB, st_gry->karty_graczaC, st_gry->karty_graczaD);
    if(st_gry->kolej_gracza==0)wyswietl_info(st_gry,3);
    else wyswietl_info(st_gry, 0);
    for(int i=0; i<13; i++){
        int w=st_gry->karty_graczaA[i];
        GtkWidget *img;
        if(w==otrzymane_karty[0] || w==otrzymane_karty[1] || w==otrzymane_karty[2]){
            img=gtk_image_new_from_file(st_gry->karty[st_gry->karty_graczaA[i]].obraz2);
        }
        else img=gtk_image_new_from_file(st_gry->karty[st_gry->karty_graczaA[i]].obraz);
        gtk_button_set_image(GTK_BUTTON(st_gry->buttons[i]),(GtkWidget *)img);
    }
    st_gry->przekazywanie=0;
    gtk_widget_hide(GTK_WIDGET(button));
    gtk_widget_show(st_gry->stol_karty[0]);
    for(int i=0; i<13; i++)st_gry->do_przekazania[i]=0;
    st_gry->wybranych_kart=0;
    g_timeout_add(8*st_gry->szybkosc, G_SOURCE_FUNC(zobacz_karty), st_gry);
}

void zagraj_karte(GtkButton *button, struct para *p){
    //funkcja wywolywana, gdy gracz kliknie na ktoras z kart na swojej rece
    //zarowno w fazie przekazywania kart
    //jak i w trakcie rozgrywki, w celu wylozenia karty
    int i=p->a;
    struct stan_gry *st_gry=p->b;
    if(st_gry->przekazywanie==1){
        //jesli nadal trwa faza przekazywania kart
        if(st_gry->do_przekazania[i]==1){
            st_gry->do_przekazania[i]=0;
            st_gry->wybranych_kart--;
            GtkWidget *img=gtk_image_new_from_file(st_gry->karty[st_gry->karty_graczaA[i]].obraz);
            gtk_button_set_image(GTK_BUTTON(button),(GtkWidget *)img);
        }
        else if(st_gry->wybranych_kart<3){
            st_gry->do_przekazania[i]=1;
            st_gry->wybranych_kart++;
            GtkWidget *img=gtk_image_new_from_file(st_gry->karty[st_gry->karty_graczaA[i]].obraz2);
            gtk_button_set_image(GTK_BUTTON(button),(GtkWidget *)img);
        }
        else return;
    }
    else{
        //jesli trwa wlasciwa faza rozgrywki
        if(st_gry->kolej_gracza!=0 || st_gry->blokada==1)return;
        if(st_gry->kart_na_stole==0 && st_gry->zagranych_lew==0){
            if(st_gry->karty_graczaA[i]!=0)return;
        }
        if(st_gry->kart_na_stole>0){
            int czy_ma_kolor;
            for(int i=0; i<13; i++){
                 if(st_gry->karty_graczaA[i]!=-1 && st_gry->karty[st_gry->karty_graczaA[i]].kolor==st_gry->kolor)czy_ma_kolor=1;
            }
            if(st_gry->karty[st_gry->karty_graczaA[i]].kolor!=st_gry->kolor && czy_ma_kolor==1){
                wyswietl_info(st_gry, 2);
                return;
            }
        }
        else st_gry->kolor=st_gry->karty[st_gry->karty_graczaA[i]].kolor;
        //jesli zagranie wybranej przez gracza karty jest dozwolone
        //funkcja wyswietli wybrana karte na stole
        gtk_image_set_from_file ((GtkImage *)st_gry->stol_karty[0], st_gry->karty[st_gry->karty_graczaA[i]].obraz);
        gtk_widget_hide(GTK_WIDGET(button));
        st_gry->karty_na_stole[0]=st_gry->karty_graczaA[i];
        st_gry->karty_graczaA[i]=-1;
        st_gry->kart_na_stole++;
        wyswietl_info(st_gry, 0);
        st_gry->kolej_gracza=1;
        st_gry->blokada=1;
        g_timeout_add(st_gry->szybkosc, G_SOURCE_FUNC(wyloz_karte), st_gry);
    }
}
