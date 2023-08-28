#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592653589793238462643

double f(double x){
    return pow(x, 4) - 6*sin(3*x-1);
}

int n_krokow(double e, double a0, double b0){
    double v = (b0-a0)/(2*e);
    return floor(log(v)/log(2)) + 1;
}

double bisekcja(double a, double b, double e){
    int n = n_krokow(e, a, b);
    for(int i=0; i<n; i++){
        double m = (a + b)/2;
        if(f(m) == 0)
            return m;
        if(f(m)*f(a)>0)
            a = m;
        else
            b = m;
    }
    return (a+b)/2;
}

int main(){
    double e = pow(10, -8);
    printf("x0 = %.9f\n", bisekcja(-1*pow(6, 0.25), (2-3*PI)/6, e));
    printf("x1 = %.9f\n", bisekcja((2-3*PI)/6, (1.0-PI)/3, e));
    printf("x2 = %.9f\n", bisekcja(1/pow(3, 4), 1.0/3+PI/6, e));
    printf("x3 = %.9f\n", bisekcja(1.0/3+PI/6, 1.0/3 + PI/3, e));
    return 0;
}
