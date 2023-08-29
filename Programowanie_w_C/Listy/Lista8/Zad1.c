#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "kolejka.h"

struct dane{
    char imie[25];
    char nazwisko[25];
};

int main(){
    int max_size=1;
    int size=0;
    char imie[25];
    char nazwisko[25];
    int wiek;
    struct kopiec *tab=calloc(max_size, sizeof(struct kopiec));
    struct dane *osoby=calloc(max_size, sizeof(struct dane));
    //wczytywanie danych powinno byc zakonczone przez wpisanie cyfry 0
    while(1){
        scanf("%s", imie);
        if(strcmp(imie, "0")==0){
            break;
        }
        scanf("%s", nazwisko);
        scanf("%d", &wiek);
        struct dane dn;
        struct kopiec kop;
        kop.klucz=size;
        kop.priorytet=wiek;
        wstaw_element(kop, tab, size);
        for(int i=0; i<25; i++){
            dn.nazwisko[i]=nazwisko[i];
            dn.imie[i]=imie[i];
        }
        osoby[size]=dn;
        size++;
        if(size==max_size){
            max_size=2*size+1;
            tab=realloc(tab, max_size*sizeof(struct kopiec));
            osoby=realloc(osoby, max_size*sizeof(struct dane));
        }
    }
    size--;
    int ile=size;
    for(int i=ile; i>=0; i--){
        int n=najwieksza_wartosc(tab);
        printf("%d %s %s\n", tab[0].priorytet, osoby[n].imie, osoby[n].nazwisko);
        usun_najwiekszy(tab, size);
        size--;
    }
    free(tab);
    free(osoby);
    //sortowanie 5000 losowych liczb;
    struct kopiec *tab2=calloc(5000, sizeof(struct kopiec));
    srand(time(NULL));
    for(int i=0; i<5000; i++){
        int a=rand();
        struct kopiec kop;
        kop.priorytet=a;
        wstaw_element(kop, tab2, i);
    }
    for(int i=0; i<5000; i++){
        printf("%d ", tab2[0].priorytet);
        usun_najwiekszy(tab2, 4999-i);
    }
    free(tab2);
    return 0;
}
