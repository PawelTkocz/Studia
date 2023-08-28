#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f_double(double x){
    return (x - sin(x))/pow(x, 3)*12132;
}

float f_float(float x){
    return (x - sinf(x))/powf(x, 3)*12132;
}

int main(){
    printf("single:\n");
    for(int i=11; i<=20; i++)printf("%d. %.60f\n", i, f_float(powf(10.0, -1*i)));
    printf("double:\n");
    for(int i=11; i<=20; i++)printf("%d. %.60f\n", i, f_double(pow(10.0, -1*i)));
}
