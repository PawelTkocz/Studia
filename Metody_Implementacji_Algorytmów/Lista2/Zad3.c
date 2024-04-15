#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int find_first(int n, int p, char s[n]){
    for(int i=n-1; i>=2; i--){
        for(char c=s[i]+1; c<'a'+p; c++){
            if(s[i-1] != c && s[i-2] != c){
                s[i] = c;
                return i;
            }
        }
    }
    if(n>=2){
        for(char c=s[1]+1; c<'a'+p; c++){
            if(s[0] != c){
                s[1] = c;
                return 1;
            }
        }
    }
    if(s[0]+1 >= 'a'+p)
        return -1;
    s[0]++;
    if(n!=1)
        s[1] = 'a';
    return 1;
}

int main(){
    int n, p;
    scanf("%d %d\n", &n, &p);
    char s[n];
    scanf("%s", s);
    int ind = find_first(n, p, s);
    if(ind == -1){
        printf("NO\n");
        return 0;
    }
    for(int i=ind+1; i<n; i++){
        for(char c='a'; c<'a'+p; c++){
            if(s[i-1] != c && s[i-2] != c){
                s[i] = c;
                break;
            }
        }
    }
    printf("%s\n", s);
    return 0;
}

