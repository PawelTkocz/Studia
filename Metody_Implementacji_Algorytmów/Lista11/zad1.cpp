#include <bits/stdc++.h>
using namespace std;


int main(){
    int n;
    cin >> n;
    int top = n;
    int tab[n+1];
    for(int i=0; i<n+1; i++)
        tab[i] = 0;
    for(int i=n; i>0; i--){
        int k;
        cin >> k;
        tab[k] = 1;
        while(top >=0 && tab[top] == 1){
            cout << top << " ";
            top--;
        }
        cout << endl;
    }
}