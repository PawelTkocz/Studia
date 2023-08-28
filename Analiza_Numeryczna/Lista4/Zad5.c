#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double next(double x, double r){
    return x * (2 - x*r);
}

int main(){
    double r;
    double x0;
    double x;
    double e = pow(10, -16);
    int n;
    int testow = 100;
    int suma = 0;

    srand(time(NULL));
    for(int i=0; i<testow/2; i++){
        r = rand() % 1000 + 1;
        x0 = (double)(rand() % 1000 + 1.0) / 1000 / r;
        n = 0;
        x = x0;
        while(fabs(x - 1.0/r)>e){
            n++;
            x = next(x, r);
        }
        suma += n;
    }

    e = pow(10, -14);
    for(int i=0; i<testow/2; i++){
        r = (double)(rand() % 1000 + 1.0) / 1002;
        x0 = 0.5;
        n = 0;
        x = x0;
        while(fabs(x - 1.0/r)>e){
            n++;
            x = next(x, r);
        }
        suma += n;
    }
    printf("srednia liczba potrzebnych iteracji to %lf\n", (double)suma/testow);
}
