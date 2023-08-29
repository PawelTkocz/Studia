#include <stdio.h>

//Pawel Tkocz 332168

int utf8_to_unicode(const unsigned char utf8[5]){
    if(utf8[4]!=0) return -1;
    int bajtow=0;
    int bylo0=0;
    for(int i=1; i<5; i++){
        if(utf8[i]==0){
            if(bylo0==0){
              bylo0=1;
              bajtow=i;
            }
        }
        else{
            if(bylo0==1) return -1;
        }
    }
    unsigned int unicode=0;
    if(bajtow==1){
        unicode=utf8[0];
        if((unicode>>7)>0) return -1;
        return unicode;
    }
    for(int i=0; i<bajtow; i++){
        int w=utf8[i];
        if((w>>8)>0) return -1;
        if(i==0){
            int poczatek=(w>>(8-bajtow-1));
            int poczatek_ok=1;
            for(int j=0; j<bajtow-1; j++){
                poczatek_ok=(poczatek_ok<<1);
                poczatek_ok+=1;
            }
            poczatek_ok=(poczatek_ok<<1);
            if(poczatek_ok!=poczatek)return -1;
            //pierwszy bajt jest zakodowany w poprawny sposob
            poczatek_ok=(poczatek_ok<<(8-bajtow-1));
            unicode=utf8[0]-poczatek_ok;
        }
        else{
            if((w>>6)!=2)return -1;
            w-=(1<<7);
            unicode=unicode<<6;
            unicode+=w;
        }
    }
    return unicode;
}

int main(){
    unsigned char utf8[5]={0};
    for(int i=0; i<5; i++){
        int a;
        scanf("%x", &a);
        utf8[i]=a;
    }
    int unicode = utf8_to_unicode(utf8);
    if(unicode==-1){
        printf("Kod utf8 jest niepoprawny\n");
        return 0;
    }
    printf("s: %s \n", utf8);
    printf("reprezentacja UTF-8: %x %x %x %x %x\n",
        utf8[0], utf8[1], utf8[2], utf8[3], utf8[4]);
    printf("Zapis unicode: 0x%x\n", unicode);
    return 0;
}
