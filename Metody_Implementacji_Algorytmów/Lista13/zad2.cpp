#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    int tab[n];
    int tabsort[n];
    for(int i=0; i<n; i++){
        cin >> tab[i];
        tabsort[i] = tab[i];
    }
    sort(tabsort, tabsort+n);

    long long part1[n];
    long long part2[n];
    part1[0] = tab[0];
    part2[0] = tabsort[0];
    for(int i=1; i<n; i++){
        part1[i] = tab[i] + part1[i-1];
        part2[i] = tabsort[i] + part2[i-1];
    }

    int k;
    cin >> k;
    for(int i=0; i<k; i++){
        int a, b, c;
        cin >> a >> b >> c;
        if(a == 1){
            if(b == 1)
                cout << part1[c-1] << endl;  
            else{
                long long res = part1[c-1] - part1[b-2];
                cout << res << endl;
            }          
        }
        else{
            if(b == 1)
                cout << part2[c-1] << endl;
            else{
                long long res = part2[c-1] - part2[b-2];
                cout << res << endl;
            }
        }
    }
}