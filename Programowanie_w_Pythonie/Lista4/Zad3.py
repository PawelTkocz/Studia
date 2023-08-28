def kopia(s):
    kopia = [[0 for i in range(9)] for j in range(9)]
    for i in range(9):
        for j in range(9):
            kopia[i][j] = s[i][j]
    return kopia

def nastepna_komorka(wiersz, kolumna,  kierunek):
    kolumna += kierunek
    if kolumna == 9:
        kolumna = 0
        wiersz += 1
    elif kolumna < 0:
        kolumna = 8
        wiersz -= 1
    return (wiersz, kolumna)

def sprawdz_poprawnosc(sudoku, wiersz, kolumna):
    x = sudoku[wiersz][kolumna]
    for i in range(9):
        if sudoku[wiersz][i] == x and i != kolumna:
            return False
        if sudoku[i][kolumna] == x and i != wiersz:
            return False
    a = wiersz // 3
    b = kolumna // 3
    for i in range(3):
        for j in range(3):
            if sudoku[3*a+i][3*b+j] == x and (3*a+i != wiersz or 3*b+j != kolumna):
                return False
    return True

def rozwiazanie_sudoku(s):
    sudoku = kopia(s)
    wiersz = 0
    kolumna = 0
    kierunek = 1
    while wiersz >= 0:
        if s[wiersz][kolumna] == 0:
            i = sudoku[wiersz][kolumna] + 1
            while i <= 9:
                sudoku[wiersz][kolumna] = i
                if sprawdz_poprawnosc(sudoku, wiersz, kolumna):
                    break 
                i+=1
            if i > 9:
                sudoku[wiersz][kolumna] = 0
                kierunek = -1            
            else:
                kierunek = 1
        komorka = nastepna_komorka(wiersz, kolumna, kierunek)
        wiersz = komorka[0]
        kolumna = komorka[1]    
        if wiersz == 9:
            yield sudoku
            kierunek = -1
            wiersz = 8
            kolumna = 8
    yield None

def wyswietl_sudoku(sudoku):
    if sudoku == None:
        return
    pozioma_linia = "-" * 25
    print(pozioma_linia)
    for i in range(9):
        print("| ", end="")
        for j in range(9):
            print(sudoku[i][j], end=" ")
            if j%3==2:
                print("|", end=" ")
        print("")
        if i%3==2:
            print(pozioma_linia)

# sudoku_1 ma tylko jedno rozwiązanie
sudoku_1 = [
        [0, 3, 0, 0, 0, 2, 0, 0, 0],
        [0, 8, 0, 0, 0, 0, 0, 0, 7],
        [0, 0, 6, 3, 1, 0, 9, 0, 0],
        [0, 6, 0, 2, 5, 0, 0, 8, 0],
        [0, 0, 0, 0, 0, 4, 5, 0, 0],
        [0, 0, 2, 0, 0, 9, 0, 0, 0],
        [1, 0, 0, 0, 0, 0, 0, 9, 0],
        [0, 0, 0, 0, 4, 0, 0, 0, 0],
        [0, 0, 3, 5, 6, 0, 1, 0, 0]
]

# sudoku_2 powstało przez usunięcie ostatniej cyfry 1 z sudoku_1
# sudoku_2 ma zatem wiele rozwiązań
sudoku_2 = [
        [0, 3, 0, 0, 0, 2, 0, 0, 0],
        [0, 8, 0, 0, 0, 0, 0, 0, 7],
        [0, 0, 6, 3, 1, 0, 9, 0, 0],
        [0, 6, 0, 2, 5, 0, 0, 8, 0],
        [0, 0, 0, 0, 0, 4, 5, 0, 0],
        [0, 0, 2, 0, 0, 9, 0, 0, 0],
        [1, 0, 0, 0, 0, 0, 0, 9, 0],
        [0, 0, 0, 0, 4, 0, 0, 0, 0],
        [0, 0, 3, 5, 6, 0, 0, 0, 0]
]

# sudoku_3 powstalo przez wpisanie do sudoku_1 cyfry 8 w prawym
# dolnym rogu, co sprawia, że sudoku_3 nie ma rozwiazan
sudoku_3 = [
        [0, 3, 0, 0, 0, 2, 0, 0, 0],
        [0, 8, 0, 0, 0, 0, 0, 0, 7],
        [0, 0, 6, 3, 1, 0, 9, 0, 0],
        [0, 6, 0, 2, 5, 0, 0, 8, 0],
        [0, 0, 0, 0, 0, 4, 5, 0, 0],
        [0, 0, 2, 0, 0, 9, 0, 0, 0],
        [1, 0, 0, 0, 0, 0, 0, 9, 0],
        [0, 0, 0, 0, 4, 0, 0, 0, 0],
        [0, 0, 3, 5, 6, 0, 1, 0, 8]
]

wyswietl_sudoku(sudoku_1)
for rozwiazanie in rozwiazanie_sudoku(sudoku_1):
    wyswietl_sudoku(rozwiazanie)

#wyswietl_sudoku(sudoku_2)
#for rozwiazanie in rozwiazanie_sudoku(sudoku_2):
#    wyswietl_sudoku(rozwiazanie)

#wyswietl_sudoku(sudoku_3)
#for rozwiazanie in rozwiazanie_sudoku(sudoku_3):
#    wyswietl_sudoku(rozwiazanie)