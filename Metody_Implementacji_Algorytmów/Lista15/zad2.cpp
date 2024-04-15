#include <bits/stdc++.h>
#include <math.h>
using namespace std;

long long dist(int x1, int y1, int x2, int y2){
    long long l1 = x1-x2;
    long long l2 = y1-y2;
    return l1*l1 + l2*l2;
}

bool is_triangle(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){
    return x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2) != 0;
}

int main(){
    long long x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    if(!is_triangle(x1, y1, x2, y2, x3, y3))
        cout << "No" << endl;
    else{
        long long l1, l2;
        l1 = dist(x1, y1, x2, y2);
        l2 = dist(x2, y2, x3, y3);
        if(l1 == l2)
            cout << "YeS" << endl;
        else
            cout << "No" << endl;
    }
}

