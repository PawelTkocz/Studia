#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>

long long int gcd(long long int a, long long int b){
    if(b>a){
        long long pom=b;
        b=a;
        a=pom;
    }
    while(b!=0){
        long long int c=a%b;
        a=b;
        b=c;
    }
    return a;
}

long long int gcde(long long int a, long long int b,long long int *x,long long int *y){
    *x=1;
    *y=0;
    long long int r=0;
    long long int s=1;
    while(b!=0){
        long long int c=a%b;
        long long int q=a/b;
        a=b;
        b=c;

        long long int rpom=r;
        long long int spom=s;
        r=*x-q*r;
        s=*y-q*s;
        *x=rpom;
        *y=spom;
    }
    return a;
}

long long int lcm(long long int a, long long int b, long long int nwd){
    return a/nwd*b;
}

long long int potega(long long int a, long long int b, long long int c){
    long long int rez=1;
    while(b>0){
        if(b%2==1){
            rez=(a*rez)%c;
        }
        a=(a*a)%c;
        b/=2;
    }
    return rez;
}

long long int encrypt(long long int a, long long int b, long long int c){
    return potega(c, b, a);
}

int main(){
    int n;
    scanf("%d", &n);
    char komenda[10];
    long long int a, b, c;
    for(int i=0; i<n; i++){
        scanf("%s", komenda);
        if(strcmp(komenda, "GCD")==0){
            scanf("%lld", &a);
            scanf("%lld", &b);
            long long nwd=gcd(a, b);
            printf("%lli\n", nwd);
        }
        if(strcmp(komenda, "LCM")==0){
            scanf("%lld", &a);
            scanf("%lld", &b);
            printf("%lli\n", lcm(a, b, gcd(a, b)));
        }
        if(strcmp(komenda, "GCDE")==0){
            scanf("%lld", &a);
            scanf("%lld", &b);
            long long int x;
            long long int y;
            long long int nwd=gcde(a, b, &x, &y);
            printf("%lld %lld %lld\n", nwd, x, y);
        }
        if(strcmp(komenda, "POWMOD")==0){
            scanf("%lld", &a);
            scanf("%lld", &b);
            scanf("%lld", &c);
            printf("%lld\n", potega(a, b, c));
        }
        if(strcmp(komenda, "PUBKEY")==0 || strcmp(komenda, "PRIVKEY")==0){
            scanf("%lld", &a);
            scanf("%lld", &b);
            long long int n=a*b;
            long long int delta = lcm(a-1, b-1, gcd(a-1, b-1));
            long long int e=0;
            for(long long int j=3; j<delta; j++){
                if(gcd(j, delta)==1){
                    e=j;
                    j=delta;
                }
            }
            long long int x;
            long long int y;
            gcde(e, delta, &x, &y);
            while(x<0)x+=delta;
            if(strcmp(komenda, "PRIVKEY")==0)printf("%lld %lld\n", n, x);
            if(strcmp(komenda, "PUBKEY")==0)printf("%lld %lld\n", n, e);
        }
        if(strcmp(komenda, "ENCRYPT")==0 || strcmp(komenda, "DECRYPT")==0){
            scanf("%lld", &a);
            scanf("%lld", &b);
            scanf("%lld", &c);
            long long int d;
            for(long long int j=0; j<c; j++){
                scanf("%lld", &d);
                long long int odp=encrypt(a, b, d);
                printf("%lld ", odp);
            }
            printf("\n");
        }
    }
    return 0;
}
