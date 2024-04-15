#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    char numbers[1000000];
    char c = getchar();
    int cnt = 0;
    while(c != '\n'){
        numbers[cnt++] = c-'0';
        c = getchar();
    }
    int a, b;
    scanf("%d %d", &a, &b);

    bool right[cnt];
    int mod = 0;
    int mod_10 = 1;
    for(int i=cnt-1; i>=0; i--){
        mod = (mod+mod_10*numbers[i])%b;
        mod_10 = (10*mod_10)%b;
        if(mod == 0)
            right[i] = true;
        else
            right[i] = false;
    }
    mod = 0;
    int answ = -1;
    for(int i=0; i<cnt-1; i++){
        mod = (mod*10+numbers[i])%a;
        if(mod == 0 && numbers[i+1] != 0 && right[i+1]){
            answ = i;
            break;
        }
    }
    if(answ == -1)
        printf("NO\n");
    else{
        printf("YES\n");
        for(int i=0; i<=answ; i++){
            putchar('0'+numbers[i]);
            //printf("%d", numbers[i]);
        }
        printf("\n");
        for(int i=answ+1; i<cnt; i++){
            putchar('0'+numbers[i]);
            //printf("%d", numbers[i]);
        }
        printf("\n");
    }
    return 0;
}
