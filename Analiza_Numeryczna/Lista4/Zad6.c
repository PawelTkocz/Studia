#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x, double a){
    return 1.5*x - 0.5*x*x*x*a;
}

double best_x0(double a, double e){
    int min=100;
    double best_x0 = 0;
    double res = 1/sqrt(a);

    double start;
    double end;
    double jump;
    if(a>=1){
        start = 0.01;
        end = 1.0;
        jump = 0.01;
    }
    else{
        start = 1.0;
        end = 1/a;
        jump = (end - start)/100.0;
    }

    for(double i=start; i<end; i+=jump){
        int n=0;
        double x = i;
        while(fabs(x-res)>e && n<20){
            x = f(x, a);
            n++;
        }
        if(n<min){
            min = n;
            best_x0 = i;
        }
    }
    return best_x0;
}

double find_x0(double a){
    if(a>=1){
        int n =0;
        int b = (int)a;
        while(b > 1){
            n++;
            b = (b >> 1);
        }
        n = (n>>1);
        return 1 / pow(2, n);
    }
    else{
        int n = 0;
        while(a<1){
            n++;
            a*=2;;
        }
        n = (n>>1)-1;
        return pow(2, n);
    }
}

int main(){
    double res;
    double e = pow(10, -10);
    int n;
    double x0;
    double x;
    double sum = 0;

    for(int i=0; i<10; i++){
        double a = 0.1 * (i+1);
        x0 = best_x0(a, pow(10, -5));
        printf("%lf.\nNajlepsze x0: %lf\n", a, x0);
        n = 0;
        x = x0;
        res = 1/sqrt(a);
        while(fabs(x - res)>e){
            n++;
            x = f(x, a);
        }
        sum += n;
    }
    for(int i = 0; i<10; i++){
        double a = pow(3, i);
        x0 = best_x0(a, pow(10, -5));
        printf("%lf.\nNajlepsze x0: %lf\n", a, x0);
        n =0;
        x = x0;
        res = 1/sqrt(a);
        while(fabs(x - res)>e){
            n++;
            x = f(x, a);
        }
        sum += n;
    }

    printf("Srednia ilosc iteracji: %lf\n", sum/20);

}
