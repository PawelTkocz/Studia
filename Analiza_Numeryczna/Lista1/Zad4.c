#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    double tab[21];
    tab[0] = log(2023.0/2022);
    for(int i=1; i<21; i++) tab[i] = 1.0/i - tab[i-1]*2022;

    for(int i=1; i<=20; i+=2) printf("%d. %lf\n", i, tab[i]);
    printf("\n");
    for(int i=2; i<=20; i+=2) printf("%d. %lf\n", i, tab[i]);
}

