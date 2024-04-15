#include <bits/stdc++.h>
using namespace std;

int main(){
    string a;
    cin >> a;
    long long cnt = 0;
    int len = a.length();
    for(int i=len-1; i>0; i--){
        int dig1 = a[i]-'0';
        if(dig1 % 4 == 0)
            cnt++;
        int dig2 = a[i-1]-'0';
        if(10*dig2+dig1 % 4 == 0)
            cnt+=i+1;
    }
    printf("%lld\n", cnt);
}
