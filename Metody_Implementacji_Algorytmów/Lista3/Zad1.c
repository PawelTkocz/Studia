#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    int t;
    scanf("%d\n", &t);
    char name[4] = "vika";
    for(int i=0; i<t; i++){
        int n, m;
        scanf("%d %d\n", &n, &m);
        char carpet[n][m];
        for(int j = 0; j<n; j++){
            scanf("%s", carpet[j]);
        }
        int cnt = 0;
        bool found = false;
        for(int j=0; j<m; j++){
            for(int k=0; k<n; k++){
                if(carpet[k][j] == name[cnt]){
                    cnt++;
                    if(cnt == 4){
                        found = true;
                    }
                    break;
                }
            }
            if(found == true)
                break;
        }
        if(found)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

