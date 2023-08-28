#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

double f(double x){
    return pow(M_E, 2*x);
}

double f_d(double x){
    return 2*pow(M_E, 2*x);
}

double g(double x){
    return log(x)*log(x);
}

double g_d(double x){
    return 2*log(x)/x;
}

double h(double x){
    return (2*x-3)/(x*x*x+x*x-x);
}

double h_d(double x){
    return (-4*pow(x, 3)+7*x*x+6*x-3)/(x*x*pow((x*x+x-1) ,2));
}

double k(double x){
    return x*pow(3, x);
}

double k_d(double x){
    return pow(3, x)*(x*log(3)+1);
}

double derivative_1(double (*fun)(double), double x, double h){
    return ((*fun)(x+h) - (*fun)(x))/h;
}

double derivative_2(double (*fun)(double), double x, double h){
    return ((*fun)(x+h) - (*fun)(x-h))/(2*h);
}


int main(){

    double (*functions[])(double) = {f, g, h, k};
    double (*derivatives[])(double) = {f_d, g_d, h_d, k_d};
    double points[] = {0.5, 1.4, 1.1, 8.2};

    for(int i=0; i<4; i++){
        printf("Pochodna funkcji nr %d w punkcie x=%lf\n", i+1, points[i]);
        printf("Poprawna wartosc: %lf\n", (derivatives[i])(points[i]));
        printf("Przyblizenia:\n");
        printf("h(=2^n) Metoda 1     Metoda 2\n");
        for(int j=0; j<55; j++){
            printf("%d.      %lf      %lf\n",
                   j,
                   derivative_1((*functions[i]), points[i], pow(2, (-1*j))),
                   derivative_2((*functions[i]), points[i], pow(2, (-1*j))));
        }
    }
}

