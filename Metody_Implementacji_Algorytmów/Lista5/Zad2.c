#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int cmpf(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

bool check(int *tab, int k, int s, int n){
    long long tab2[n];
    for(long long i=0; i<n; i++){
        tab2[i] = (long long)tab[i] + (i+1)*k;
    }
    qsort(tab2, n, sizeof(long long), cmpf);
    long long sum = 0;
    for(int i=0; i<k; i++){
        sum += tab2[i];
        if(sum > s)
            return false;
    }
    return true;
}

long long getsum(int *tab, int k, int n){
    int tab2[n];
    //
    for(int i=0; i<n; i++){
        tab2[i] = tab[i] + (i+1)*k;
    }
    qsort(tab2, n, sizeof(int), cmpf);
    long long sum = 0;
    for(int i=0; i<k; i++){
        sum += tab2[i];
    }
    return sum;
}

int main(){
    int n, s;
    scanf("%d %d", &n, &s);
    int tab[n];
    for(int i=0; i<n; i++){
        scanf("%d", &tab[i]);
    }
    int b = 0;
    int e = n;
    while(b <= e){
        int m = (b+e)/2;
        if(check(tab, m, s, n)){
            b = m+1;
        }
        else{
            e = m-1;
        }
    }
    long long sum = getsum(tab, b-1, n);
    printf("%d %lld", b-1, sum);
}

