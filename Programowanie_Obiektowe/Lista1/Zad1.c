#include <stdio.h>
#include <stdlib.h>

typedef enum {trojkat, kolo, kwadrat} TYPFIG;
typedef struct{
    TYPFIG typfig;
    float wiezcholki[4][2];
    float dl_boku;
    float srodek_kola[2];
    float r;
}Figura;

Figura * new_square(float x, float y, float a){
    if(a<=0){
        printf("Bok kwadratu musi miec dlugosc wieksza od 0");
        return NULL;
    }
    Figura *f = (Figura*)malloc(sizeof(Figura));
    f->typfig=kwadrat;
    f->wiezcholki[0][0]=x;
    f->wiezcholki[0][1]=y;
    f->wiezcholki[1][0]=x+a;
    f->wiezcholki[1][1]=y;
    f->wiezcholki[2][0]=x+a;
    f->wiezcholki[2][1]=y+a;
    f->wiezcholki[3][0]=x;
    f->wiezcholki[3][1]=y+a;
    f->dl_boku=a;
    return f;
}

Figura * new_circle(float x, float y, float r){
    if(r<=0){
        printf("Promien kola musi byc wiekszy rowny 0");
        return NULL;
    }
    Figura *f = (Figura*)malloc(sizeof(Figura));
    f->typfig=kolo;
    f->srodek_kola[0]=x;
    f->srodek_kola[1]=y;
    f->r=r;
    return f;
}

int ok_trojkat(float x1, float y1, float x2, float y2, float x3, float y3){
    if((x1==x2 && y1==y2)||(x1==x3 && y1==y3)||(x2==x3 && y2==y3))return 0;
    return 1;
}

Figura * new_triangle(float x1, float y1, float x2, float y2, float x3, float y3){
    if(ok_trojkat(x1, y1, x2, y2, x3, y3)==0){
        printf("Nieprawidlowe wiezcholki trojkata");
        return NULL;
    }
    Figura *f = (Figura*)malloc(sizeof(Figura));
    f->typfig=trojkat;
    f->wiezcholki[0][0]=x1;
    f->wiezcholki[0][1]=y1;
    f->wiezcholki[1][0]=x2;
    f->wiezcholki[1][1]=y2;
    f->wiezcholki[2][0]=x3;
    f->wiezcholki[2][1]=y3;
    return f;
}

float pole(Figura *f){
    if(f->typfig==kolo)return 3.1415*f->r*f->r;
    else if(f->typfig==kwadrat)return f->dl_boku*f->dl_boku;
    else{
        int x1=f->wiezcholki[0][0];
        int x2=f->wiezcholki[1][0];
        int x3=f->wiezcholki[2][0];
        int y1=f->wiezcholki[0][1];
        int y2=f->wiezcholki[1][1];
        int y3=f->wiezcholki[2][1];
        return abs((x2-x1)*(y3-y1)-(y2*y1)*(x3-x1))/2;
    }
}

void przesun(Figura *f, float x, float y){
    if(f->typfig==kolo){
        f->srodek_kola[0]+=x;
        f->srodek_kola[1]+=y;
    }
    else if(f->typfig==kwadrat){
        for(int i=0; i<4; i++){
            f->wiezcholki[i][0]+=x;
            f->wiezcholki[0][i]+=y;
        }
    }
    else{
        for(int i=0; i<3; i++){
            f->wiezcholki[i][0]+=x;
            f->wiezcholki[0][i]+=y;
        }
    }
}

void show(Figura *f){
    if(f->typfig==kolo){
        printf("Kolo o srodku w punkcie (%f, %f) i promieniu dlugosci %f\n", f->srodek_kola[0], f->srodek_kola[1], f->r);
    }
    else if(f->typfig==kwadrat){
        printf("Kwadrat o boku %f i wiezcholkach w punktach: ", f->dl_boku);
        for(int i=0; i<4; i++){
            printf("(%f, %f) ", f->wiezcholki[i][0], f->wiezcholki[i][1]);
        }
        printf("\n");
    }
    else{
        printf("Trojkat o wiezcholkach w punktach: ");
        for(int i=0; i<3; i++){
            printf("(%f, %f) ", f->wiezcholki[i][0], f->wiezcholki[i][1]);
        }
        printf("\n");
    }
}

float sumapol(Figura* f[], int size){
    int suma=0;
    for(int i=0; i<size; i++){
        suma+=pole(f[i]);
    }
    return suma;
}

int main(){
    return 0;
}
