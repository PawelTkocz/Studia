#include <stdio.h>

//Pawel Tkocz 332168
int main(){
    int s=32;
    int m=64;
    char key[1000];
    int ini=-1;
    int koniec =0;
    char kom[3];
    char tekst[129];
    char a;
    while(koniec==0){
        for(int i=0; i<3; i++){
            a=getchar();
            if(a==EOF){
                koniec=1;
                kom[0]=0;
                i=3;
            }
            else{
                kom[i]=a;
            }
        }
        if(koniec==0){
            a=getchar();
        }
        if(kom[0]=='C' && kom[1]=='F' && kom[2]=='G'){
            scanf("%d %d", &s, &m);
            a=getchar();
        }
        else if(kom[0]=='K' && kom[1]=='E' && kom[2]=='Y'){
            for(int i=0; i<m; i++){
                a=getchar();
                key[i]=a;
                if(a<s || a>=s+m){
                    return 0;
                }
            }
            a=getchar();
        }
        else if(kom[0]=='I' && kom[1]=='N' && kom[2]=='I'){
            scanf("%d", &ini);
            a=getchar();
        }
        else if(kom[0]=='E' && kom[1]=='N' && kom[2]=='C'){
            if(ini==-1){
                return 0;
            }
            int dl=0;
            for(int i=0; i<129; i++){
                a=getchar();
                if(a=='\n'){
                    tekst[i]=0;
                    dl=i;
                    i=129;
                }
                else{
                    tekst[i]=a;
                    if(a<s || a>=s+m){
                        return 0;
                    }
                }
            }
            int b=(tekst[0]-s+ini)%m;
            printf("%c", key[b]);
            int poprz=key[b];
            for(int i=1; i<dl; i++){
                int k=(tekst[i]-s+poprz-s)%m;
                printf("%c", key[k]);
                poprz=key[k];
            }
            printf("\n");
        }
        else if(kom[0]=='D' && kom[1]=='E' && kom[2]=='C'){
            if(ini==-1){
                return 0;
            }
            int dl;
            for(int i=0; i<129; i++){
                a=getchar();
                if(a=='\n'){
                    tekst[i]=0;
                    dl=i;
                    i=129;
                }
                else{
                    tekst[i]=a;
                    if(a<s || a>=s+m){
                        return 0;
                    }
                }
            }
            int p;
            for(int i=0; i<m; i++){
                if(key[i]==tekst[0]){
                    p=i;
                    i=m;
                }
            }
            int b=(p-ini)%m;
            if(b<0){
                b+=m;
            }
            int li=s+b;
            printf("%c", li);
            int poprz=tekst[0]-s;
            for(int i=1; i<dl; i++){
                for(int j=0; j<m; j++){
                    if(key[j]==tekst[i]){
                        p=j;
                        j=m;
                    }
                }
                int k=(p-poprz)%m;
                if(k<0){
                    k+=m;
                }
                li=s+k;
                printf("%c", li);
                poprz=tekst[i]-s;
            }
            printf("\n");
        }
    }
    return 0;
}
