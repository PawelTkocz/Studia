#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "kierki_obs.h"

void inicjalizuj_karte(struct karta karty[52], int id, int k, int w, char *n1, char *n2){
    //funkcja inicjalizujaca karte
    karty[id].id=id;
    karty[id].kolor=k;
    karty[id].wartosc=w;
    strcpy(karty[id].obraz, n1);
    strcpy(karty[id].obraz2, n2);
}

void inicjalizuj_talie(struct karta karty[52]){
    //funkcja inicjalizujace talie 52 kart
    inicjalizuj_karte(karty, 0, 1, 2, "karty/dwa1.png", "karty/dwa12.png");
    inicjalizuj_karte(karty, 1, 1, 3, "karty/trzy1.png", "karty/trzy12.png");
    inicjalizuj_karte(karty, 2, 1, 4, "karty/cztery1.png", "karty/cztery12.png");
    inicjalizuj_karte(karty, 3, 1, 5, "karty/piec1.png", "karty/piec12.png");
    inicjalizuj_karte(karty, 4, 1, 6, "karty/szesc1.png", "karty/szesc12.png");
    inicjalizuj_karte(karty, 5, 1, 7, "karty/siedem1.png", "karty/siedem12.png");
    inicjalizuj_karte(karty, 6, 1, 8, "karty/osiem1.png", "karty/osiem12.png");
    inicjalizuj_karte(karty, 7, 1, 9, "karty/dziewiec1.png", "karty/dziewiec12.png");
    inicjalizuj_karte(karty, 8, 1, 10, "karty/dziesiec1.png", "karty/dziesiec12.png");
    inicjalizuj_karte(karty, 9, 1, 11, "karty/walet1.png", "karty/walet12.png");
    inicjalizuj_karte(karty, 10, 1, 12, "karty/dama1.png", "karty/dama12.png");
    inicjalizuj_karte(karty, 11, 1, 13, "karty/krol1.png", "karty/krol12.png");
    inicjalizuj_karte(karty, 12, 1, 14, "karty/as1.png", "karty/as12.png");
    inicjalizuj_karte(karty, 13, 2, 2, "karty/dwa2.png", "karty/dwa22.png");
    inicjalizuj_karte(karty, 14, 2, 3, "karty/trzy2.png", "karty/trzy22.png");
    inicjalizuj_karte(karty, 15, 2, 4, "karty/cztery2.png", "karty/cztery22.png");
    inicjalizuj_karte(karty, 16, 2, 5, "karty/piec2.png", "karty/piec22.png");
    inicjalizuj_karte(karty, 17, 2, 6, "karty/szesc2.png", "karty/szesc22.png");
    inicjalizuj_karte(karty, 18, 2, 7, "karty/siedem2.png", "karty/siedem22.png");
    inicjalizuj_karte(karty, 19, 2, 8, "karty/osiem2.png", "karty/osiem22.png");
    inicjalizuj_karte(karty, 20, 2, 9, "karty/dziewiec2.png", "karty/dziewiec22.png");
    inicjalizuj_karte(karty, 21, 2, 10, "karty/dziesiec2.png", "karty/dziesiec22.png");
    inicjalizuj_karte(karty, 22, 2, 11, "karty/walet2.png", "karty/walet22.png");
    inicjalizuj_karte(karty, 23, 2, 12, "karty/dama2.png", "karty/dama22.png");
    inicjalizuj_karte(karty, 24, 2, 13, "karty/krol2.png", "karty/krol22.png");
    inicjalizuj_karte(karty, 25, 2, 14, "karty/as2.png", "karty/as22.png");
    inicjalizuj_karte(karty, 26, 0, 2, "karty/dwa0.png", "karty/dwa02.png");
    inicjalizuj_karte(karty, 27, 0, 3, "karty/trzy0.png", "karty/trzy02.png");
    inicjalizuj_karte(karty, 28, 0, 4, "karty/cztery0.png", "karty/cztery02.png");
    inicjalizuj_karte(karty, 29, 0, 5, "karty/piec0.png", "karty/piec02.png");
    inicjalizuj_karte(karty, 30, 0, 6, "karty/szesc0.png", "karty/szesc02.png");
    inicjalizuj_karte(karty, 31, 0, 7, "karty/siedem0.png", "karty/siedem02.png");
    inicjalizuj_karte(karty, 32, 0, 8, "karty/osiem0.png", "karty/osiem02.png");
    inicjalizuj_karte(karty, 33, 0, 9, "karty/dziewiec0.png", "karty/dziewiec02.png");
    inicjalizuj_karte(karty, 34, 0, 10, "karty/dziesiec0.png", "karty/dziesiec02.png");
    inicjalizuj_karte(karty, 35, 0, 11, "karty/walet0.png", "karty/walet02.png");
    inicjalizuj_karte(karty, 36, 0, 12, "karty/dama0.png", "karty/dama02.png");
    inicjalizuj_karte(karty, 37, 0, 13, "karty/krol0.png", "karty/krol02.png");
    inicjalizuj_karte(karty, 38, 0, 14, "karty/as0.png", "karty/as02.png");
    inicjalizuj_karte(karty, 39, 3, 2, "karty/dwa3.png", "karty/dwa32.png");
    inicjalizuj_karte(karty, 40, 3, 3, "karty/trzy3.png", "karty/trzy32.png");
    inicjalizuj_karte(karty, 41, 3, 4, "karty/cztery3.png", "karty/cztery32.png");
    inicjalizuj_karte(karty, 42, 3, 5, "karty/piec3.png", "karty/piec32.png");
    inicjalizuj_karte(karty, 43, 3, 6, "karty/szesc3.png", "karty/szesc32.png");
    inicjalizuj_karte(karty, 44, 3, 7, "karty/siedem3.png", "karty/siedem32.png");
    inicjalizuj_karte(karty, 45, 3, 8, "karty/osiem3.png", "karty/osiem32.png");
    inicjalizuj_karte(karty, 46, 3, 9, "karty/dziewiec3.png", "karty/dziewiec32.png");
    inicjalizuj_karte(karty, 47, 3, 10, "karty/dziesiec3.png", "karty/dziesiec32.png");
    inicjalizuj_karte(karty, 48, 3, 11, "karty/walet3.png", "karty/walet32.png");
    inicjalizuj_karte(karty, 49, 3, 12, "karty/dama3.png", "karty/dama32.png");
    inicjalizuj_karte(karty, 50, 3, 13, "karty/krol3.png", "karty/krol32.png");
    inicjalizuj_karte(karty, 51, 3, 14, "karty/as3.png", "karty/as32.png");
}

void inicjalizuj_stan_gry(struct stan_gry *st_gry){
    //funckja ustawia parametry stanu gry na wartosci domyslne
    strcpy(st_gry->nazwy_graczy[0], "Użytkownik");
    strcpy(st_gry->nazwy_graczy[1], "Zachód");
    strcpy(st_gry->nazwy_graczy[2], "Północ");
    strcpy(st_gry->nazwy_graczy[3], "Wschód");
    st_gry->czekaj=0;
    st_gry->szybkosc=250;
    for(int i=0; i<20; i++){
        for(int j=0; j<4; j++){
            st_gry->historia_gry[i][j]=0;
        }
    }
    st_gry->rozegranych_rund=0;
    for(int i=0; i<4; i++){
        st_gry->punkty_runda[i]=0;
        st_gry->punkty_suma[i]=0;
    }
    st_gry->kolej_gracza=0;
    st_gry->przekazywanie=1;
    st_gry->do_zamkniecia=NULL;
    for(int i=0; i<13; i++){
        st_gry->do_przekazania[i]=0;
        st_gry->karty_graczaA[i]=-1;
        st_gry->karty_graczaB[i]=-1;
        st_gry->karty_graczaC[i]=-1;
        st_gry->karty_graczaD[i]=-1;
    }
    st_gry->wybranych_kart=0;
    st_gry->karty_graczy[0]=st_gry->karty_graczaA;
    st_gry->karty_graczy[1]=st_gry->karty_graczaB;
    st_gry->karty_graczy[2]=st_gry->karty_graczaC;
    st_gry->karty_graczy[3]=st_gry->karty_graczaD;
    st_gry->kart_na_stole=0;
    st_gry->zagranych_lew=0;
    st_gry->blokada=1;
    st_gry->kolor=-1;
    st_gry->rozdane_karty=0;
    st_gry->przekaz_komu=2;
    inicjalizuj_talie(st_gry->karty);
}

int koniec_gry(int punkty_suma[4]){
    //funkcja zwraca 1 jesli ktorys z graczy ma conajmniej 100 punktow
    for(int i=0;i<4; i++){
        if(punkty_suma[i]>=100)return 1;
    }
    return 0;
}

int punktuj_lewe(int karty_na_stole[4], int *punkty, int kolor, struct stan_gry *st_gry){
    //funkcja zwraca indeks gracza ktory zbiera karty lezace na stole
    //dodatkowo liczy ile punktow karnych otrzyma ten gracz
    //i dopisuje je w tablicy punkty
    int tab[4];
    int suma_pkt=0;
    for(int i=0; i<4; i++){
        tab[i]=st_gry->karty[karty_na_stole[i]].wartosc;
        if(st_gry->karty[karty_na_stole[i]].kolor==kolor)tab[i]+=100;
        if(st_gry->karty[karty_na_stole[i]].kolor==3)suma_pkt++;
        if(karty_na_stole[i]==36)suma_pkt+=13;
    }
    int bierze=0;
    int maxi=tab[0];
    for(int i=1; i<4; i++){
        if(tab[i]>maxi){
            bierze=i;
            maxi=tab[i];
        }
    }
    punkty[bierze]+=suma_pkt;
    return bierze;
}

void ustaw_karty(int *reka){
    //funkcja ustawia karty kolorystycznie (trefl, karo, pik, kier)
    //i ustawia karty jednego koloru w rosnacej kolejnosci
    for(int i=0; i<12; i++){
        for(int j=0; j<12-i; j++){
            if(reka[j]>reka[j+1]){
                int pom=reka[j];
                reka[j]=reka[j+1];
                reka[j+1]=pom;
            }
        }
    }
}

void rozdaj_karty(int *karty_graczaA, int *karty_graczaB, int *karty_graczaC, int *karty_graczaD){
    //funckja tworzy talie 52 kart i nastepnie ja tasuje
    //potem kazdemu z graczy przydziela losowo wybrane 13 kart
    int *wskazniki[4];
    wskazniki[0]=karty_graczaA;
    wskazniki[1]=karty_graczaB;
    wskazniki[2]=karty_graczaC;
    wskazniki[3]=karty_graczaD;
    srand(time(NULL));
    int talia[52];
    for(int i=0; i<52; i++)talia[i]=i;
    for(int i=0; i<10000; i++){
        int a=rand()%52;
        int b=rand()%52;
        int pom=talia[a];
        talia[a]=talia[b];
        talia[b]=pom;
    }
    int a;
    int *pom_ptr;
    for(int i=0; i<52; i++){
        a=rand()%(52-i);
        pom_ptr=wskazniki[i/13];
        pom_ptr[i%13]=talia[a];
        for(int j=a; j<52-1-i; j++){
            int pom=talia[j];
            talia[j]=talia[j+1];
            talia[j+1]=pom;
        }
    }
    ustaw_karty(karty_graczaA);
    ustaw_karty(karty_graczaB);
    ustaw_karty(karty_graczaC);
    ustaw_karty(karty_graczaD);
}

int kto_zaczyna(int *karty_graczaA, int *karty_graczaB, int *karty_graczaC, int *karty_graczaD){
    //funckcja sprawdza ktory z graczy ma karte o indeksie 0 (czyli 2 trefl)
    //i zwraca indeks tego gracza
    int *wskazniki[4];
    wskazniki[0]=karty_graczaA;
    wskazniki[1]=karty_graczaB;
    wskazniki[2]=karty_graczaC;
    wskazniki[3]=karty_graczaD;
    int *pom;
    for(int i=0; i<52; i++){
        pom=wskazniki[i/13];
        if(pom[i%13]==0)return i/13;
    }
    return 0;
}

int wybierz_karte(int *karty_gracza, int kolor, int pierw, int karty_na_stole[4], struct stan_gry *st_gry){
    //funckja podejmuje decyzje ktora z kart dostepnych na rece najlepiej wyrzucic na stol
    //biorac pod uwage karty juz znajujace sie na stole
    struct karta *karty=st_gry->karty;
    if(pierw==1){
        karty_gracza[0]=-1;
        return 0;
    }
    int kolorow[4]={0};
    for(int i=0; i<13; i++){
        if(karty_gracza[i]!=-1)kolorow[karty[karty_gracza[i]].kolor]++;
    }
    if(kolor==-1){
        //jesli gracz zagrywa pierwsza karte na stol
        int mini=0;
        int ile=14;
        for(int i=0; i<4; i++){
            if(kolorow[i]>0 && kolorow[i]<ile){
                    mini=i;
                    ile=kolorow[i];
            }
        }
        int najm=15;
        int najm_ind=0;
        //gracz wyrzuci karte w kolorze, ktorego ma najmniej na rece
        //o ile karta ta bedzie slabsza od damy
        for(int i=0; i<13; i++){
            if(karty_gracza[i]!=-1 && karty[karty_gracza[i]].kolor==mini && karty[karty_gracza[i]].wartosc<12){
                int pom=karty_gracza[i];
                karty_gracza[i]=-1;
                return pom;
            }
            if(karty_gracza[i]!=-1 && karty[karty_gracza[i]].wartosc<najm){
                najm=karty[karty_gracza[i]].wartosc;
                najm_ind=i;
            }
        }
        //jesli gracz nie ma takiej karty, wyrzuci najslabsza karte z dostepnych na rece
        int pom=karty_gracza[najm_ind];
        karty_gracza[najm_ind]=-1;
        return pom;
    }
    if(kolorow[kolor]>0){
        //jesli na stole znajduje sie juz karta
        //i gracz ma conajmniej jedna karte zadanego koloru na rece
        if(kolor==0){
            int ind_damy=-1;
            for(int i=0; i<13; i++)if(karty_gracza[i]==36){
                ind_damy=i;
            }
            if(ind_damy!=-1){
                //jesli gracz ma szanse bezpiecznie pozbyc sie damy pik, to to zrobi
                for(int i=0; i<4; i++){
                    if(karty_na_stole[i]!=-1 && karty[karty_na_stole[i]].kolor==0 && karty[karty_na_stole[i]].wartosc>12){
                        int pom=karty_gracza[ind_damy];
                        karty_gracza[ind_damy]=-1;
                        return pom;
                    }
                }
            }
        }
        int kart=0;
        int najsil=-1;
        //sprawdzam jaka z wylozonych dotychczas na stol kart w zadanym kolorze jest najsilniejsza
        for(int i=0; i<4; i++){
            if(karty_na_stole[i]>=0){
                kart++;
                if(karty[karty_na_stole[i]].kolor==kolor && karty[karty_na_stole[i]].wartosc>najsil){
                        najsil=karty[karty_na_stole[i]].wartosc;
                }
            }
        }
        int moz_najwieksza=-1;
        int najwieksza=-1;
        int najmniejsza=-1;
        //szukam najsilniejszej karty w zadanym kolorze, lecz nie silniejszej od tych znajdujacych sie juz na stole
        for(int i=0; i<13; i++){
            if(karty_gracza[i]!=-1 && karty[karty_gracza[i]].kolor==kolor){
                if(najmniejsza==-1){
                    najmniejsza=i;
                }
                if(karty[karty_gracza[i]].wartosc<najsil){
                        moz_najwieksza=i;
                }
                else {
                    najwieksza=i;
                }
            }
        }
        if(moz_najwieksza!=-1){
            //jesli udalo sie taka znalezc, to gracz ja zagra
            int pom=karty_gracza[moz_najwieksza];
            karty_gracza[moz_najwieksza]=-1;
            return pom;
        }
        else{
            if(kart==3){
                //jesli na stole znajduja sie juz trzy karty, gracz pozbywa sie najsilniejszej karty w danym kolorze
                int pom=karty_gracza[najwieksza];
                karty_gracza[najwieksza]=-1;
                return pom;
            }
            else{
                //jesli po graczu ktos bedzie jeszcze dokladal karte, zagrywa najmniejsza jaka ma
                int pom=karty_gracza[najmniejsza];
                karty_gracza[najmniejsza]=-1;
                return pom;
            }
        }
    }
    //jesli gracz nie ma zadanego koloru
    int najw_in=-1;
    int najw_war=-1;
    int dama_pik=-1;
    //sprawdzam, czy gracz ma dame pik oraz szukam najsilniejszej karty do pozbycia sie jej
    for(int i=0; i<13; i++){
        if(karty_gracza[i]==36)dama_pik=i;
        if(karty_gracza[i]!=-1 && karty[karty_gracza[i]].wartosc>najw_war){
            najw_war=karty[karty_gracza[i]].wartosc;
            najw_in=i;
        }
    }
    if(dama_pik>=0){
        karty_gracza[dama_pik]=-1;
        return 36;
    }
    if(kolorow[3]>0){
        //jesli gracz ma na rece kiery, wyrzuca najsilniejszy z nich
        for(int i=12; i>=0; i--){
            if(karty_gracza[i]!=-1){
                int pom=karty_gracza[i];
                karty_gracza[i]=-1;
                return pom;
            }
        }
    }
    //jesli nie, wyrzuca najsilniejsza karte na rece
    int pom=karty_gracza[najw_in];
    karty_gracza[najw_in]=-1;
    return pom;
}

int losuj_przeciwnika(){
    //funckja losuje indeks jednego z przeciwnikow
    int a=rand()%3+1;
    return a;
}

void zamiana_kart(int *karty_gracza1, int *karty_gracza2, int do_przekazania[13], int *otrzymane_karty, struct stan_gry *st_gry){
    //funckja decyduje ktorych z kart na rece najlepiej sie pozbyc
    //i dokonuje zamiany tych trzech kart z trzema wybranymi przez uzytkownika kartami
    struct karta *karty=st_gry->karty;
    int wybrane[13]={0};
    int ile_wybranych=0;
    for(int i=0; i<13; i++){
        if(karty_gracza2[i]==36){
            otrzymane_karty[ile_wybranych]=36;
            wybrane[i]=1;
            ile_wybranych++;
        }
    }
    //jesli gracz ma na recie silne kiery lub dame, krola, asa pik, to pozbedzie sie ich
    for(int i=12; i>=0; i--){
        if(ile_wybranych<3){
            if((karty[karty_gracza2[i]].kolor==3 && karty[karty_gracza2[i]].wartosc>9)||karty_gracza2[i]==37 || karty_gracza2[i]==38){
                otrzymane_karty[ile_wybranych]=karty_gracza2[i];
                wybrane[i]=1;
                ile_wybranych++;
            }
        }
    }
    if(ile_wybranych<3){
        //jesli nadal nie wybrano trzech kart
        //zostana wybrane najsilniejsze z kart gracza na rece
        for(int i=14; i>=2; i--){
            for(int t=0; t<13; t++){
                if(wybrane[t]==0 && karty[karty_gracza2[t]].wartosc==i){
                    wybrane[t]=1;
                    otrzymane_karty[ile_wybranych]=karty_gracza2[t];
                    ile_wybranych++;
                    if(ile_wybranych==3){
                        t=13;
                        i=0;
                    }
                }
            }
        }
    }
    int dane_karty[3];
    int pom=0;
    //przekazanie wybranych kart do reki uzytkownika
    for(int i=0; i<13; i++){
        if(do_przekazania[i]==1){
            dane_karty[pom]=karty_gracza1[i];
            karty_gracza1[i]=otrzymane_karty[pom];
            pom++;
        }
    }
    pom=0;
    //przekazanie kart wybranych przez uzytkownika do reki gracza
    for(int i=0; i<13; i++){
        if(wybrane[i]==1){
            karty_gracza2[i]=dane_karty[pom];
            pom++;
        }
    }
    ustaw_karty(karty_gracza1);
    ustaw_karty(karty_gracza2);
}

void uloz_podium(int *miejsca_graczy, int suma_punktow[4]){
    //funckja otrzymuje ostateczne wyniki rozgrywki
    //sortuje je razem z indeksami odpowiednich graczy
    //tworzac w ten sposob podium
    for(int i=0; i<4; i++)miejsca_graczy[i]=i;
    for(int i=0; i<3; i++){
        for(int j=0; j<3-i; j++){
            if(suma_punktow[j]>suma_punktow[j+1]){
                int pom=miejsca_graczy[j];
                miejsca_graczy[j]=miejsca_graczy[j+1];
                miejsca_graczy[j+1]=pom;
                pom=suma_punktow[j];
                suma_punktow[j]=suma_punktow[j+1];
                suma_punktow[j+1]=pom;
            }
        }
    }
}
