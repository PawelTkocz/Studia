inp = open('zad_input.txt', 'r')
out = open('zad_output.txt', 'w')
nrows = 0
ncolumns = 0

def draw(drawing, row, col):
    for i in range(row):
        for j in range(col):
            if drawing[i][j] == 1:
                out.write("#")
            elif drawing[i][j] == 0:
                out.write(".")
            else:
                out.write("!")
        out.write("\n")

def free_places(n, desc):
    sum = 0
    for e in desc:
        sum += e
    return n - (sum + len(desc)-1)

def place_block(nfrees, line, idx, desc, n):
    found = True  
    for i in range(nfrees+1):
        ok = True
        for j in range(i):
            if line[idx+j] == 1:
                ok = False
                break
        for j in range(desc[0]):
            if line[idx+i+j] == 0:
                ok = False
                break
        if not ok or (idx+i+desc[0] < n and line[idx+i+desc[0]] == 1):
            continue
        if len(desc) == 1:
            ok = True
            for j in range(idx+i+desc[0]+1, n):
                if line[j] == 1:
                    ok = False
                    break
            if ok:
                return True
        else:
            found =  place_block(nfrees-i, line, idx+i+desc[0]+1, desc[1:], n)
            if found:
                return True
    return False

def line_still_possible(n, line, desc):
    nfrees = free_places(n, desc)
    return place_block(nfrees, line, 0, desc, n)

def fill_line(n, line, desc):
    found = 0
    for i in range(n):
        if line[i] == 2:
            line[i] = 1
            p1 = line_still_possible(n, line, desc)
            if not p1:
                line[i] = 0
                found += 1
            else:
                line[i] = 0
                p2 = line_still_possible(n, line, desc)
                if not p2:
                    line[i] = 1
                    found += 1
                else:
                    line[i] = 2
    return (found, line)

def solve(rows, columns):
    drawing = [[2 for x in range(ncolumns)] for y in range(nrows)]
    left = ncolumns*nrows
    while left > 0:
        for i in range(nrows):
            line = drawing[i]
            res = fill_line(ncolumns, line, rows[i])
            left -= res[0]
        for i in range(ncolumns):
            line = [drawing[j][i] for j in range(nrows)]
            res = fill_line(nrows, line, columns[i])
            if res[0]>0:
                left -= res[0]
                for j in range(nrows):
                    drawing[j][i] = line[j]
    draw(drawing, nrows, ncolumns)


line =  inp.readline()
args = line.split()
nrows = eval(args[0])
ncolumns = eval(args[1])
rows = [ [] for _ in range(nrows)]
columns = [ [] for _ in range(ncolumns)]

for i in range(nrows):
    line =  inp.readline()
    args = line.split()
    for j in args:
        rows[i].append(eval(j))

for i in range(ncolumns):
    line =  inp.readline()
    args = line.split()
    for j in args:
        columns[i].append(eval(j))

solve(rows, columns)

inp.close()
out.close()
