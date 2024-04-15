#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    int n;
    scanf("%d\n", &n);
    for(int i=0; i<n; i++){
        char c = getchar();
        int sum =0;
        bool zero = false;
        int zero_cnt = 0;
        bool flag = false;
        while(c != '\n'){
            int dig = c-'0';
            sum += dig;
            if(dig == 0){
                zero = true;
                zero_cnt++;
            }
            if(dig == 2 || dig == 4 || dig == 6 || dig == 8)
                flag = true;
            c = getchar();
        }
        if(((flag && zero) || (zero_cnt>1)) && sum%3==0)
            printf("red\n");
        else
            printf("cyan\n");
    }
    return 0;
}

