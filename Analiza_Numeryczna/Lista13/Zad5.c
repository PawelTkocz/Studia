#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265358979323846

double fa(double x){
    return (2023.0*pow(x, 10)-1977.0*pow(x, 5)-1939.0);
}

double fb(double x){
    return 1.0/(1.0+x*x);
}

double fc(double x){
    return cos(2*x-M_PI/6);
}

void print_romberg(double tab[21][21]){
    for(int i=0; i<21; i++){
        printf("m=%d\n", i);
        for(int k=0; k<=20-i; k++){
            printf("%d. %.20f\n", k, tab[i+k][i]);
        }
    }
}

double t_2_pow_k(int k, double f(double), double a, double b){
    int n = pow(2, k);
    double h = (b-a)/n;
    double sum = 0.0;
    sum += (f(a) + f(b))/2.0;
    for(int i=1; i<n; i++){
        sum+=f(a+i*h);
    }
    return h*sum;
}

void oblicz(double a, double b, double f(double), double romberg[21][21]){
    for(int i=0; i<21; i++)
        romberg[i][0] = t_2_pow_k(i, f, a, b);

    for(int m=1; m<21; m++){
        for(int k=0; k<=20-m; k++){
            romberg[m+k][m] = (pow(4, m)*romberg[m+k][m-1] - romberg[m+k-1][m-1])/(pow(4, m)-1);
        }
    }
}

int main(){
    double romberg[21][21];
    oblicz(-3, 2, &fa, romberg);
    printf("\nPodpunkt a\n\n");
    printf("Poprawny wynik: 33165012,045454545454545454545455\n");
    print_romberg(romberg);
    oblicz(-5, 5, &fb, romberg);
    printf("\nPodpunkt b\n\n");
    printf("Poprawny wynik: 2.746801533890031721722543852889922\n");
    print_romberg(romberg);
    oblicz(-2*M_PI, M_PI/3, &fc, romberg);
    printf("\nPodpunkt c\n\n");
    printf("Poprawny wynik: 0.75");
    print_romberg(romberg);
}
