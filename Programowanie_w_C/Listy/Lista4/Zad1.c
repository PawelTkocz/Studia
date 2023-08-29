#include <stdio.h>

//Pawel Tkocz 332168

int unicode_to_utf8(const unsigned int unicode, unsigned char utf8[5]){
    int pos=1;
    while((unicode>>pos)!=0){
        pos++;
    }
    //pos zawiera informacje na ilu bitach mozna zapisac binarnie a
    int bajtow=0;
    int p=0; //p bedzie zawieralo informacje o liczbie bitow, na ktorych bedzie trzeba zapisac binarnie wartosc unicode
    if(pos<=7){
        bajtow=1;
        utf8[0]=unicode;
        utf8[1]=0;
        return bajtow;
    }
    else if(pos<=11){
        bajtow=2;
        p=11;
    }
    else if(pos<=16){
        bajtow=3;
        p=16;
    }
    else if(pos<=21){
        bajtow=4;
        p=21;
    }
    else{
        return -1;
    }
    for(int i=0; i<bajtow; i++){
        int r=1; //na poczatku kazdego bajtu znajduje sie 1
        if(i==0){
            //przygotowanie pierwszego bajta utf-8
            for(int j=0; j<bajtow-1; j++){
                r=r<<1;
                r |= 1;
            }
            r=r<<1;
            //r jest rowne teraz binarnie 11...10 gdzie jedynek jest tyle ile wynosi wartosc zmiennej bajtow
            for(int j=0; j<8-bajtow-1; j++){
                //pojedynczo dodaje na koniec zmiennej r 1 lub 0 w zaleznosci od tego, jaki bit wystepuje
                //na pozycji numer p-1 w binarnym zapisie liczby unicode
                r=r<<1;
                if((unicode&(1<<(p-1)))>0){
                    r|=1;
                }
                p--;
            }
            utf8[0]=r;
        }
        else{
            r=r<<7;
            int msk=0b111111<<(6*(bajtow-1-i)); //przygotowanie maski bitowej
            msk=msk&unicode;
            msk=msk>>(6*(bajtow-1-i));
            r=r|msk;
            utf8[i]=r;
        }
    }
    utf8[bajtow]=0;
    return bajtow;
}

int main(){
    unsigned int unicode;
    scanf("%x", &unicode);
    unsigned char utf8[5]={0};
    int nbytes=unicode_to_utf8(unicode, utf8);
    if(nbytes==-1){
        printf("Podanego zanku unicode nie da sie zapisac w UTF-8 na czterech bajtach\n");
        return 0;
    }
    printf("Zapis unicode: 0x%x\n", unicode);
    printf("%d-bajtowa reprezentacja UTF-8: %x %x %x %x %x\n",
        nbytes, utf8[0], utf8[1], utf8[2], utf8[3], utf8[4]);
    printf("s: %s \n", utf8);
    return 0;
}
