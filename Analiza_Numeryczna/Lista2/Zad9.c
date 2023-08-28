#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f_v1(double x){
    return 12132.0 * (x-sin(x))/pow(x, 3);
}

double f_v2(double x){
    //sin(x) = 1-x^2/3!+x^4/5!-x^6/7!+...
    double suma = 1 - pow(x, 2)/20.0 + pow(x, 4)/840.0 - pow(x, 6)/75600.0;
    return 2022.0*suma;
}

double f_v3(double x){
    //limes
    return 2022.0*cos(x);
}

int main(){
    for(int k=11; k<=20; k++){
        double arg = pow(10.0, -1*k);
        printf("%d. %.14f          %.14f          %.14f\n", k, f_v1(arg), f_v2(arg), f_v3(arg));
    }
    return 0;
}
