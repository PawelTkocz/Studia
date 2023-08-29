#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if(argc!=4)return 0;
    char asci_art[11][6][9]={
    {
    "  ____  ",
    " / __ \\ ",
    "| /  \\ |",
    "| |  | |",
    "| \\__/ |",
    " \\____/ ",
    },
    {
    "   __   ",
    "  /_ |  ",
    "   | |  ",
    "   | |  ",
    "   | |  ",
    "   |_|  ",
    },
    {
    "  ____  ",
    " |__  | ",
    "    ) | ",
    "   /  / ",
    "  /  /_ ",
    " |_____|",
    },
    {
    "  ____  ",
    " |__  \\ ",
    "  __)  |",
    " |__  < ",
    " ___)  |",
    " \\____/ ",
    },
    {
    " _   _  ",
    "| ||| | ",
    "| ||| |_",
    "|__   _|",
    "   | |  ",
    "   |_|  ",
    },
    {
    " ______ ",
    "|  ____|",
    "| |___  ",
    "|___  \\ ",
    " ___)  |",
    "|_____/ ",
    },
    {
    "   __   ",
    "  / /   ",
    " / /__  ",
    "|  _  \\ ",
    "| (_)  |",
    " \\____/ ",
    },
    {
    " ______ ",
    "|____  |",
    "    / / ",
    "   / /  ",
    "  / /   ",
    " /_/    ",
    },
    {
    "  ____  ",
    " / __ \\ ",
    "| (__) |",
    " > __ < ",
    "| (__) |",
    " \\____/ ",
    },
    {
    "  ____  ",
    " / __ \\ ",
    "| (__) |",
    " \\__  / ",
    "   / /  ",
    "  /_/   ",
    },
    {
    "        ",
    "   __   ",
    "  (__)  ",
    "   __   ",
    "  (__)  ",
    "        ",
    },
    };
    int h=atoi(argv[1]);
    int m=atoi(argv[2]);
    int s=atoi(argv[3]);
    if(h<0 || h>23 || m<0 || m>59 || s<0 || s>59)return 0;
    for(int i=0; i<6; i++){
        printf("%s", asci_art[h/10][i]);
        printf("%s", asci_art[h%10][i]);
        printf("%s", asci_art[10][i]);
        printf("%s", asci_art[m/10][i]);
        printf("%s", asci_art[m%10][i]);
        printf("%s", asci_art[10][i]);
        printf("%s", asci_art[s/10][i]);
        printf("%s", asci_art[s%10][i]);
        printf("\n");
    }
    long long czas=s+60*m+3600*h;
    while(1){
        char a=getchar();
        if(a=='\n'){
            czas++;
            s=czas%60;
            m=(czas%3600)/60;
            h=(czas/3600)%24;
            for(int i=0; i<50; i++) printf("\n");
            for(int i=0; i<6; i++){
                printf("%s", asci_art[h/10][i]);
                printf("%s", asci_art[h%10][i]);
                printf("%s", asci_art[10][i]);
                printf("%s", asci_art[m/10][i]);
                printf("%s", asci_art[m%10][i]);
                printf("%s", asci_art[10][i]);
                printf("%s", asci_art[s/10][i]);
                printf("%s", asci_art[s%10][i]);
                printf("\n");
            }
        }
    }
    return 0;
}
