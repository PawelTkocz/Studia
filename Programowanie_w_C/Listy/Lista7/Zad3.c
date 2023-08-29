#include <stdio.h>
#include <stdlib.h>

typedef struct e_lista *ListaWsk;
struct e_lista{
    int wartosc;
    struct e_lista *next;
};

void init(ListaWsk *wsk){
    *wsk=NULL;
}
void clr(ListaWsk *wsk){
    for(ListaWsk p=*wsk, q; p!=NULL; p=q){
        q=p->next;
        free(p);
    }
    *wsk=NULL;
}
void Inse(ListaWsk *wsk, int p, int x){
    ListaWsk c=(ListaWsk)malloc(sizeof(struct e_lista));
    c->wartosc=x;
    if(p==0){
        c->next=*wsk;
        *wsk=c;
        return;
    }
    ListaWsk a=*wsk;
    for(int i=0; i<p-1; i++){
        a=(a->next);
    }
    c->next=(a->next);
    (a->next)=c;
}
void Dele(ListaWsk *wsk, int p){
    if(p==0){
        ListaWsk pom=((*wsk)->next);
        free(*wsk);
        *wsk=pom;
        return;
    }
    ListaWsk a=*wsk;
    for(int i=0; i<p-1; i++){
        a=(a->next);
    }
    (a->next)=((a->next)->next);
    //ListaWsk pomm=(a->next);
    //free(pomm);
}
int Sum(ListaWsk *wsk, int p1, int p2){
    //printf("hej");
    int suma=0;
    ListaWsk a=*wsk;
    //printf("hej");
    for(int i=0; i<p1; i++){
        a=(a->next);
    }
    //printf("hej");
    for(int i=p1; i<=p2; i++){
        suma+=(a->wartosc);
        a=(a->next);
    }
    //printf("hej");
    return suma;
}

void wypisz(ListaWsk *wsk){
    ListaWsk p=*wsk;
    printf("\n");
    while(p!=NULL){
        printf("%d ", p->wartosc);
        p=(p->next);
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);
    ListaWsk L0;
    init(&L0);
    getchar();
    for(int i=0; i<n; i++){
        char a=getchar();
        int b, c;
        scanf("%d", &b);
        if(a=='I'){
            scanf("%d", &c);
            //printf("ok");
            Inse(&L0, b, c);
        }
        if(a=='D'){
            Dele(&L0, b-1);
        }
        if(a=='S'){
            scanf("%d", &c);
            int suma;
            suma=Sum(&L0, b-1, c-1);
            printf("%d\n", suma);
        }
        getchar();
        wypisz(&L0);
    }
    return 0;
}
