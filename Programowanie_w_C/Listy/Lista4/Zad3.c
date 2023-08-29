#include <stdio.h>

//Pawel Tkocz 332168

void kwadrat_kolek(int n, int k, char tab[n][n]){
    for(int i=k+1; i<n-k-1; i++){
        tab[k][i]='o';
        tab[i][k]='o';
        tab[n-k-1][i]='o';
        tab[i][n-k-1]='o';
    }
}

int main(){
    int a;
    scanf("%d", &a);
    if(a%2==0 || a<1){
        printf("ERROR");
        return 0;
    }
    char tab[a][a];
    for(int i=0; i<a; i++){
        for(int j=0; j<a; j++){
            tab[i][j]='#';
        }
    }
    for(int i=a/2-1; i>=0; i-=2){
        kwadrat_kolek(a, i, tab);
    }
    for(int i=0; i<a; i++){
        for(int j=0; j<a; j++){
            printf("%c", tab[i][j]);
        }
        printf("\n");
    }
    return 0;
}
