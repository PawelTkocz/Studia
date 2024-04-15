#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    int tab[n];
    for(int i=0; i<n; i++){
        int b;
        cin >> b;
        tab[i] = b;
    }
    for(int i=0; i<n; i++){
        int next = tab[i]-1;
        if(next == i)
            continue;
        int next2 = tab[next]-1;
        if(tab[next2]-1 == i){
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}