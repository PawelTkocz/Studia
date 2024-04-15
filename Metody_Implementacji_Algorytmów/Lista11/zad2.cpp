#include <bits/stdc++.h>
using namespace std;


int main(){
    int n, q;
    cin >> n >> q;
    
    int tab[n];
    for(int i=0; i<n; i++){
        int k;
        cin >> k;
        tab[i] = k;
    }
    int freq[n];
    for(int i=0; i<n; i++)
        freq[i] = 0;

    for(int i=0; i<q; i++){
        int x, y;
        cin >> x >> y;
        for(int j=x-1; j<y; j++)
            freq[j]++;
    }

    sort(freq, freq+n);
    sort(tab, tab+n);

    int sum=0;
    for(int i=0; i<n; i++){
        sum+= freq[i]*tab[i];
    }
    cout<<sum;
}