#include <stdio.h>

//Paweł Tkocz 332168
int main(){
    //pierwsze znaki na kazdym z bebnow
    int offset[4]={' ', '@', '`', 'a'};
    //liczba znakow na poszczegolych bebnach
    int len[4];
    len[0]='?'-offset[0]+1;
    len[1]='_'-offset[1]+1;
    len[2]='~'+1-offset[2]+1;
    len[3]='z'-offset[3]+1;
    //aktualna pozycja kazdego z bebnow
    int beben[4];
    beben[0]='$'-offset[0];
    beben[1]='U'-offset[1];
    beben[2]='m'-offset[2];
    beben[3]='o'-offset[3];

    int akt_beben=0;
    int a=getchar();
    while(a != EOF){
        if(a=='.'){
            int k=offset[akt_beben]+beben[akt_beben];
            printf("%c", k);
        }
        else if(a=='>'){
            akt_beben=(akt_beben+1)%4;
        }
        else if(a=='<'){
            akt_beben=(akt_beben-1);
            if(akt_beben==-1){
                akt_beben=3;
            }
        }
        else if(a=='^'){
            beben[akt_beben]=(beben[akt_beben]+1)%len[akt_beben];
        }
        else if(a=='v'){
            beben[akt_beben]=beben[akt_beben]-1;
            if(beben[akt_beben]<0)
                beben[akt_beben]=len[akt_beben]-1;
        }
        else{
            printf("\n");
        }
        a=getchar();
    }

    return 0;
}



