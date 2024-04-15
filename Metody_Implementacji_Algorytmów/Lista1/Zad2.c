#include <stdio.h>
#include <stdlib.h>


int main(){
    int n;
    scanf("%d", &n);
    int dices[n][6];
    for(int i=0; i<n; i++){
        for(int j=0; j<6; j++){
            int v;
            scanf("%d", &v);
            dices[i][j] = v;
        }
    }
    int numbers[1001];
    for(int i=0; i<1001; i++)
        numbers[i] = 0;

    for(int first=0; first<n; first++){
        for(int first_side = 0; first_side<6; first_side++){
            numbers[dices[first][first_side]] = 1;
            if(n==1)
                continue;
            for(int second=0; second<n; second++){
                if(first==second)
                    continue;
                for(int second_side=0; second_side<6; second_side++){
                    numbers[dices[first][first_side]*10 + dices[second][second_side]] = 1;
                    if(n==2)
                        continue;
                    int third = 3-first-second;
                    for(int third_side=0; third_side<6; third_side++)
                        numbers[dices[first][first_side]*100 + dices[second][second_side]*10 + dices[third][third_side]] = 1;
                }
            }
        }
    }

    for(int i=1; i<1001; i++){
        if(numbers[i] == 0){
            printf("%d\n", i-1);
            break;
        }
    }
    return 0;
}
