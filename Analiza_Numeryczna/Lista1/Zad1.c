#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x){
    double x_pow_13 = pow(x, 13);
    return (sqrt(x_pow_13 + 1) - 1)*4044/x_pow_13;
}

int main(){
    double x = 0.001;
    printf("%lf", f(x));
}
