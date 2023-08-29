#include <stdio.h>

//Pawel Tkocz 332168
int main(){
    int n;
    scanf("%d", &n);
    int p=0;
    int q=0;
    int p_pier=1;
    int q_pier=1;
    if(n<4 || n>100000 || n%2!=0){
        printf("NIEPOPRAWNA LICZBA");
    }
    else{
        if(n==4){
            printf("2 2");
        }
        for(int i=3; i<=n/2; i+=2){
            p=i;
            q=n-i;
            p_pier=1;
            q_pier=1;
            for(int j=3; j*j<=p; j+=2){
                if(p%j==0)
                    p_pier=0;
            }
            for(int l=3; l*l<=q; l+=2){
                if(q%l==0)
                    q_pier=0;
            }
            if(p_pier==1 && q_pier==1){
                printf("%d %d ", p, q);
            }
        }
    }
    return 0;
}
