#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        int a, b, c;
        cin >> a >> b >> c;
        int second = c/2 + b;
        int first = c - c/2 + a;
        if(first > second)
            cout << "First" << endl;
        else
            cout << "Second" << endl;
    }
}

