#include <stdio.h>
#include <string.h>

//Pawel Tkocz 332168

int replace(int n, char* tekst, char* wynik, char* old_text, char* new_text){
    //n jest max dlugoscia teksow, czyli n=10000
    int dl_old=strlen(old_text);
    int dl_new=strlen(new_text);
    int zn_w=0; //wksaznik sluzacy do zapisywania nowych znakow w tablicy wynik
    for(int i=0; i<n; i++){
        if(strncmp(tekst, old_text, dl_old)==0){
            if(zn_w+dl_new>n){
                //byloby wiecej niz n znakow w tablicy wynik
                return 0;
            }
            for(int j=0; j<dl_new; j++){
                wynik[zn_w]=new_text[j];
                zn_w++;
            }
            tekst+=dl_old;
        }
        else{
            if(zn_w>=n){
                //byloby wiecej niz n znakow w tablicy wynik
                return 0;
            }
            wynik[zn_w]=tekst[0];
            zn_w++;
            tekst++;
        }
        if(tekst[0]==0){
            i=n;
        }
    }
    return 1;
}
