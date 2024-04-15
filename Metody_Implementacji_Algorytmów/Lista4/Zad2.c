#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    long long n, m, l;
    scanf("%lld %lld %lld", &n, &m, &l);
    long long len[n+2];
    len[0] = 0;
    len[n+1] = 0;
    long long ngroups = 0;
    bool flag = false;
    
    for(int i=1; i<=n; i++){
        long long p;
        scanf("%lld", &p);
        len[i] = p;
        if(p <= l){
            flag = false;
        }
        else{
            if(!flag){
                ngroups++;
                flag = true;
            }
        }
    }

    for(int i=0; i<m; i++){
        int c;
        scanf("%d", &c);
        if(c == 0)
            printf("%d\n", ngroups);
        else{
            int x, y;
            scanf("%d %d", &x, &y);
            if(len[x] + y > l && len[x] <= l){
                long long len_left = len[x-1];
                long long len_right = len[x+1];

                if(len_left <= l && len_right <= l)
                    ngroups++;
                else if(len_left > l && len_right > l)
                    ngroups--;
            }
            len[x] += y;
        }
    }
}