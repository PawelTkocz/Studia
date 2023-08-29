#include <stdio.h>
#include <time.h>

void tik(){
    time_t seconds;
    long long s=time(&seconds);
    while(1){
        int k=time(&seconds);
        if(k>s){
            s=k;
            printf("tik\n");
            fflush(stdout);
        }
    }
}

int main(){
    tik();
    return 0;
}
