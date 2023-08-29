#include <stdio.h>
#include <string.h>
#include "replace.h"
#define Max_dl_tekstu 10000

//Pawel Tkocz 332168

int replace(int n, char* tekst, char* wynik, char* old_text, char* new_text);
//funkcja zwroci wartosc 1 jesli wynikowy teskt nie bedzie za dlugi
//jesli zwroci wartosc 0 to znaczy ze wynik zawieralby wiecej niz 10000 znakow

int main(int argc, char** argv){
    if(argc!=3){
        printf("Podano niepoprawna liczbe argumentow\n");
        return 0;
    }
    if(strlen(argv[1])>1000 || strlen(argv[2])>1000){
        printf("Argumenty moga zawierac maksymalnie 1000 znakow\n");
        return 0;
    }
    char tekst[Max_dl_tekstu]={0};
    char a=getchar();
    int zn=0;
    while(a!=EOF){
        if(zn==Max_dl_tekstu){
            printf("Podano za dlugi tekst. Maksymalna dlugosc tekstu: %d znakow\n", Max_dl_tekstu);
            return 0;
        }
        tekst[zn]=a;
        zn++;
        a=getchar();
    }
    char wynik[Max_dl_tekstu]={0};
    if(replace(Max_dl_tekstu, tekst, wynik, argv[1], argv[2])==1){
         printf("\n%s", wynik);
    }
    else{
        printf("\nWyynikowy tekst zawiera wiecej niz %d znakow\n", Max_dl_tekstu);
    }
    return 0;
}
