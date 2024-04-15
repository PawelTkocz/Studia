#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n;
    cin >> m;
    int cnt[n+1];
    for(int i=0; i<n+1; i++){
        cnt[i] = 0;
    }
    for(int i=0; i<m; i++){
        int x, y;
        cin >> x;
        cin >> y;
        cnt[x]++;
        cnt[y]++;
    }
    
    int twos = 0;
    int ones = 0;
    for(int i=1; i<n+1; i++){
        if(cnt[i] == n-1 && m == n-1){
            cout << "star topology";
            return 0;
        }
        if(cnt[i] == 1)
            ones++;
        else if(cnt[i] == 2)
            twos++;
        else{
            cout << "unknown topology";
            return 0;
        }
    }
    if(ones == 2 && twos == n-2)
        cout << "bus topology";
    else if(twos == n)
        cout << "ring topology";
    else
        cout << "unknown topology";
}