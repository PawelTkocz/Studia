#include <stdio.h>

int main(){
    int n, m, a, t;
    scanf("%d %d %d", &n, &m, &a);
    int akc[m];
    for(int i=0; i<m; i++){
        int x;
        scanf("%d", &x);
        akc[i]=x;
    }
    int tab[a][n];
    for(int i=0; i<a; i++){
        for(int j=0; j<n; j++){
            int x;
            scanf("%d", &x);
            tab[i][j]=x;
        }
    }
    scanf("%d", &t);
    for(int j=0; j<t; j++){
        int i;
        scanf("%d", &i);
        char x=getchar();
        x=getchar();
        while(x>='a' && x<'a'+a){
            i=tab[x-'a'][i];
            x=getchar();
        }
        printf("%d ", i);
        int ok=0;
        for(int k=0; k<m; k++){
            if(akc[k]==i){
                printf("ACCEPT\n");
                ok=1;
                k=m;
            }
        }
        if(ok==0) printf("REJECT\n");
    }
    return 0;
}
