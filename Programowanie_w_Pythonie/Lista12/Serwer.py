import sqlite3
import datetime
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Table, Column, Integer, ForeignKey, String, DateTime
from sqlalchemy import create_engine
from sqlalchemy.orm import validates
from sqlalchemy.orm import sessionmaker, relationship
from xmlrpc.server import SimpleXMLRPCServer

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

def lista_ksiazek():
    res = []
    lista = sesja.query(Ksiazka).all()
    for elem in lista:
        res.append((elem.id, elem.autor, elem.tytul, elem.rok))
    return res

def lista_znajomych():
    res = []
    lista = sesja.query(Znajomy).all()
    for elem in lista:
        res.append((elem.id, elem.imie, elem.nazwisko, elem.email))
    return res    

def lista_wypozyczen():
    res = []
    lista = sesja.query(Wypozyczenie).all()
    for elem in lista:
        zn = sesja.query(Znajomy).get(elem.wypozyczajacy)
        ks = sesja.query(Ksiazka).get(elem.ksiazka)   
        res.append((elem.id, elem.data.strftime("%d/%m/%Y"), zn.imie, zn.nazwisko, zn.email, ks.autor, ks.tytul, ks.rok))
    return res

def dodaj_ksiazke(autor, tytul, rok):
    if(autor and tytul and rok):
        ks = Ksiazka(autor = autor, tytul = tytul, rok = rok)
        sesja.add(ks)
        sesja.commit()
        return (True, "")
    else:
        return (False, "Aby dodać ksiażkę podaj jej autora/autorkę, tytuł i rok wydania")

def dodaj_znajomego(imie, nazwisko, email):
    if(imie and nazwisko and email):
        zn = Znajomy(imie = imie, nazwisko = nazwisko, email = email)
        sesja.add(zn)
        sesja.commit()
        return (True, "")
    else:
        return (False, "Aby dodać znajomego podaj jej imię, nazwisko i email")

def znajdz_znajomego(imie, nazwisko, email):
    znajomi_filters = []
    if(imie):
        znajomi_filters.append(Znajomy.imie==imie)
    if(nazwisko):
        znajomi_filters.append(Znajomy.nazwisko==nazwisko)
    if(email):
        znajomi_filters.append(Znajomy.email==email)    
    znajomi = sesja.query(Znajomy).filter(*znajomi_filters).all()
    return znajomi

def znajdz_ksiazke(autor, tytul, rok):
    ksiazki_filters = []
    if(autor):
        ksiazki_filters.append(Ksiazka.autor==autor)
    if(tytul):
        ksiazki_filters.append(Ksiazka.tytul==tytul)
    if(rok):
        ksiazki_filters.append(Ksiazka.rok==rok)    
    ksiazki = sesja.query(Ksiazka).filter(*ksiazki_filters).all()
    return ksiazki

def usun_znajomego(imie, nazwisko, email):
    znajomi = znajdz_znajomego(imie, nazwisko, email)
    if len(znajomi)==0:
       return (False, "W bazie danych nie znajduje się znajomy o podanych danych")
    elif len(znajomi)>1:
        return (False, "Dane dotyczące znajomego są zbyt mało dokładne - odpowiadają conajmniej dwóm znajomym") 
    else:
        sesja.delete(znajomi[0])
        sesja.commit()
        return (True, "")

def usun_ksiazke(autor, tytul, rok):
    ksiazki = znajdz_ksiazke(autor, tytul, rok)
    if len(ksiazki)==0:
        return (False, "W bazie danych nie znajduje się ksiazka o podanych danych")
    elif len(ksiazki)>1:
        return (False, "Dane dotyczące ksiązki są zbyt mało dokładne - odpowiadają conajmniej dwóm książkom")
    else:
        sesja.delete(ksiazki[0])
        sesja.commit()
        return (True, "")

def wypozycz_ksiazke(imie, nazwisko, email, autor, tytul, rok, data):
    znajomi = znajdz_znajomego(imie, nazwisko, email)
    if len(znajomi)==0:
        return (False, "W bazie danych nie znajduje się znajomy o podanych danych")
    elif len(znajomi)>1:
        return (False, "Dane dotyczące znajomego są zbyt mało dokładne - odpowiadają conajmniej dwóm znajomym")
    ksiazki = znajdz_ksiazke(autor, tytul, rok)
    if len(ksiazki)==0:
        return (False, "W bazie danych nie znajduje się ksiazka o podanych danych")
    elif len(ksiazki)>1:
        return (False, "Dane dotyczące ksiązki są zbyt mało dokładne - odpowiadają conajmniej dwóm książkom")
    if(data):
        wyp = Wypozyczenie(wypozyczajacy = znajomi[0].id, ksiazka = ksiazki[0].id, data = datetime.datetime.strptime(data, '%d/%m/%Y'))
    else:
        wyp = Wypozyczenie(wypozyczajacy = znajomi[0].id, ksiazka = ksiazki[0].id)
    sesja.add(wyp)
    sesja.commit()
    return (True, "")

def oddaj_ksiazke(imie, nazwisko, email, autor, tytul, rok, data):
    znajomi = znajdz_znajomego(imie, nazwisko, email)
    ksiazki = znajdz_ksiazke(autor, tytul, rok)
    if(len(znajomi) == 0 or len(ksiazki)==0):
        return (False, "Podano błędne dane książki lub znajomego")
    znajomi_id = [z.id for z in znajomi]
    ksiazki_id = [k.id for k in ksiazki]
    pasujacych_wypozyczen = 0
    pas_wyp = None
    wypozyczenia = sesja.query(Wypozyczenie).all()
    for wyp in wypozyczenia:     
        znajomy_id = wyp.wypozyczajacy
        ksiazka_id = wyp.ksiazka
        if(znajomy_id in znajomi_id and ksiazka_id in ksiazki_id):
            if(not data or data == wyp.data.strftime("%d/%m/%Y")):
                pasujacych_wypozyczen += 1
                pas_wyp = wyp
    if pasujacych_wypozyczen==0:
        return (False, "Nie zaksięgowano wypożyczenia o podanych danych")
    elif pasujacych_wypozyczen>1:
        return (False, "Dane dotyczące wypożyczenia są zbyt malo dokładne - odpowiadają conajmniej dwóm zaksięgowanym wypożyczeniom")
    else:
        sesja.delete(pas_wyp)
        sesja.commit()
    return (True, "")


server = SimpleXMLRPCServer(('localhost', 8002))
server.register_function(lista_ksiazek)
server.register_function(lista_znajomych)
server.register_function(lista_wypozyczen)
server.register_function(dodaj_ksiazke)
server.register_function(dodaj_znajomego)
server.register_function(usun_ksiazke)
server.register_function(usun_znajomego)
server.register_function(wypozycz_ksiazke)
server.register_function(oddaj_ksiazke)
server.serve_forever()

sesja.close()