def opt_dist(list, d):
    l = len(list)
    ones = [0] * (l+1)

    for i in range(l-1, -1, -1):
        if list[i]=='1':
            ones[i] = ones[i+1] + 1
        else:
            ones[i] = ones[i+1]

    if d==0:
        return ones[0]

    minimum = d - ones[0] + 2*ones[d]
    for i in range(l-d+1):
        val = d - 2*ones[i] + 2*ones[i+d] + ones[0]
        if val < minimum:
            minimum = val
    return minimum

inp = open('zad4_input.txt', 'r')
out = open('zad4_output.txt', 'w')

line =  inp.readline()
while line:
    args = line.split()
    lst = args[0]
    d = args[1]
    res = opt_dist(list(lst), eval(d))
    out.write(str(res))
    out.write("\n")
    line = inp.readline()
inp.close()