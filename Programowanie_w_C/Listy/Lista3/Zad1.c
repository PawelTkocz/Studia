#include <stdio.h>
#include <ctype.h>


int main(){
    int poprz;
    char a=getchar();
    printf("%c", a);
    poprz=a;
    a=getchar();
    while(a!='\n'){
        if(poprz<a){
            printf("%c", toupper(a));
        }
        else{
            printf("%c", tolower(a));
        }
        poprz=a;
        a=getchar();
    }
    return 0;
}
