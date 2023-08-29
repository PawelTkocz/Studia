#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Paweł Tkocz 332168
int main()
{
    const double pi=3.141592653589793238462643383279;
    double pi_ok=0.0; //znalezione przyblizenie wartosci pi
    srand(time(0));
    long long zakres=1;
    double r=1.0;
    double x=0.0;
    double y=0.0;
    double p_cw=0.0; //szacowane pole cwiartki kola
    double p_kw=r*r;  //pole kwadratu
    double pi_roz=0.0; //roznica wartosci pi i szacowania pi
    for(int i=0; i<10; i++){
        if(i>0)
            zakres*=10;
        long long wew=0;
        for(long long j=0; j<zakres; j++){
            x=(double)rand()/RAND_MAX;
            y=(double)rand()/RAND_MAX;
            if(x*x+y*y<=r*r)
                wew++;
        }
        p_cw=p_kw*wew/zakres; //=pi*r*r/4
        pi_ok=p_cw*4/r/r;
        pi_roz=pi-pi_ok;
        if(pi_roz<0)
            pi_roz*=-1;
        printf("Ilość próbek: %lld, Szacowana wartość pi: %lf, Różnica względem pi: %lf\n", zakres, pi_ok, pi_roz);
    }
    printf("\nMetoda ze wzoru Leibniza: \n");
    long long e=0; //10^7 da dokladne pi
    printf("Podaj długość szeregu: \n");
    scanf("%lld", &e);
    double suma=0.0;
    for(long long i=0; i<e; i++){
        double kn=1.0/(2*i+1);
        if(i%2==1){
            kn*=-1;
        }
        suma+=kn;
    }
    pi_ok=suma*4;
    pi_roz=pi-pi_ok;
    if(pi_roz<0)
        pi_roz*=-1;
    printf("Ilość próbek: %lld, Szacowana wartość pi: %lf, Różnica względem pi: %lf\n", e, pi_ok, pi_roz);
    return 0;
}
