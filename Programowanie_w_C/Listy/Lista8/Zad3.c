#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct wezel{
    int stworzony;
    int ind;
    struct wezel *wezel_prawy;
    struct wezel *wezel_lewy;
}wezel;

void init(struct wezel *w){
    w->wezel_lewy=NULL;
    w->wezel_prawy=NULL;
}

void odp_wsk_wez(struct wezel **odp, struct wezel *x, struct wezel *y, struct wezel *z, char a){
    if(a=='x')*odp=x;
    if(a=='y')*odp=y;
    if(a=='z')*odp=z;
}

int policz_c(int *tab, struct wezel *a){
    if(a==NULL || tab[a->ind]==1)return 0;
    tab[a->ind]=1;
    return 1+policz_c(tab, a->wezel_lewy)+policz_c(tab, a->wezel_prawy);
}

int main(){
    int n;
    scanf("%d", &n);
    char a;
    char s1[5];
    char b1[5];
    char b2[5];
    int r=1;
    int c=0;
    int size=0;
    struct wezel *x=NULL;
    struct wezel *y=NULL;
    struct wezel *z=NULL;
    a=getchar();
    printf("round: 0, x: 0, y: 0, z: 0, cells: 0\n");
    int *tab=calloc(1, sizeof(int));
    for(int i=0; i<n; i++){
        a=getchar();
        scanf("%s", s1);
        scanf("%s", s1);
        if(strcmp(s1, "cons")==0){
            scanf("%s", b1);
            scanf("%s", b2);
            struct wezel **lewy;
            lewy = malloc(sizeof(*lewy));
            *lewy = malloc(sizeof(**lewy));
            struct wezel **prawy=NULL;
            prawy = malloc(sizeof(*prawy));
            *prawy = malloc(sizeof(**prawy));
            odp_wsk_wez(lewy, x, y, z, b1[0]);
            odp_wsk_wez(prawy, x, y, z, b2[0]);
            struct wezel *nowy=malloc(sizeof(struct wezel));
            init(nowy);
            nowy->ind=size;
            nowy->stworzony=r;
            nowy->wezel_lewy=*lewy;
            nowy->wezel_prawy=*prawy;
            if(a=='x'){
                x=nowy;
            }
            if(a=='y'){
                y=nowy;
            }
            if(a=='z'){
                z=nowy;
            }
            size++;
            tab=realloc(tab, (size+1)*sizeof(int));
            free(lewy);
            //free(*lewy);
            free(prawy);
            //free(*prawy);
        }
        else if(strcmp(s1, "null")==0){
            if(a=='x')x=NULL;
            if(a=='y')y=NULL;
            if(a=='z')z=NULL;
        }
        else if(strcmp(s1, "car")==0){
            scanf("%s", b1);
            struct wezel **pierw;
            pierw = malloc(sizeof(*pierw));
            *pierw = malloc(sizeof(**pierw));
            odp_wsk_wez(pierw, x, y, z, b1[0]);
            if(*pierw!=NULL){
                if(a=='x')x=(*pierw)->wezel_lewy;
                if(a=='y')y=(*pierw)->wezel_lewy;
                if(a=='z')z=(*pierw)->wezel_lewy;
            }
            free(pierw);
            //free(*pierw);
        }
        else if(strcmp(s1, "cdr")==0){
            scanf("%s", b1);
            struct wezel **pierw;
            pierw = malloc(sizeof(*pierw));
            *pierw = malloc(sizeof(**pierw));
            odp_wsk_wez(pierw, x, y, z, b1[0]);
            if(*pierw!=NULL){
                if(a=='x')x=(*pierw)->wezel_prawy;
                if(a=='y')y=(*pierw)->wezel_prawy;
                if(a=='z')z=(*pierw)->wezel_prawy;
            }
            free(pierw);
            //free(*pierw);
        }
        c=0;
        for(int j=0; j<size; j++){
            tab[j]=0;
        }
        c+=policz_c(tab, x);
        c+=policz_c(tab, y);
        c+=policz_c(tab, z);
        printf("round: %d, ", r);
        if(x!=NULL)printf("x: %d, ", x->stworzony);
        else printf("x: 0, ");
        if(y!=NULL)printf("y: %d, ", y->stworzony);
        else printf("y: 0, ");
        if(z!=NULL)printf("z: %d, ", z->stworzony);
        else printf("z: 0, ");
        printf("cells: %d\n", c);
        r++;
        a=getchar();
    }
    free(tab);
    return 0;
}
