#include <stdio.h>
#define MAX_HASH 100
typedef long long unsigned int hash_t;

hash_t hash(char word[]){
    hash_t h=0;
    int zn=0;
    while(word[zn]!=0){
        int c=word[zn];
        h*=257;
        h+=c;
        h=h%MAX_HASH;
        zn++;
    }
    return h;
}

int main(){
    hash_t tab[MAX_HASH]={0};
    char s[60];
    scanf("%s", s);
    while(!feof(stdin)){
        hash_t h=hash(s);
        tab[h]++;
        scanf("%s", s);
    }
    for(int i=0; i<MAX_HASH; i++){
        printf("%lld\n", tab[i]);
    }
    return 0;
}
