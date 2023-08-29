#include <stdio.h>
#include <stdlib.h>


int main(){
    int max_size=10;
    int size=0;
    char* tab=calloc(max_size, sizeof(char));
    char a=getchar();
    while(a!=EOF){
        tab[size]=a;
        size++;
        if(size==max_size){
            max_size*=2;
            tab=realloc(tab, max_size*sizeof(char));
            int rozmiar=max_size*sizeof(char);
            printf("Zwiekszono ilosc pamieci. W tablicy zmiesci sie teraz %d charow, wiec jej rozmiar wynosi %d bajtow\n", max_size, rozmiar);
        }
        a=getchar();
    }
    for(int i=0; i<max_size; i++){
        printf("%c", tab[i]);
    }
    free(tab);
    return 0;
}
