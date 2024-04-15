#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        string first;
        cin >> first;
        int cnt = first.length();

        string second;
        cin >> second;
        int acnt = 0;
        bool withnota = false;
        for(int j=0; j<second.length(); j++){
            if(second[j] == 'a')
                acnt++;
            else
                withnota = true;
        }

        if(acnt == 0){
            cout<<(long long)pow(2.0L, cnt) << "\n";
        }
        else if(acnt == 1){
            if(withnota)
                cout<<"-1\n";
            else
                cout<<"1\n";
        }
        else{
            cout<<"-1\n";
        }
    }
}