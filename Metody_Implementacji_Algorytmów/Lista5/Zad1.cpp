#include <bits/stdc++.h>
using namespace std;

int binsearch(int *tab, int a, int s, int e){
    while(s+1<e){
        int m = (e+s)/2;
        if(tab[m] <= a)
            s = m;
        else
            e = m;
    }
    return e;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int tab1[n];
    int tab2[m];

    for(int i=0; i<n; i++){
        scanf("%d", &tab1[i]);
    }
    sort(tab1, tab1+n);
    for(int i=0; i<m; i++){
        scanf("%d", &tab2[i]);
    }

    for(int i=0; i<m; i++){
        printf("%d ", binsearch(tab1, tab2[i], -1, n));
    }

}

