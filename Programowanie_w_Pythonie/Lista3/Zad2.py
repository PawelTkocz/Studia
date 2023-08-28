import timeit

def doskonale_imperatywna(n):
    res = []
    for i in range(2, n+1):
        suma = 0
        for j in range(1, i):
            if i % j == 0:
                suma += j
        if suma == i:
            res.append(i)
    return res

def doskonale_skladana(n):
    res = [i for i in range(2, n+1) if sum([y for y in range (1, i) if i%y==0])==i]
    return res

def doskonale_funkcyjna(n):
    res = list(range(2, n+1))
    res = list(filter(lambda x: sum([y for y in range(1, x) if x%y==0])==x, res))
    return res

def czas(n, f):
    SETUP_CODE = "from __main__ import " + f
    TEST_CODE = f + "(" + str(n) + ")"
    times = timeit.repeat(setup = SETUP_CODE,
                          stmt = TEST_CODE,
                          repeat = 2,
                          number = 30)
    t_avg = sum(times)/len(times)
    return round(t_avg, 3)

def czas_tabelka():
    czasy = []
    for i in range(100, 1000, 200):
        czasy.append([str(i)+":", czas(i, "doskonale_imperatywna"), czas(i, "doskonale_skladana"), czas(i, "doskonale_funkcyjna")])
    headers = ["n ", "imperatywna", "skladana", "funkcyjna"]
    print ("".join(header.rjust(12) for header in headers))
    for row in czasy:
        print ("".join(str(time).rjust(12) for time in row))


print(doskonale_imperatywna(10000))
print(doskonale_skladana(10000))
print(doskonale_funkcyjna(10000))
czas_tabelka()
