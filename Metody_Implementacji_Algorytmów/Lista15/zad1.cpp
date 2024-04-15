#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        int x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        int sum = 0.0;
        if(y1 == y2 && y3 < y1)
            sum = abs(x1-x2);
        else if(y1 == y3 && y2 < y1)
            sum = abs(x1-x3);
        else if(y3 == y2 && y1 < y2)
            sum = abs(x3-x2);
        cout << sum << endl;
    }
}

