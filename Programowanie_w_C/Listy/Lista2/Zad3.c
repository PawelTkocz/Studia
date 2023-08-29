#include <stdio.h>

//Pawel Tkocz 332168

int main(){
    int m;
    int s;
    int n;
    scanf("%d %d %d", &m, &s, &n);
    int wejscie[n];
    int wyjscie[n];
    for(int i=0; i<n; i++){
        int we, wy;
        scanf("%d %d", &we, &wy);
        wejscie[i]=we;
        wyjscie[i]=wy;
    }
    int ob_pietro=0;
    int kierunek=1;
    int osob=0;
    for(int i=0; i<s; i++){
        osob-=wyjscie[ob_pietro];
        if(osob<0){
            osob=0;
        }
        osob+=wejscie[ob_pietro];
        if(osob>m){
            osob=m;
        }
        ob_pietro+=kierunek;
        if(ob_pietro==n-1){
            kierunek=-1;
        }
        if(ob_pietro==0){
            kierunek=1;
        }
    }
    osob-=wyjscie[ob_pietro];
    if(osob<0){
        osob=0;
    }
    printf("%d %d", ob_pietro, osob);
    return 0;
}
