#include <stdio.h>
#include <stdlib.h>

long long maks(long long a, long long b){
    if(a>b)
        return a;
    return b;
}

void max_from_up(int k, long long *up, long long *down){
    if(up[1] > 0)
        down[0] += up[1];
    else
        down[0] = -1;
    if(up[k-2] > 0)
        down[k-1] += up[k-2];
    else
        down[k-1] = -1;
    for(int i=1; i<k-1; i++)
        down[i] += maks(up[i-1], up[i+1]);
}

void max_from_down(int k, long long *up, long long *down, int *vals){
    long long r, l;
    for(int i=0; i<k; i++){
        r = (i+2<k) ? down[i+2] + vals[i] : 0;
        l = (i-2>=0) ? down[i-2] + vals[i] : 0;
        up[i] = maks(maks(r, l), up[i]);
    }
}

long long max_in_tab(int k, long long *tab){
    long long res = tab[0];
    for(int i=1; i<k; i++)
        if(tab[i]>res)
            res = tab[i];
    return res;
}

void change_order(int *tab){
    for(int i=0; i<3; i++)
        tab[i] = (tab[i]+1)%3;
}

int main(){
    int powers[10] = {1, 7, 49, 343, 2401, 16807, 117649, 823543, 5764801, 40353607};

    int w, k;
    scanf("%d %d", &w, &k);

    int v[3][k];
    int *vals[3] = {&v[0][0], &v[1][0], &v[2][0]};
    long long r[3][k];
    long long *rows[3] = {&r[0][0], &r[1][0], &r[2][0]};

    int row_order[3] = {0, 1, 2};
    char row[k+2];
    fgets(row, 2, stdin);

    for(int i=0; i<2; i++){
        fgets(row, k+2, stdin);
        long long *ptr = rows[i];
        int *vptr = vals[i];
        for(int j=0; j<k; j++){
            ptr[j] = powers[row[j]-'0'];
            vptr[j] = ptr[j];
        }
    }
    if(k==3){
        r[1][1] = -1;
        v[1][1] = -1;
    }

    for(int i=2; i<w; i++){
        fgets(row, k+2, stdin);
        long long *ptr0 = rows[row_order[0]];
        long long *ptr1 = rows[row_order[1]];
        long long *ptr2 = rows[row_order[2]];
        int *v1 = vals[row_order[1]];
        int *v2 = vals[row_order[2]];

        for(int j=0; j<k; j++){
            v2[j] = powers[row[j]-'0'];
            ptr2[j] = v2[j];
        }
        max_from_up(k, ptr0, ptr2);
        max_from_down(k, ptr1, ptr2, v1);
        change_order(row_order);
    }

    long long res = max_in_tab(k, rows[row_order[1]]);
    printf("%lld\n", res);
}