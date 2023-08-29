#include <stdio.h>
#include <stdlib.h>

int f(int a, int b, int l){
    int tab[l];
    for(int i=0; i<l; i++){
        tab[i]=0;
    }
    int zn=0;
    while(a>0){
        tab[zn]=a%b;
        a/=b;
        zn++;
    }
    int w=tab[0];
    for(int i=1; i<l; i++){
        w*=b;
        w+=tab[i];
    }
    return w;
}

int main(){
    int b, l, n;
    n=0;
    scanf("%d %d", &b, &l);
    char a=getchar();
    while(a!=EOF){
        if(a>='0' && a<='9'){
            n*=10;
            n+=a-'0';
        }
        a=getchar();
    }
    if(n==0){
        n=1;
        for(int i=0; i<l; i++){
            n*=b;
        }
    }

    for(int i=0; i<n; i++){
        int iks=f(i%n, b, l)%n;
        for(int j=0; j<n; j++){
            if(j==iks)printf("X");
            else printf(".");
        }
        printf("\n");
    }
    printf("\n");
    srand(0);
    for(int i=0; i<n; i++){
        int iks=rand()%n;
        for(int j=0; j<n; j++){
            if(j==iks)printf("X");
            else printf(".");
        }
        printf("\n");
    }
    return 0;
}
