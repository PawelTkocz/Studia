#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sort(int n, double tab[n], int index[n]){
    for(int i=0; i<n-1; i++){
        double min_v = tab[i];
        int min_ind = i;
        for(int j=i+1; j<n; j++){
            if(tab[j]<min_v){
                min_v = tab[j];
                min_ind = j;
            }
        }
        double pom = tab[i];
        tab[i] = min_v;
        tab[min_ind] = pom;
        int pom2 = index[i];
        index[i] = index[min_ind];
        index[min_ind] = pom2;
    }
}

void calculate(int n, int tab[n], int *a, int *b, int *d){
    int s = -1;
    if(tab[0]==0)
        s = 1;
    int c = tab[n-1];
    *a = 0;
    if(c == 1) *a = 1;
    *b = 0;
    *d = 0;
    for(int i=n-2; i>0; i--){
        if(tab[i]==1){
            if(*d==0){
                *d = pow(2, i+1-c);
                *b = 1;
            }
            else{
                *b += *d/pow(2, i+1-c);
            }
        }
    }
    if(*d==0){
        if(c==-1){
            *b = 1;
            *d = 4;
        }
        if(c==0){
            *b = 1;
            *d = 2;
        }
        if(c==1){
            *b = 0;
            *d = 1;
        }
    }
    else{
        if(c==-1){
            *b += *d/4;
        }
        if(c==0){
            *b += *d/2;
        }
    }
    *d *= s;
}

int get_pos(int n, int tab[n]){
    int res= pow(2, n-1) * (tab[n-1] + 1);
    int x = 1;
    for(int i=0; i<n-1; i++){
        res += tab[i]*x;
        x*=2;
    }
    return res;
}

void f(int n, int i, int tab[n], double res[]){
    if(i==n){
        int a, b, c;
        int pos = get_pos(n, tab);
        calculate(n, tab, &a, &b, &c);
        int r = pow(2, n-1)*3;
        res[pos] = a;
        res[pos+r] = b;
        res[pos+2*r] = c;
    }
    else if(i==n-1){
        //wykladnik
        tab[i] = -1;
        f(n, i+1, tab, res);
        tab[i] = 0;
        f(n, i+1, tab, res);
        tab[i] = 1;
        f(n, i+1, tab, res);
    }
    else{
        tab[i] = 0;
        f(n, i+1, tab, res);
        tab[i] = 1;
        f(n, i+1, tab, res);
    }
}

int main(){
    int n = 6;
    int r = pow(2, n-1) * 3;
    int tab[n];
    double res[r*3];
    f(n, 0, tab, res);
    double res2[r];
    int index[r];
    for(int i=0; i<r; i++){
        index[i] = i;
        int a = res[i];
        int b = res[r+i];
        int c = res[2*r+i];
        if(c<0)res2[i] = -1*a + (double)b/(double)c;
        else res2[i] = a + (double)b/(double)c;
    }
    sort(r, res2, index);
    for(int i=0; i<r; i++){
        printf("%lf\n", res2[i]);
    }
    printf("Najmniejszy przedzial to [%lf, %lf]\n", res2[0], res2[r-1]);
    printf("Te same wartosci zapisane jako liczby mieszane:\n");
    for(int i=0; i<r; i++){
        int a = res[index[i]];
        int b = res[index[i]+r];
        int c = res[index[i]+2*r];
        if(c<0)
            printf("-");
        if(a!=0)
            printf("%d ", a);
        if(b!=0)
            printf("%d/%d", b, abs(c));
        printf("\n");
    }
    return 0;
}


