#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979

double a_v1(double x){
    return 1/(x+sqrt(x*x+2022.0*2022.0));
}

double a_v2(double x){
    if(x<0)
        return (sqrt(x*x+2022*2022) - x)/(2022.0*2022.0);
    else
        return 1/(x+sqrt(x*x+2022.0*2022.0));
}

double b_v1(double x){
    //log3(x)
    return log(x)/log(3)-7;
}

double b_v2(double x){
    return log(x/pow(3, 7))/log(3);
}

double c_v1(double x){
    return 4*cos(x)*cos(x)-3;
}

double c_v2(double x){
    return 4*sin(x+PI/6)*sin(PI/6-x);
    // = cos(3*x)/cos(x);
}

int main(){
    double a_1 = -1*pow(10, 10);
    double a_2 = -1*pow(2, 30);
    printf("a) (x + sqrt(x^2 - 2022^2))^(-1)\n");
    printf("Dla x = -(10^10):\n");
    printf("Poprawna wartosc: 4891.7887412547\n");
    printf("Wersja 1:         %.10f\n", a_v1(a_1));
    printf("Wersja 2:         %.10f\n", a_v2(a_1));
    printf("Dla x = -(2^30):\n");
    printf("Poprawna wartosc: 525.2518165662\n");
    printf("Wersja 1:         %.10f\n", a_v1(a_2));
    printf("Wersja 2:         %.10f\n\n", a_v2(a_2));

    double b = pow(3, 7) - pow(2, -20);
    printf("b) log3(x)-7\n");
    printf("Dla x = 3^7 - 2^(-20):\n");
    printf("Poprawna wartosc: -0.000000000396923535\n");
    printf("Wersja 1:         %.18f\n", b_v1(b));
    printf("Wersja 2:         %.18f\n\n", b_v2(b));

    double c = PI/6-pow(2, -20);
    printf("c) 4cos(x)^2-3\n");
    printf("Dla x = PI/6 - 2^(-20):\n");
    printf("Poprawna wartosc: 0.00000330362292078688\n");
    printf("Wersja 1:         %.20f\n", c_v1(c));
    printf("Wersja 2:         %.20f\n", c_v2(c));
    return 0;
}






