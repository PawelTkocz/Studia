def kompresja(tekst):
    result = []
    i=0
    while(i<len(tekst)):
        char = tekst[i]
        l_wystapien = 1
        while(i+1 < len(tekst) and tekst[i+1] == char):
            i+=1
            l_wystapien+=1
        result.append((l_wystapien, char))
        i+=1     
    return result

def dekompresja(tekst_skompresowany):
    result = ""
    for i in tekst_skompresowany:
        l_wystapien = i[0]
        char = i[1]
        result += char*l_wystapien
    return result

skompresowany_tekst = kompresja("suuuuper")
print(skompresowany_tekst)
zdekompresowany_tekst = dekompresja(skompresowany_tekst)
print(zdekompresowany_tekst)   

#f = open('PanTadeusz.txt', 'r')
#pan_tadeusz = f.read()
#print(kompresja(pan_tadeusz))
#link do Pana Tadeusza z portalu WolneLektury w formacie txt
#https://wolnelektury.pl/media/book/txt/pan-tadeusz.txt

