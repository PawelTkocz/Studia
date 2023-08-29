#include <stdio.h>

//Pawel Tkocz 332168
int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    int dane_ok=1;
    if(b>1000000 || a>1000000 || b<1 || a<1){
        printf("Obie liczby musza byc z zakresu [1,1000000]\n");
        dane_ok=0;
    }
    if(b<=a){
        printf("Druga liczba musi byc wieksza niz pierwsza\n");
        dane_ok=0;
    }
    if(dane_ok==0){
        return 0;
    }
    int k;
    int suma;
    int ok;
    int cyfra;
    for(int i=a; i<b; i++){
        k=i;
        ok=1;
        suma=0;
        while(k>0){
            cyfra=k%10;
            suma+=cyfra;
            if(cyfra==0){
                ok=0;
                k=0;
            }
            else if(i%cyfra!=0){
                ok=0;
                k=0;
            }
            k/=10;
        }
        if(ok==1){
            if(i%suma==0){
                printf("%d\n", i);
            }
        }
    }
    return 0;
}
