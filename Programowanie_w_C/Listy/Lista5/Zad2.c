#include <stdio.h>
#include <string.h>
#define MAX_HASH 100000
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
    char words[MAX_HASH][60];
    for(int i=0; i<MAX_HASH; i++){
        for(int j=0; j<60; j++){
            words[i][j]=0;
        }
    }
    int kolizji=0;
    int roznych_slow=0;
    int najcz_ind=0; //przechowuje informacje w ktorym wierszu tabeli words znajduje sie najczesciej wystepujace slowo
    int najcz_ile=1; //przechowuje informacje ile razy pojawia sie najczesciej wystepujace slowo
    int wystapienia[MAX_HASH]={0};
    char s[60];
    scanf("%s", s);
    while(!feof(stdin)){
        hash_t h=hash(s);
        if(words[h][0]==0){
            for(int i=0; i<60; i++){
                words[h][i]=s[i];
                if(s[i]==0)i=60;
            }
            wystapienia[h]=1;
            roznych_slow++;
            if(najcz_ile==1)najcz_ind=h;
        }
        else{
            if(strncmp(s, words[h], 60)==0){
                wystapienia[h]++;
                if(wystapienia[h]>najcz_ile){
                    najcz_ile=wystapienia[h];
                    najcz_ind=h;
                }
            }
            else{
                kolizji++;
            }
        }
        scanf("%s", s);
    }
    printf("roznych slow: %d\n", roznych_slow);
    printf("kolizji: %d\n", kolizji);
    printf("najczestsze slowo: %s\n", words[najcz_ind]);
    printf("liczba wystapien tego slowa: %d\n", najcz_ile);

    return 0;
}

