#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv){
    if(argc<2)return 0;
    char naglowek[3];
    int width;
    int height;
    int max_value;
    scanf("%s", naglowek);
    scanf("%d %d %d", &width, &height, &max_value);
    printf("%s\n", naglowek);
    printf("%d %d\n%d\n", width, height, max_value);
    getchar();
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            unsigned char a, b, c;
            a=(unsigned char)getchar();
            b=(unsigned char)getchar();
            c=(unsigned char)getchar();
            if(strcmp(argv[1], "-blackwhite")==0){
                int srednia=(a+b+c)/3;
                putchar(srednia);
                putchar(srednia);
                putchar(srednia);
            }
            else if(strcmp(argv[1], "-filter")==0){
                if(argc!=3)return 0;
                int rgb[3]={0};
                for(unsigned int j=0; j<strlen(argv[2]); j++){
                    if(argv[2][j]=='r')rgb[0]=1;
                    if(argv[2][j]=='g')rgb[1]=1;
                    if(argv[2][j]=='b')rgb[2]=1;
                }
                if(rgb[0]==1)putchar(a);
                else putchar(0);
                if(rgb[1]==1)putchar(b);
                else putchar(0);
                if(rgb[2]==1)putchar(c);
                else putchar(0);
            }
            else if(strcmp(argv[1], "-contrast")==0){
                if(a>127)putchar(255);
                else printf("0");
                if(b>127)putchar(255);
                else printf("0");
                if(c>127)putchar(255);
                else printf("0");
            }
            else if(strcmp(argv[1], "-gamma")==0){
                if(argc!=3)return 0;
                double gmm=atof(argv[2]);
                double a2=(double)a/255;
                double b2=(double)b/255;
                double c2=(double)c/255;
                a2=pow(a2, gmm);
                b2=pow(b2, gmm);
                c2=pow(c2, gmm);
                a2*=255;
                b2*=255;
                c2*=255;
                a=a2;
                b=b2;
                c=c2;
                putchar(a);
                putchar(b);
                putchar(c);
            }
            else{
                printf("Program zostal wywolany ze zlymi argumentami");
            }
        }
    }
    printf("\n");
    return 0;
}
