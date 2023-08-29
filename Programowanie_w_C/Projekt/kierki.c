#include <stdio.h>
#include <stdlib.h>
#include "kierki_obs.h"
#include "kierki_gtk.h"

int main(int argc,char *argv[]){
    struct stan_gry *st_gry=(struct stan_gry*)malloc(sizeof(struct stan_gry));
    inicjalizuj_stan_gry(st_gry);
    gtk_init(&argc, &argv);
    rozpocznij_gre(st_gry);
    gtk_main();
    return 0;
}
