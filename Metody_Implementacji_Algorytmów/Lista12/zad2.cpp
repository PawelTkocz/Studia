#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        int k;
        cin >> k;
        bool f = false;
        int cnt = 0;
        for(int j=0; j<k; j++){
            int p;
            cin >> p;
            if(p == 1 && f==false)
                cnt++;
            else
                f = true;
        }
        if(f){
            if(cnt%2==0)
                cout << "First" << endl;
            else
                cout << "Second" << endl;
        }
        else{
            if(cnt%2==0)
                cout << "Second" << endl;
            else
                cout << "First" << endl;
        }
    }
}

