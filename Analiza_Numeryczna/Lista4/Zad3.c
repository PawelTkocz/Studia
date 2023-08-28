#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x){
    return x - 0.49;
}

double en(double x0, double a, double b){
    return fabs(x0 - (a + b)/2);
}

double en_szac(int n, double a0, double b0){
    return (b0-a0)/pow(2, n+1);
}

int main(){
    double a0 = 0.0;
    double b0 = 1.0;
    double a = a0;
    double b = b0;
    double x0 = 0.49;
    for(int i=0; i<5; i++){
        double m = (a + b)/2;
        if(f(m) == 0){
            printf("Miejsce zerowe to x=%lf\n", m);
            break;
        }
        if(f(m)*f(a)>0)
            a = m;
        else
            b = m;
        printf("%d. [%lf, %lf]\n", i+1, a, b);
        printf("|e%d| = %lf\n", i+1, en(x0, a, b));
        printf("|e%d| <= %lf\n", i+1, en_szac(i+1, a0, b0));
    }
    return 0;
}
