#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main(){

    float sum_f=0.0;
    for(int i=0; i<2000000; i+=2){
        sum_f += 4.0/(2*i+1);
        sum_f -= 4.0/(2*i+3);
    }
    printf("Float:\n");
    printf("Pi = %.7f\n", M_PI);
    printf("Suma = %.7f\n", sum_f);
    printf("Wielkosc bledu: %.7f\n", fabs(M_PI-sum_f));

    double sum_d=0.0;
    for(int i=0; i<2000000; i+=2){
        sum_d += 4.0/(2*i+1);
        sum_d -= 4.0/(2*i+3);
    }
    printf("Double:\n");
    printf("Pi = %.7f\n", M_PI);
    printf("Suma = %.7f\n", sum_d);
    printf("Wielkosc bledu: %.7f\n", fabs(M_PI-sum_d));
}

