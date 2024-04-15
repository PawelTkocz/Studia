#include <bits/stdc++.h>
using namespace std;

long long newton(int n, int k){
    double res = 1;
    for(int i = 1; i <= k; i++){
        res = res * (n - i + 1 ) / i;
    }
    return (long long)res;
}

int main(){
    string a, b;
    cin >> a >> b;
    int a_cnt = 0;
    int b_cnt = 0;
    int unkn = 0;
    for(int i=0; i<a.length(); i++){
        if(a[i] == '-')
            a_cnt--;
        else
            a_cnt++;

        if(b[i] == '-')
            b_cnt--;
        else if(b[i] == '+')
            b_cnt++;
        else
            unkn++;
    }    
    int diff = b_cnt-a_cnt;
    double res = 0.0;
    long long possib = 0;
    for(int i=0; i<=unkn; i++){
        if(unkn-2*i == diff){
            possib += newton(unkn, i);
        }
    }
    res = (double)possib/pow(2, unkn);
    printf("%.12lf", res);
    return 0;
}

