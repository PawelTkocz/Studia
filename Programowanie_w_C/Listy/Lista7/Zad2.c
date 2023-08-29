#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct e_lista *ListaWsk;
struct e_lista{
    char wartosc[100];
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

void insert(ListaWsk *wsk, int p, char *x){
    ListaWsk c=(ListaWsk)malloc(sizeof(struct e_lista));
    for(int i=0; i<100; i++){
        c->wartosc[i]=x[i];
    }
    if(p==0){
        (c->next)=(*wsk);
        (*wsk)=c;
        return;
    }
    ListaWsk a=*wsk;
    for(int i=0; i<p-1; i++){
        a=(a->next);
    }
    c->next=(a->next);
    (a->next)=c;
}
void del(ListaWsk *wsk, int p){
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
    free(a->next);
    (a->next)=((a->next)->next);
}
char* get(ListaWsk *wsk, int p){
    ListaWsk a=*wsk;
    for(int i=0; i<p; i++){
        a=(a->next);
    }
    return a->wartosc;
}

void list_print(ListaWsk *wsk){
    ListaWsk p=*wsk;
    while(p!=NULL){
        printf("%s ", p->wartosc);
        p=(p->next);
    }
    printf("\n");
}

int main(){
    ListaWsk L0;
    init(&L0);
    char s1[10];
    char s2[10];
    char s3[1000];
    int petla=1;
    while(petla==1){
        scanf("%s", s1);
        if(strcmp(s1, "insert")==0){
            scanf("%s", s2);
            scanf("%s", s3);
            int b=atoi(s2);
            insert(&L0, b, s3);
        }
        if(strcmp(s1, "del")==0){
            scanf("%s", s2);
            int b=atoi(s2);
            del(&L0, b-1);
        }
        if(strcmp(s1, "get")==0){
            scanf("%s", s2);
            int b=atoi(s2);
            char* ele=get(&L0, b-1);
            printf("%s\n", ele);
        }
        if(strcmp(s1, "koniec")==0)petla=0;
        else list_print(&L0);
    }
    clr(&L0);
    return 0;
}
