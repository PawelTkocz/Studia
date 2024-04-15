#include <bits/stdc++.h>
using namespace std;

int main(){
    int k;
    cin >> k;
    long long cnt = 1;
    int colors[k];
    int balls_left = 0;
    for(int i=0; i<k; i++){
        int n;
        cin>>n;
        colors[i] = n;
        balls_left += n;
    }
    
    long long newtons[1001][1001];
    for(int i=0; i<1001; i++){
        for(int j=i; j<1001; j++){
            if(j==i || i==0)
                newtons[i][j] = 1;
            else
                newtons[i][j] = (newtons[i][j-1] + newtons[i-1][j-1])%1000000007;
        }
    }
    
    for(int i=k-1; i>=0; i--){
        cnt *= newtons[colors[i] - 1][balls_left-1];
        cnt %= 1000000007;
        balls_left-=colors[i];
    }
    cout << cnt;
}