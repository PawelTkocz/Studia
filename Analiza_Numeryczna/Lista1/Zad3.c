#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    double tab[51];
    tab[0] = 1.0;
    tab[1] = -1.0/7;
    for(int i=2; i<=50; i++) tab[i] = 146.0/7*tab[i-1] + 3*tab[i-2];
    for(int i=0; i<51; i++)printf("%d. %lf\n", i, tab[i]);
}
