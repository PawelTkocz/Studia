def two_dim_list(y):
    #funkcja tworzy listę y pustych list
    res = []
    for i in range(y):
        res.append([])
    return res

def negative_results(x1, y1):
    #funkcja zwraca 1 jesli w tabliczce
    #pojawia sie ujemna liczba, 0 wpp.
    if x1 < 0 or y1 < 0 :
        return 1
    else:
        return 0

def max_abs_val(x1, x2, y1, y2):
    #funckja zwraca największą wartość bezwzględną
    #ze wszystkich otrzymanych wyników mnożenia
    v1 = abs(x1*y1)
    v2 = abs(x1*y2)
    v3 = abs(x2*y1)
    v4 = abs(x2*y2)
    return max(v1, v2, v3, v4)

def digits(x):
    #funkcja zwraca dla liczby całkowitej jej liczbę cyfr
    #licząc ewentualny znak '-' jako cyfrę
    return len(str(x))

def print_mul_table(x1, x2, y1, y2, res):
    #funkcja wypisująca tabliczkę mnożenia
    minus = negative_results(x1, y1)
    most_digits = digits(max_abs_val(x1, x2, y1, y2))
    column_width = most_digits + minus
    print(" " * column_width, end=" ")
    for i in range(x1, x2 + 1):
        print(" " * (column_width - digits(i)) + str(i), end = " ")
    print("")
    for i in range(y2-y1+1):
        print(" " * (column_width - digits(y1+i)) + str(y1+i), end = " ")
        for j in range(x2-x1+1):
            print(" " * (column_width - digits(res[i][j])) + str(res[i][j]), end = " ")
        print("")

def tabliczka(x1, x2, y1, y2):
    res = two_dim_list(y2 - y1 + 1)
    for i in range(y1, y2+1):
        for j in range(x1, x2+1):
            res[i-y1].append(i*j)
    print_mul_table(x1, x2, y1, y2, res)

tabliczka(-4, 6, -1, 9)