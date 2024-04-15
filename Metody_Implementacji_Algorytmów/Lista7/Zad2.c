#include <stdio.h>
#include <stdlib.h>
 
long long choices(int n){
    long long res = 1;
    for(int i=n-4; i<= n; i++){
        res *= i;
    }
    return res/120;
}
 
int main() {
    int n;
    scanf("%d", &n);
    long long c = choices(n);
    long long res = c*c*120;
    printf("%lld\n", res);
}