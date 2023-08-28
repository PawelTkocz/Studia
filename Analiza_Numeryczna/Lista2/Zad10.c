#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979

double x_next_v1(double x, int k){
    return pow(2.0, k) * sqrt(2.0*(1.0 - sqrt(1.0 - pow((x/(pow(2.0, k))), 2))));
}

double x_next_v2(double x, int k){
    double y = x*x/(pow(4.0, k) * (1 + sqrt(1 - pow((x/pow(2.0, k)), 2))));
    return pow(2.0, k)*sqrt(2.0*y);
}

int main(){
    printf("PI = %.14f\n", PI);

    double cur_x_v1 = 2.0;
    double cur_x_v2 = 2.0;
    for(int k=1; k<100; k++){
        printf("%d. %.14f          %.14f\n", k, cur_x_v1, cur_x_v2);
        cur_x_v1 = x_next_v1(cur_x_v1, k);
        cur_x_v2 = x_next_v2(cur_x_v2, k);
    }

    return 0;
}
