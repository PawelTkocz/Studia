#Zadanie 1 Wersja B

class Wyrazenie:
    def __add__(self, arg):
        return Dodaj(self, arg)

    def __mul__(self, arg):
        return Razy(self, arg)

    def __str__(self):
        pass

    def oblicz(self, zmienne):
        pass

    @staticmethod
    def uprosc1(w):
        if isinstance(w, Zmienna) or isinstance(w, Stala):
            return w
        else:
            w1 = Wyrazenie.uprosc1(w.arg1)
            w2 = Wyrazenie.uprosc1(w.arg2)
            if isinstance(w1, Stala) and isinstance(w2, Stala):
                return Stala(w.oblicz({}))
            else:
                if isinstance(w, Razy):
                    return Razy(w1, w2)
                elif isinstance(w, Dodaj):
                    return Dodaj(w1, w2)
                elif isinstance(w, Odejmij):
                    return Odejmij(w1, w2)
                else:
                    return Podziel(w1, w2)

    @staticmethod
    def uprosc2(w):
        if isinstance(w, Zmienna) or isinstance(w, Stala):
            return w
        else:
            w1 = Wyrazenie.uprosc2(w.arg1)
            w2 = Wyrazenie.uprosc2(w.arg2)
            if isinstance(w, Razy):
                if (isinstance(w1, Stala) and w1.oblicz({}) == 0) or (isinstance(w2, Stala) and w2.oblicz({}) == 0):
                    return Stala(0)
                return Razy(w1, w2)
            elif isinstance(w, Dodaj):
                if (isinstance(w1, Stala) and w1.oblicz({}) == 0):
                    return w2
                elif (isinstance(w2, Stala) and w2.oblicz({}) == 0):
                    return w1
                return Dodaj(w1, w2)
            elif isinstance(w, Odejmij):
                if (isinstance(w1, Stala) and w1.oblicz({}) == 0):
                    return Razy(Stala(-1), w2)
                elif (isinstance(w2, Stala) and w2.oblicz({}) == 0):
                    return w1
                return Odejmij(w1, w2)
            else:
                if (isinstance(w1, Stala) and w1.oblicz({}) == 0) and (isinstance(w2, Stala) and w2.oblicz({}) != 0):
                    return Stala(0)
                return Podziel(w1, w2)
        
class Razy(Wyrazenie):
    def __init__(self, arg1, arg2):
        self.arg1 = arg1
        self.arg2 = arg2

    def oblicz(self, zmienne):
        return self.arg1.oblicz(zmienne) * self.arg2.oblicz(zmienne)

    def __str__(self):
        return self.arg1.__str__() + ' * ' + self.arg2.__str__()

class Dodaj(Wyrazenie):
    def __init__(self, arg1, arg2):
        self.arg1 = arg1
        self.arg2 = arg2

    def oblicz(self, zmienne):
        return self.arg1.oblicz(zmienne) + self.arg2.oblicz(zmienne)

    def __str__(self):
        return '(' + self.arg1.__str__() + ' + ' + self.arg2.__str__() + ')'

class Odejmij(Wyrazenie):
    def __init__(self, arg1, arg2):
        self.arg1 = arg1
        self.arg2 = arg2

    def oblicz(self, zmienne):
        return self.arg1.oblicz(zmienne) - self.arg2.oblicz(zmienne)

    def __str__(self):
        return '(' + self.arg1.__str__() + ' - ' + self.arg2.__str__() + ')'

class Podziel(Wyrazenie):
    def __init__(self, arg1, arg2):
        self.arg1 = arg1
        self.arg2 = arg2

    def oblicz(self, zmienne):
        mianownik = self.arg2.oblicz(zmienne)
        if mianownik == 0:
            raise DivisionByZero("Proba dzielenia przez zero")
        else:
            return self.arg1.oblicz(zmienne) / mianownik

    def __str__(self):
        return self.arg1.__str__() + ' / ' + self.arg2.__str__()

class Zmienna(Wyrazenie):
    def __init__(self, nazwa):
        self.nazwa = nazwa

    def oblicz(self, zmienne):
        if self.nazwa not in zmienne.keys():
            raise VariableNotFoundException("Zmienna " + self.nazwa + " nie ma przypisanej wartosci")
        else:
            return zmienne[self.nazwa]

    def __str__(self):
        return self.nazwa

class Stala(Wyrazenie):
    def __init__(self, stala):
        self.stala = stala

    def oblicz(self, zmienne):
        return self.stala

    def __str__(self):
        return str(self.stala)

class VariableNotFoundException(Exception):
    pass

class DivisionByZero(Exception):
    pass

# a = (x + 2) * y
a = Razy(Dodaj(Zmienna("x"), Stala(2)), Zmienna("y"))
# b = (2 + 3) * (x + (6 - 1))
b = Razy(Dodaj(Stala(2), Stala(3)), Dodaj(Zmienna("x"), Odejmij(Stala(6), Stala(1))))
# c = ((4 - 4) * x) + (y - 0)
c = Dodaj(Razy(Odejmij(Stala(4), Stala(4)), Zmienna("x")), (Odejmij(Zmienna("y"), Stala(0))))

print(f"Wyrazenie a: {a.__str__()}")
zmienne_a = {
    "x": 7,
    "y": 1
}
print(f"Wartosc wyrazenia a: {a.oblicz(zmienne_a)}")
print(f"Wyrazenie b: {b.__str__()}")
zmienne_b = {
    "x": 3,
}
print(f"Wartosc wyrazenia b: {b.oblicz(zmienne_b)}")
print(f"Uproszczone wyrazenie b: {Wyrazenie.uprosc1(b).__str__()}")
print(f"Wyrazenie c: {c.__str__()}")
zmienne_c = {
    "x": 3,
    "y": 14
}
print(f"Wartosc wyrazenia c: {c.oblicz(zmienne_c)}")
print(f"Uproszczone wyrazenie c: {Wyrazenie.uprosc2(Wyrazenie.uprosc1(c)).__str__()}")

d = a.__add__(b.__mul__(c))
print(f"Wyrazenie d: {d.__str__()}")
print(f"Uproszczone wyrazenie d: {Wyrazenie.uprosc2(Wyrazenie.uprosc1(d)).__str__()}")
