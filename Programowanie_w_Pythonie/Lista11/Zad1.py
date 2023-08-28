import sqlite3
import argparse
import datetime
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Table, Column, Integer, ForeignKey, String, DateTime
from sqlalchemy import create_engine
from sqlalchemy.orm import validates
from sqlalchemy.orm import sessionmaker, relationship

Base = declarative_base()
engine = create_engine("sqlite:///biblioteka.db", echo=False)

class Ksiazka(Base):
    __tablename__ = "Ksiazki"
    id = Column(Integer, primary_key=True)
    autor = Column(String(40), nullable=False)
    tytul = Column(String(40), nullable=False)
    rok = Column(Integer, nullable=False)
    wypozyczenia = relationship("Wypozyczenie")

    @validates("rok")
    def validate_rok(self, key, value):
        #sprawdzam czy data wydania książki nie jest z przyszłości
        assert int(value) <= datetime.date.today().year
        return value

class Znajomy(Base):
    __tablename__ = "Znajomi"
    id = Column(Integer, primary_key=True)
    imie = Column(String(20), nullable=False)
    nazwisko = Column(String(20), nullable=False)
    email = Column(String(20), nullable=False)
    wypozyczenia = relationship("Wypozyczenie")

    @validates("email")
    def validate_email(self, key, value):
        #sprawdzam czy w emailu pojawia sie znak @
        assert '@' in value
        return value

class Wypozyczenie(Base):
    __tablename__ = "Wypozyczenia"
    id = Column(Integer, primary_key=True)
    wypozyczajacy = Column(Integer, ForeignKey("Znajomi.id"))
    ksiazka = Column(Integer, ForeignKey("Ksiazki.id"))
    data = Column(DateTime, default = datetime.datetime.utcnow)

    @validates("data")
    def validate_ksiazka(self, key, value):
        #sprawdzam czy nie zaksięgowano wypozyczenia na datę z przyszłości
        assert value < datetime.datetime.utcnow()
        return value

Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)
sesja = Session()
con = sqlite3.connect("biblioteka.db")
cur = con.cursor()

def wypisz_ksiazke(ksiazka, with_id):
    id = ksiazka.id if with_id else "*"
    print("{: <2} {: <30} {: <30} {: <4}".format(id, ksiazka.autor, ksiazka.tytul, ksiazka.rok))

def wypisz_znajomego(znajomy, with_id):
    id = znajomy.id if with_id else "#"
    print("{: <2} {: <30} {: <30} {: <30}".format(id, znajomy.imie, znajomy.nazwisko, znajomy.email))

def wypisz_wypozyczenie(wypozyczenie):
    zn = sesja.query(Znajomy).get(wypozyczenie.wypozyczajacy)
    ks = sesja.query(Ksiazka).get(wypozyczenie.ksiazka)    
    print(str(wypozyczenie.id) + ". " + wypozyczenie.data.strftime("%d/%m/%Y"))
    wypisz_znajomego(zn, False)
    wypisz_ksiazke(ks, False)

def wypisz_ksiazki():
    print("{: <2} {: <30} {: <30} {: <4}".format("Id", "Autor", "Tytuł", "Rok wydania"))
    lista = sesja.query(Ksiazka).all()
    for elem in lista:
        wypisz_ksiazke(elem, True)

def wypisz_znajomych():
    print("{: <2} {: <30} {: <30} {: <30}".format("Id", "Imię", "Nazwisko", "Email"))
    lista = sesja.query(Znajomy).all()
    for elem in lista:
        wypisz_znajomego(elem, True)    

def wypisz_wypozyczenia():
    lista = sesja.query(Wypozyczenie).all()
    for elem in lista:
        wypisz_wypozyczenie(elem)

def dodaj_ksiazke(args):
    if(args.autor and args.tytul and args.rok):
        ks = Ksiazka(autor = args.autor, tytul = args.tytul, rok = args.rok)
        sesja.add(ks)
        sesja.commit()
    else:
        print("Aby dodać ksiażkę podaj jej autora/autorkę, tytuł i rok wydania")

def dodaj_znajomego(args):
    if(args.imie and args.nazwisko and args.email):
        zn = Znajomy(imie = args.imie, nazwisko = args.nazwisko, email = args.email)
        sesja.add(zn)
        sesja.commit()
    else:
        print("Aby dodać znajomego podaj jej imię, nazwisko i email")    
    return

def znajdz_znajomego(args):
    znajomi_filters = []
    if(args.imie):
        znajomi_filters.append(Znajomy.imie==args.imie)
    if(args.nazwisko):
        znajomi_filters.append(Znajomy.nazwisko==args.nazwisko)
    if(args.email):
        znajomi_filters.append(Znajomy.email==args.email)    
    znajomi = sesja.query(Znajomy).filter(*znajomi_filters).all()
    return znajomi

def znajdz_ksiazke(args):
    ksiazki_filters = []
    if(args.autor):
        ksiazki_filters.append(Ksiazka.autor==args.autor)
    if(args.tytul):
        ksiazki_filters.append(Ksiazka.tytul==args.tytul)
    if(args.rok):
        ksiazki_filters.append(Ksiazka.rok==args.rok)    
    ksiazki = sesja.query(Ksiazka).filter(*ksiazki_filters).all()
    return ksiazki


def wypozycz_ksiazke(args):
    znajomi = znajdz_znajomego(args)
    if(len(znajomi)==0):
        print("W bazie danych nie znajduje się znajomy o podanych danych")
        return
    elif(len(znajomi)>1):
        print("Dane dotyczące znajomego są zbyt mało dokładne - odpowiadają conajmniej dwóm znajomym")
        return
    ksiazki = znajdz_ksiazke(args)
    if(len(ksiazki)==0):
        print("W bazie danych nie znajduje się ksiazka o podanych danych")
        return
    elif(len(ksiazki)>1):
        print("Dane dotyczące ksiązki są zbyt mało dokładne - odpowiadają conajmniej dwóm książkom")
        return
    if(args.data):
        wyp = Wypozyczenie(wypozyczajacy = znajomi[0].id, ksiazka = ksiazki[0].id, data = datetime.datetime.strptime(args.data, '%d/%m/%Y'))
    else:
        wyp = Wypozyczenie(wypozyczajacy = znajomi[0].id, ksiazka = ksiazki[0].id)
    sesja.add(wyp)
    sesja.commit()
    return

def oddaj_ksiazke(args):
    znajomi = znajdz_znajomego(args)
    ksiazki = znajdz_ksiazke(args)
    if(len(znajomi) == 0 or len(ksiazki)==0):
        print("Podano błędne dane książki lub znajomego")
        return
    znajomi_id = [z.id for z in znajomi]
    ksiazki_id = [k.id for k in ksiazki]
    pasujacych_wypozyczen = 0
    pas_wyp = None
    wypozyczenia = sesja.query(Wypozyczenie).all()
    for wyp in wypozyczenia:     
        znajomy_id = wyp.wypozyczajacy
        ksiazka_id = wyp.ksiazka
        if(znajomy_id in znajomi_id and ksiazka_id in ksiazki_id):
            if(not args.data or args.data == wyp.data.strftime("%d/%m/%Y")):
                pasujacych_wypozyczen += 1
                pas_wyp = wyp
    if(pasujacych_wypozyczen==0):
        print("Nie zaksięgowano wypożyczenia o podanych danych")
    elif(pasujacych_wypozyczen>1):
        print("Dane dotyczące wypożyczenia są zbyt malo dokładne - odpowiadają conajmniej dwóm zaksięgowanym wypożyczeniom")
    else:
        sesja.delete(pas_wyp)
        sesja.commit()
    return


parser = argparse.ArgumentParser()
action = parser.add_mutually_exclusive_group(required=True)
action.add_argument('-dodaj', help="[ksiazki | znajomi] a następnie odpowiednie argumenty z ksiazka_arg lub znajomy_arg")
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
        wypisz_ksiazki()
    elif(args.wypisz == "znajomi"):
        wypisz_znajomych()
    elif(args.wypisz == "wypozyczenia"):
        wypisz_wypozyczenia()
    else:
        raise Exception("-wypisz [ksiazki | znajomi | wypozyczenia]")

if(args.dodaj):
    if(args.dodaj == "ksiazki"):
        dodaj_ksiazke(args)
    elif(args.dodaj == "znajomi"):
        dodaj_znajomego(args)
    else:
        raise Exception("-dodaj [ksiazki | znajomi]")

if(args.wypozycz):
    wypozycz_ksiazke(args)

if(args.oddaj):
    oddaj_ksiazke(args)

sesja.close()