import random

def usun_zbyt_dlugie_slowa(tekst, max_dl_slowa):
    result = ""
    ilosc_slow = 0
    i = 0
    usunieto = False
    while i < len(tekst):
        if not tekst[i].isalpha():
            if not usunieto:
                result += str(tekst[i])
            else:
                usunieto = False
            i+=1
        else:
            slowo = ""
            dlugosc_slowa = 0
            while i < len(tekst) and tekst[i].isalpha():
                slowo += str(tekst[i])
                dlugosc_slowa+=1
                i+=1
            if dlugosc_slowa <= max_dl_slowa:
                result += slowo
                ilosc_slow+=1
            else:
                usunieto = True
    return (result, ilosc_slow)

def usun_losowe_slowa(tekst, all_words, words_to_remove):
    randoms = []
    random.seed()
    for i in range(words_to_remove):
        x = random.randint(0, all_words-1)
        while True:
            if x in randoms:
                x = (x+1)%all_words
            else:
                randoms.append(x)
                break    
    result = ""
    words = 0
    usunieto = False
    i = 0
    while i < len(tekst):
        if not (str(tekst[i]).isalpha()):
            if not usunieto:
                result += tekst[i]
            else:
                usunieto = False
            i+=1
        else:
            slowo = ""
            while i < len(tekst) and tekst[i].isalpha():
                slowo += tekst[i]
                i+=1
            if not (words in randoms):
                result += slowo
            else:
                usunieto = True
            words+=1
    return result

def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    res = usun_zbyt_dlugie_slowa(tekst, dl_slowa)
    new_text = res[0]
    words = res[1]
    if words <= liczba_slow:
        return new_text
    return usun_losowe_slowa(new_text, words, words-liczba_slow)

tekst = "Podział peryklinalny inicjałów wrzecionowatych \
kambium charakteryzuje się ścianą podziałową inicjowaną \
w płaszczyźnie maksymalnej."
print(uprosc_zdanie(tekst, 10, 5))


#f = open('PanTadeusz.txt', 'r')
#pan_tadeusz = f.read()
#print(uprosc_zdanie(pan_tadeusz, 5, 30000))
#link do Pana Tadeusza z portalu WolneLektury w formacie txt
#https://wolnelektury.pl/media/book/txt/pan-tadeusz.txt



