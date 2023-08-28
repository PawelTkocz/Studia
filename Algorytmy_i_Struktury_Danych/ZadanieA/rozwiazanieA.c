#include <stdio.h>
#include <stdlib.h>

long long min(long long a, long long b){
    if(a>b)
        return b;
    else
        return a;
}

int main(){
    int n;
    scanf("%d", &n);
    int odl[n];
    int d;
    long long suma = 0;
    for(int i=0; i<n; i++){
        scanf("%d", &d);
        odl[i] = d;
        suma += d;
    }


    long long d_r = 0;
    long long dist;
    long long d_max = -1;
    long long d_max_r = -1;
    int ind_max = -1;
    for(int i=0; i<n-1; i++){
        d_r += odl[i];
        dist = min(suma-d_r, d_r);
        if(dist > d_max){
            d_max = dist;
            d_max_r = d_r;
            ind_max = i+1;
        }
    }


    int p1 = 0;
    int p2 = ind_max;
    d_r = d_max_r;
    long long new_d;

    while(p1<ind_max && p2<n){
        d_r = d_r - odl[p1];
        dist = min(d_r, suma - d_r);
        while(p2 < n){
            d_r = d_r + odl[p2];
            new_d = min(d_r, suma-d_r);
            if(new_d>dist){
                dist = new_d;
                p2++;
            }
            else{
                d_r -= odl[p2];
                break;
            }
        }
        if(dist > d_max)
            d_max = dist;
        p1++;
    }
    printf("%lld\n", d_max);
}