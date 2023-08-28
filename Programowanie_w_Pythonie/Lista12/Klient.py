import xmlrpc.client
import argparse

def wypisz_ksiazki(lista):
    print("{: <2} {: <30} {: <30} {: <4}".format("Id", "Autor", "Tytuł", "Rok wydania"))
    for elem in lista:
        print("{: <2} {: <30} {: <30} {: <4}".format(elem[0], elem[1], elem[2], elem[3]))

def wypisz_znajomych(lista):
    print("{: <2} {: <30} {: <30} {: <30}".format("Id", "Imię", "Nazwisko", "Email"))
    for elem in lista:
        print("{: <2} {: <30} {: <30} {: <30}".format(elem[0], elem[1], elem[2], elem[3]))

def wypisz_wypozyczenia(lista):
    for elem in lista:
        print(str(elem[0]) + ". " + elem[1])
        print("{: <30} {: <30} {: <30}".format(elem[2], elem[3], elem[4]))
        print("{: <30} {: <30} {: <4}".format(elem[5], elem[6], elem[7]))

def powiadom_o_ewentualnym_bledzie(res):
    if(not res[0]):
        print(res[1])

server = xmlrpc.client.ServerProxy("http://localhost:8002", allow_none=True)

parser = argparse.ArgumentParser()
action = parser.add_mutually_exclusive_group(required=True)
action.add_argument('-dodaj', help="[ksiazki | znajomi] a następnie odpowiednie argumenty z ksiazka_arg lub znajomy_arg")
action.add_argument('-usun', help="[ksiazki | znajomi] a następnie odpowiednie argumenty z ksiazka_arg lub znajomy_arg")
action.add_argument('-wypisz', help="[ksiazki | znajomi | wypozyczenia]")
action.add_argument('-wypozycz', action='store_true', help="wymagane wystarczająco dokładne informacje o ksiazce oraz znajomym (można podać datę)")
action.add_argument('-oddaj', action='store_true', help="wymagane wystarczająco dokładne informacje o ksiazce oraz znajomym (można podać datę wypożyczenia)")
ksiazka_arg = parser.add_argument_group('ksiazka_arg')
ksiazka_arg.add_argument('--autor')
ksiazka_arg.add_argument('--tytul')
ksiazka_arg.add_argument('--rok')
znajomy_arg = parser.add_argument_group('znajomy_arg')
znajomy_arg.add_argument('--imie')
znajomy_arg.add_argument('--nazwisko')
znajomy_arg.add_argument('--email')
wypozyczenie_arg = parser.add_argument_group('wypozyczenie_arg')
wypozyczenie_arg.add_argument('--data')
args = parser.parse_args()

if(args.wypisz):
    if(args.wypisz == "ksiazki"):
        wypisz_ksiazki(server.lista_ksiazek())
    elif(args.wypisz == "znajomi"):
        wypisz_znajomych(server.lista_znajomych())
    elif(args.wypisz == "wypozyczenia"):
        wypisz_wypozyczenia(server.lista_wypozyczen())
    else:
        raise Exception("-wypisz [ksiazki | znajomi | wypozyczenia]")

if(args.dodaj):
    if(args.dodaj == "ksiazki"):
        res = server.dodaj_ksiazke(args.autor, args.tytul, args.rok)
        powiadom_o_ewentualnym_bledzie(res)
    elif(args.dodaj == "znajomi"):
        res = server.dodaj_znajomego(args.imie, args.nazwisko, args.email)
        powiadom_o_ewentualnym_bledzie(res)
    else:
        raise Exception("-dodaj [ksiazki | znajomi]")

if(args.usun):
    if(args.usun == "ksiazki"):
        res = server.usun_ksiazke(args.autor, args.tytul, args.rok)
        powiadom_o_ewentualnym_bledzie(res)
    elif(args.usun == "znajomi"):
        res = server.usun_znajomego(args.imie, args.nazwisko, args.email)
        powiadom_o_ewentualnym_bledzie(res)
    else:
        raise Exception("-dodaj [ksiazki | znajomi]")    

if(args.wypozycz):
    res = server.wypozycz_ksiazke(args.imie, args.nazwisko, args.email, args.autor, args.tytul, args.rok, args.data)
    powiadom_o_ewentualnym_bledzie(res)

if(args.oddaj):
    res = server.oddaj_ksiazke(args.imie, args.nazwisko, args.email, args.autor, args.tytul, args.rok, args.data)
    powiadom_o_ewentualnym_bledzie(res)


