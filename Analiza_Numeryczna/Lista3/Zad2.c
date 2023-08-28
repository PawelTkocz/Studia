#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void metoda_1(double a, double b, double c, double *x1, double *x2){
    double delta = b*b-4*a*c;
    *x1 = (-1*b - sqrt(delta))/(2*a);
    *x2 = (-1*b + sqrt(delta))/(2*a);
}

void metoda_2(double a, double b, double c, double *x1, double *x2){
    double delta = b*b-4*a*c;
    if (b<0){
        *x1 = (-1*b + sqrt(delta))/(2*a);
        *x2 = c/(*x1*a);
    }
    else{
        *x1 = (-1*b - sqrt(delta))/(2*a);
        *x2 = c/(*x1*a);
    }
}

int main(){
    double a = 0.0001;
    double b = 100.0;
    double c = 0.015;
    double x1, x2;
    double y1, y2;

    printf("a = 0.0001\nb = 100.0\nc = 0.015\n");
    printf("Poprawny wynik x1: -0.0001500000000225000000067\n");
    metoda_1(a, b, c, &x1, &x2);
    metoda_2(a, b, c, &y1, &y2);
    printf("Metoda szkolna x1: %.25f\n", x2);
    printf("Metoda lepsza  x1: %.25f\n", y2);
    printf("Poprawny wynik x2: -999999.99984999999997749999\n");
    printf("Metoda szkolna x2: %.20f\n", x1);
    printf("Metoda lepsza  x2: %.20f\n", y1);
    printf("\n\n");
    a = 0.001;
    b = 100.1;
    c = 0.015;
    printf("a = 0.001\nb = 100.1\nc = 0.015\n");
    printf("Poprawny wynik x1: -0.0001498501500744761985748\n");
    metoda_1(a, b, c, &x1, &x2);
    metoda_2(a, b, c, &y1, &y2);
    printf("Metoda szkolna x1: %.25f\n", x2);
    printf("Metoda lepsza  x1: %.25f\n", y2);
    printf("Poprawny wynik x2: -100099.99985014984992552380\n");
    printf("Metoda szkolna x2: %.20f\n", x1);
    printf("Metoda lepsza  x2: %.20f\n", y1);

    return 0;
}


