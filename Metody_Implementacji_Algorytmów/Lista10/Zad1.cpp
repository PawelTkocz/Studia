#include <bits/stdc++.h>
using namespace std;

void print_mirror(string a, int k){
    for(int i=0; i<k+1; i++)
        cout<<a[i];
    for(int i=k; i>=0; i--)
        cout<<a[i];
    cout << endl;
}

int main(){
    int n;
    cin >> n;

    for(int i=0; i<n; i++){
        int len;
        string a;
        cin>>len;
        cin>>a;
        int mini = 0;
        char prev = a[0];
        if(len >= 2 && a[1] == prev)
            mini = 0;
        else{
            for(int j=1; j<len; j++){
                if(a[j] > prev){
                    mini = j-1;
                    break;
                }
                prev = a[j];
                mini = j;
            }
        }
        print_mirror(a, mini);
    }
}