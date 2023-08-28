#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f_v1(double x){
    return 4044.0 * (sqrt(pow(x, 13) + 1) - 1)/pow(x, 13);
}

double f_v2(double x){
    return 4044.0 / (sqrt(pow(x, 13)+1) + 1);
}

int main(){
    printf("%.10f\n", f_v1(0.001));
    printf("%10f\n", f_v2(0.001));
    return 0;
}
