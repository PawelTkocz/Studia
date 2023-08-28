#include <stdio.h>
#include <stdlib.h>

//Pawel Tkocz 332168

typedef struct {
  int licz, mian;
} Ulamek;

int znak_ulamka(int num, int denom){
    if(num*denom<0)return -1;
    return 1;
}

int nwd(int a, int b){
    int pom;
    while(b!=0){
        pom=b;
        b=a%b;
        a=pom;
    }
    return a;
}

int nww(int a, int b){
    return a*b/nwd(a, b);
}

void uprosc_ulamek(Ulamek *u){
    if(u==NULL)return;
    int num=u->licz;
    int denom=u->mian;
    int sign=znak_ulamka(num, denom);
    num=abs(num);
    denom=abs(denom);
    int nwd_num_denom=nwd(num, denom);
    u->licz=sign*num/nwd_num_denom;
    u->mian=denom/nwd_num_denom;
}

Ulamek * dodaj_ulamki1(Ulamek *u1, Ulamek *u2){
    if(u1==NULL || u2==NULL)return NULL;
    Ulamek *fraction = (Ulamek*)malloc(sizeof(Ulamek));
    int nww_mianownikow=nww(u1->mian, u2->mian);
    fraction->mian=nww_mianownikow;
    int rozszerzenie1=nww_mianownikow/u1->mian;
    int rozszerzenie2=nww_mianownikow/u2->mian;
    fraction->licz=u1->licz*rozszerzenie1+u2->licz*rozszerzenie2;
    uprosc_ulamek(fraction);
    return fraction;
}

void dodaj_ulamki2(Ulamek *u1, Ulamek *u2){
    if(u1==NULL || u2==NULL)return;
    int nww_mianownikow=nww(u1->mian, u2->mian);
    int rozszerzenie1=nww_mianownikow/u1->mian;
    int rozszerzenie2=nww_mianownikow/u2->mian;
    u2->licz=u1->licz*rozszerzenie1+u2->licz*rozszerzenie2;
    u2->mian=nww_mianownikow;
    uprosc_ulamek(u2);
}

Ulamek * odejmij_ulamki1(Ulamek *u1, Ulamek *u2){
    if(u1==NULL || u2==NULL)return NULL;
    u2->licz*=-1;
    Ulamek *pom=dodaj_ulamki1(u1, u2);
    u2->licz*=-1;
    return pom;
}

void odejmij_ulamki2(Ulamek *u1, Ulamek *u2){
    if(u1==NULL || u2==NULL)return;
    u2->licz*=-1;
    dodaj_ulamki2(u1, u2);
}

Ulamek * pomnoz_ulamki1(Ulamek *u1, Ulamek *u2){
    if(u1==NULL || u2==NULL)return NULL;
    Ulamek *fraction = (Ulamek*)malloc(sizeof(Ulamek));
    fraction->licz=u1->licz*u2->licz;
    fraction->mian=u1->mian*u2->mian;
    uprosc_ulamek(fraction);
    return fraction;
}

void pomnoz_ulamki2(Ulamek *u1, Ulamek *u2){
    if(u1==NULL || u2==NULL)return;
    int mian=u1->mian*u2->mian;
    int licz=u1->licz*u2->licz;
    u2->licz=licz;
    u2->mian=mian;
    uprosc_ulamek(u2);
}

Ulamek * podziel_ulamki1(Ulamek *u1, Ulamek *u2){
    if(u1==NULL || u2==NULL)return NULL;
    if(u2->licz==0){
        printf("Nie mozna dzielic przez 0\n");
        return NULL;
    }
    int pom=u2->licz;
    u2->licz=u2->mian;
    u2->mian=pom;
    Ulamek *odp=pomnoz_ulamki1(u1, u2);
    pom=u2->licz;
    u2->licz=u2->mian;
    u2->mian=pom;
    return odp;
}

void podziel_ulamki2(Ulamek *u1, Ulamek *u2){
    if(u1==NULL || u2==NULL)return;
    if(u2->licz==0){
        printf("Nie mozna dzielic przez 0\n");
        return;
    }
    int pom=u2->licz;
    u2->licz=u2->mian;
    u2->mian=pom;
    pomnoz_ulamki2(u1, u2);
}

Ulamek * nowy_ulamek(int num, int denom){
    if(denom==0){
        printf("Nie mozna dzielic przez 0\n");
        return NULL;
    }
    Ulamek *fraction = (Ulamek*)malloc(sizeof(Ulamek));
    fraction->licz=num;
    fraction->mian=denom;
    uprosc_ulamek(fraction);
    return fraction;
}

void show(Ulamek *u){
    if(u==NULL)return;
    if(u->mian==1)printf("%d\n", u->licz);
    else printf("%d/%d\n", u->licz, u->mian);
}

int main(){
    Ulamek *a = nowy_ulamek(1, 3);
    Ulamek *b = nowy_ulamek(-3, 4);
    Ulamek *c = nowy_ulamek(2, 7);
    Ulamek *d = nowy_ulamek(-3, 5);
    show(dodaj_ulamki1(a, b));
    show(odejmij_ulamki1(c, d));
    show(pomnoz_ulamki1(a, c));
    show(podziel_ulamki1(b, d));
    dodaj_ulamki2(c, b);
    show(b);
    odejmij_ulamki2(a, c);
    show(c);
    pomnoz_ulamki2(d, d);
    show(d);
    podziel_ulamki2(b, c);
    show(c);
    return 0;
}
