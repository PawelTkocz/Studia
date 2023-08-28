def pierwiastek(n):
    if n < 0:
        print("sqrt(" + str(n) + ") nie ma rozwiazania w liczbach rzeczywistych")
        return -1
    i = 0
    sum = 0
    while sum <= n:
        sum += 2*i+1
        i+=1
    return i-1


for i in range(20):
    sqrt = pierwiastek(i)
    if(sqrt != -1):
        print("sqrt(" + str(i) + ") = " + str(pierwiastek(i)))
