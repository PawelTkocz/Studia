#include <stdio.h>
#include <stdlib.h>

struct kopiec{
    int klucz;
    int priorytet;
};

void wstaw_element(struct kopiec kop, struct kopiec *tab, int size){
    tab[size]=kop;
    if(size==0)return;
    int koniec=0;
    while(koniec==0 && size!=0){
        struct kopiec ojciec=tab[(size+1)/2-1];
        if(ojciec.priorytet<tab[size].priorytet){
            tab[(size+1)/2-1]=tab[size];
            tab[size]=ojciec;
            size=(size+1)/2-1;
        }
        else{
            koniec=1;
        }
    }
}

int najwieksza_wartosc(struct kopiec *tab){
    return tab[0].klucz;
}

void usun_najwiekszy(struct kopiec *tab, int size){
    tab[0]=tab[size];
    int p=0;
    while(1){
        if(2*p+1>=size && 2*p+2>=size)return;
        else{
            if(2*p+2<size){
                //ojciec ma dwoch synow
                if(tab[2*p+1].priorytet>tab[p].priorytet && tab[2*p+1].priorytet>=tab[2*p+2].priorytet){
                    //zamiana z lewym synem
                    struct kopiec pom=tab[p];
                    tab[p]=tab[2*p+1];
                    tab[2*p+1]=pom;
                    p=2*p+1;
                }
                else if(tab[2*p+2].priorytet>tab[p].priorytet && tab[2*p+2].priorytet>=tab[2*p+1].priorytet){
                    //zamiana z prawym synem
                    struct kopiec pom=tab[p];
                    tab[p]=tab[2*p+2];
                    tab[2*p+2]=pom;
                    p=2*p+2;
                }
                else return;
            }
            else{
                //ojciec ma tylko lewego syna
                if(tab[2*p+1].priorytet>tab[p].priorytet){
                    //zamiana z lewym synem
                    struct kopiec pom=tab[p];
                    tab[p]=tab[2*p+1];
                    tab[2*p+1]=pom;
                    p=2*p+1;
                }
                return;
            }
        }
    }
}
