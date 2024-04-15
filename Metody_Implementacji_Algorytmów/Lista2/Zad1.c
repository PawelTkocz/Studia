#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    int n, a, b;
    scanf("%d %d %d\n", &n, &a, &b);

    int sum = 0;
    int max_sum = a+b;
    int prev = 0;
    for(int i=0; i<n; i++){
        char c = getchar();
        if(c == '*'){
            prev = 0;
            continue;
        }
        if(prev == 0){
            if(a>b){
                prev = -1;
                a--;
                sum++;
            }
            else{
                prev = 1;
                b--;
                sum++;
            }
        }
        else if(prev == -1){
            prev = 1;
            if(b > 0){
                b--;
                sum++;
            }
        }
        else if(prev == 1){
            prev = -1;
            if(a > 0){
                a--;
                sum++;
            }
        }
        if(sum == max_sum)
            break;
    }

    printf("%d\n", sum);

    return 0;
}
