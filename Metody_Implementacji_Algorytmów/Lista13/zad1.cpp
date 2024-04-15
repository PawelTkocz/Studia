#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    int tab[1000001];
    for(int i=0; i<1000001; i++)
        tab[i] = 0;
    for(int i=0; i<=1000; i++)
        tab[i*i] = 1;

    int k;
    int maxi = -1000001;
    int min_neg = -1000001;
    for(int i=0; i<n; i++){
        cin >> k;
        if(k < 0){
            if(min_neg < k)
                min_neg = k;
        }
        else if(tab[k] == 0 && maxi < k)
            maxi = k;
    }
    if(maxi > 0)
        cout << maxi << endl;
    else
        cout << min_neg << endl;
}

