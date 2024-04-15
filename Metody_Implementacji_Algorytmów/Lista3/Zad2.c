#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int maximum(int a, int b, int c){
    if(a >= b && a >= c)
        return a;
    if(b >= c)
        return b;
    return c;
}

int main(){
    int n, a, b, c;
    scanf("%d %d %d %d", &n, &a, &b, &c);
    int tab[n+1];
    tab[0] = 0;
    for(int i=1; i<n+1; i++){
        int ind1 = i-a;
        int ind2 = i-b;
        int ind3 = i-c;
        int v1 = ind1<0 || tab[ind1] == -1 ? -1 : tab[ind1] + 1;
        int v2 = ind2<0 || tab[ind2] == -1 ? -1 : tab[ind2] + 1;
        int v3 = ind3<0 || tab[ind3] == -1 ? -1 : tab[ind3] + 1;
        tab[i] = maximum(v1, v2, v3);
    }
    printf("%d\n", tab[n]);
    return 0;
}

