import decimal as d

def vat_faktura(lista):
    suma = 0
    for e in lista:
        suma += e
    return 0.23 * suma

def vat_paragon(lista):
    vat = 0
    for e in lista:
        vat += 0.23 * e
    return vat

def vat_faktura_decimal(lista):
    suma = d.Decimal('0');
    for e in lista:
        suma += e
    return d.Decimal('0.23') * suma

def vat_paragon_decimal(lista):
    vat = d.Decimal('0');
    for e in lista:
        vat += d.Decimal('0.23') * e
    return vat

zakupy = [0.2, 0.5, 4.59, 6]
zakupy_decimal = [d.Decimal('0.2'), d.Decimal('0.5'), d.Decimal('4.59'), d.Decimal('6')]

print(vat_faktura(zakupy))
print(vat_paragon(zakupy))
print(vat_faktura(zakupy) == vat_paragon(zakupy))

print("")

print(vat_faktura_decimal(zakupy_decimal))
print(vat_paragon_decimal(zakupy_decimal))
print(vat_faktura_decimal(zakupy_decimal) == vat_paragon_decimal(zakupy_decimal))
print("Reprezentacja liczb za pomocą klasy Decimal daje inną odpowiedź")
