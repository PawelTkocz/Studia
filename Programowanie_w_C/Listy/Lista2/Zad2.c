#include <stdio.h>

//Pawel Tkocz 332168
int main(int argc, char** argv){
    int asci[256]={0}; //tablica bedzie przyjmowala wartosci 0 lub 1
    if(argv[1][0]=='-' && argv[1][2]==0 && (argv[1][1]=='c' || argv[1][1]=='d' || argv[1][1]=='x') && argc==3){
        if(argv[1][1]=='c'){
            int k=getchar();
            while(k!=EOF){
                asci[k]=1; //w tablicy "asci" zaznaczam ktore znaki pojawily sie na wejsciu
                k=getchar();
            }
            int ile=0;
            int zn=0;
            while(argv[2][zn]!=0){
                int t=argv[2][zn];
                if(asci[t]==1){ //sprawdzam czy kolejne znaki z s pojawily sie na wejsciu
                    ile++;
                }
                zn++;
            }
            printf("\n%d", ile);
        }
        else{
            //jesli wywolano -d lub -x
            int zn=0;
            while(argv[2][zn]!=0){
                int t=argv[2][zn];
                asci[t]=1; //w tablicy "asci" zaznaczam ktore znaki pojawiaja sie w s
                zn++;
            }
            if(argv[1][1]=='d'){
                int k=getchar();
                while(k!=EOF){
                    if(asci[k]!=1){
                        printf("%c", k); //wypisuje znaki z wejscia, ktore nie pojawily sie w s
                    }
                    k=getchar();
                }
            }
            if(argv[1][1]=='x'){
                int k=getchar();
                while(k!=EOF){
                    if(asci[k]==1){
                        printf("%c", k); //wypisuje znaki z wejscia, ktore pojawily sie w s
                    }
                    k=getchar();
                }
            }
        }
        printf("\n");
    }
    else{
        printf("Niewlasciwe wywolanie komendy\n");
    }
    return 0;
}
