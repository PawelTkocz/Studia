#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(){
    int n, x, y;
    scanf("%d %d %d\n", &n, &x, &y);
    bool tab[n];
    for(int i=0; i<n; i++){
        char c = getchar();
        if(c == '0')
            tab[i] = false;
        else
            tab[i] = true;
    }

    int cheaper = y;
    if(x<y)
        cheaper = x;

    bool reversed;
    long long values[n];
    if(tab[0]){
        values[0] = 0;
        reversed = false;
    }
    else{
        values[0] = y;
        reversed = true;
    }


    for(int i=1; i<n; i++){
        if(tab[i] || !tab[i-1])
            values[i] = values[i-1];
        else{
            if(reversed)
                values[i] = values[i-1] + cheaper;
            else{
                values[i] = y;
                reversed = true;
            }
        }
    }
    printf("%lld\n", values[n-1]);
    return 0;
}

