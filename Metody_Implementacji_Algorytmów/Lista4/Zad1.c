#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    int q;
    scanf("%d", &q);
    for(int i=0; i<q; i++){
        int n;
        scanf("%d\n", &n);
        int tab[n];
        for(int j=0; j<n; j++){
            int k;
            scanf("%d", &k);
            tab[j] = k;
        }
        int results[n];
        for(int j=0; j<n; j++)
            results[j] = 0;

        for(int j=0; j<n; j++){
            if(results[j] != 0)
                continue;
            int cycle[n];
            int cycle_len = 1;
            cycle[0] = j;
            int cur = tab[j]-1;
            while(cur != j){
                cycle[cycle_len] = cur;
                cur = tab[cur]-1;
                cycle_len++;
            }
            for(int p=0; p<cycle_len; p++){
                results[cycle[p]] = cycle_len;
            }
        }
        for(int j=0; j<n; j++)
            printf("%d ", results[j]);
        printf("\n");
    }
}

