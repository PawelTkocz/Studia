#include <bits/stdc++.h>
using namespace std;

bool is_automaton(string s, string t){
    int ind_t = 0;
    int ind_s = 0;
    while(ind_s < s.length()){
        if(s[ind_s] == t[ind_t])
            ind_t++;
        ind_s++;
        if(ind_t == t.length())
            return true;
    }
    return false;
}

bool is_arrayf(string s, string t){
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s==t;
}

bool is_both(string s, string t){
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return is_automaton(s, t);
}

int main(){
    string s, t;
    cin >> s >> t;
    if(is_automaton(s, t))
        cout<<"automaton"<<endl;
    else if(is_arrayf(s, t))
        cout<<"array"<<endl;
    else if(is_both(s, t))
        cout<<"both"<<endl;
    else
        cout<<"need tree"<<endl;
}