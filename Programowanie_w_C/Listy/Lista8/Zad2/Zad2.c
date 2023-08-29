#include <stdio.h>
#include <stdlib.h>
#define ile_stacji 214

struct stacja{
    char nazwa[100];
    int poprzednik;
    int id;
    int czas_do_innych[ile_stacji];
};

void swap(int *a, int *b){
    int pom=*a;
    *a=*b;
    *b=pom;
}

int main(int argc, char *argv[]){
    if(argc<3){
        printf("Nalezy podac nazwy dwoch plikow!\n");
        return 0;
    }
    FILE *p1, *p2;
    char *plik1=argv[1];
    char *plik2=argv[2];
    p1=fopen(plik1,"r");
    p2=fopen(plik2, "r");
    struct stacja tab[ile_stacji];

    char a;
    for(int i=0; i<ile_stacji; i++){
        struct stacja nowa;
        int ind=0;
        a=getc(p1);
        while(a!=';'){
            ind*=10;
            ind+=(a-'0');
            a=getc(p1);
        }
        nowa.id=ind;
        for(int j=0; j<ile_stacji; j++)nowa.czas_do_innych[j]=10000;
        nowa.czas_do_innych[i]=0;
        nowa.poprzednik=i;
        a=getc(p1);
        int n=0;
        while(a!='\n'){
            nowa.nazwa[n]=a;
            n++;
            a=getc(p1);
        }
        nowa.nazwa[n]=0;
        tab[i]=nowa;
    }

    int s1, s2;
    double mean;
    int min;
    while(1){
        fscanf(p2, "%d %d %lf %d", &s1, &s2, &mean, &min);
        if(s1==-1)break;
        a=getc(p2);
        while(a!='\n'){
            a=getc(p2);
        }
        tab[s1].czas_do_innych[s2]=min;
    }
    fclose(p1);
    fclose(p2);
    int odleglosci[ile_stacji];
    int znaleziony[ile_stacji]={0};
    for(int i=0; i<ile_stacji; i++)odleglosci[i]=10000;
    int indeks=157;
    odleglosci[indeks]=0;
    znaleziony[indeks]=1;
    int poprzedni=indeks;
    for(int i=0; i<ile_stacji; i++){
        int minimum_in=0;
        int minimum_czas=10000;
        for(int j=0; j<ile_stacji; j++){
            if(tab[poprzedni].czas_do_innych[j]+odleglosci[poprzedni]<odleglosci[j]){
                odleglosci[j]=tab[poprzedni].czas_do_innych[j]+odleglosci[poprzedni];
                tab[j].poprzednik=poprzedni;
            }
            if(znaleziony[j]==0 && odleglosci[j]<minimum_czas){
                minimum_in=j;
                minimum_czas=odleglosci[j];
            }
        }
        znaleziony[minimum_in]=1;
        poprzedni=minimum_in;
    }
    int odleglosci_pos[ile_stacji];
    for(int i=0; i<ile_stacji; i++)odleglosci_pos[i]=odleglosci[i];
    int posortowane[ile_stacji];
    for(int i=0; i<ile_stacji; i++)posortowane[i]=i;
    for(int i=0; i<ile_stacji-1; i++){
        for(int j=0; j<ile_stacji-i-1; j++){
            if(odleglosci_pos[j]>odleglosci_pos[j+1]){
                swap(&odleglosci_pos[j], &odleglosci_pos[j+1]);
                swap(&posortowane[j], &posortowane[j+1]);
            }
        }
    }
    int trasa[ile_stacji]={0};
    for(int i=1; i<ile_stacji; i++){
        int id_s=posortowane[i];
        printf("Odleglosc do stacji %s: %d\n", tab[id_s].nazwa, odleglosci_pos[i]);
        if(odleglosci[id_s]==10000)continue;
        trasa[0]=tab[id_s].id;
        int n=1;
        struct stacja pom=tab[id_s];
        while(pom.id!=indeks){
            trasa[n]=pom.poprzednik;
            pom=tab[pom.poprzednik];
            n++;
        }
        printf("Trasa przez: ");
        for(int j=n-1; j>=1; j--){
            printf("%s --%dm-> ", tab[trasa[j]].nazwa, odleglosci[trasa[j-1]]-odleglosci[trasa[j]]);
        }
        printf("%s\n", tab[id_s].nazwa);
    }
    printf("Najblizsza stacja: %s\n", tab[posortowane[1]].nazwa);
    printf("Najdalsza stacja: %s\n", tab[posortowane[ile_stacji-1]].nazwa);
    return 0;
}

