import timeit

def pierwsze_imperatywna(n):
    res = []
    for i in range(2, n+1):
        prime = True
        for j in range(2, i):
            if i % j == 0:
                prime = False
        if prime:
            res.append(i)
    return res

def pierwsze_skladana(n):
    res = [i for i in range(2, n+1) if all(i % y != 0 for y in range (2, i))]
    return res

def pierwsze_funkcyjna(n):
    res = list(range(2, n+1))
    for i in range(2, n+1):
        res = list(filter(lambda x: x==i or x%i != 0, res))
    return res

def czas(n, f):
    SETUP_CODE = "from __main__ import " + f
    TEST_CODE = f + "(" + str(n) + ")"
    times = timeit.repeat(setup = SETUP_CODE,
                          stmt = TEST_CODE,
                          repeat = 2,
                          number = 1000)
    time_avg = sum(times)/len(times)
    return round(time_avg, 3)

def czas_tabelka():
    czasy = []
    for i in range(10, 100, 10):
        czasy.append([str(i)+":", czas(i, "pierwsze_imperatywna"), czas(i, "pierwsze_skladana"), czas(i, "pierwsze_funkcyjna")])
    headers = ["n ", "imperatywna", "skladana", "funkcyjna"]
    print ("".join(header.rjust(12) for header in headers))
    for row in czasy:
        print ("".join(str(time).rjust(12) for time in row))


print(pierwsze_imperatywna(20))
print(pierwsze_skladana(20))
print(pierwsze_funkcyjna(20))
czas_tabelka()
