#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(){
    int n;
    scanf("%d\n", &n);

    int len = 1000001;
    bool sito[len];
    for(int i=0; i<len; i++)
        sito[i] = true;
    for(int i=2; i<=sqrt(len); i++){
        if(sito[i]){
            for(int j=2*i; j<len; j+=i)
                sito[j] = false;
        }
    }
    sito[1] = false;

    for(int i=0; i<n; i++){
        long long a;
        scanf("%lld", &a);
        long long s = sqrt(a);
        if(s*s == a && sito[s])
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

