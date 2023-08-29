#ifndef KIERKI_GTK_H
#define KIERKI_GTK_H
#include <gtk/gtk.h>
#include "kierki_obs.h"

void rozpocznij_gre(struct stan_gry *st_gry);
void wyswietl_info(struct stan_gry *st_gry, int id);
void potwierdz_imie(GtkWidget *widget, struct stan_gry *st_gry);
void popros_o_imie(struct stan_gry *st_gry);
void ukryj_karty(struct stan_gry *st_gry);
gboolean animacja_rozdawania(struct stan_gry *st_gry);
void nowa_runda(GtkWidget *widget, struct stan_gry *st_gry);
void nowa_gra(GtkWidget *widget, struct stan_gry *st_gry);
void wyswietl_punktacje(GtkWidget *widget, struct stan_gry *st_gry);
void wyswietl_zakonczenie(struct stan_gry *st_gry);
gboolean zbierz_karty(struct stan_gry *st_gry);
gboolean wyloz_karte(struct stan_gry *st_gry);
gboolean zobacz_karty(struct stan_gry *st_gry);
void przekaz_karty(GtkButton *button, struct stan_gry *st_gry);
void zagraj_karte(GtkButton *button, struct para *p);

#endif
