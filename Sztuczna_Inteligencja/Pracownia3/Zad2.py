inp = open('zad_input.txt', 'r')
out = open('zad_output.txt', 'w')
nrows = 0
ncolumns = 0

def free_places(n, desc):
    sum = 0
    for e in desc:
        sum += e
    return n - (sum + len(desc)-1)

def pix_used(v):
    return v>=0 and v%2==1

def pix_emp(v):
    return v>=0 and v%2==0

def draw(drawing, row, col):
    for i in range(row):
        for j in range(col):
            if pix_used(drawing[i][j]):
                out.write("#")
            elif pix_emp(drawing[i][j]):
                out.write(".")
            else:
                out.write("!")
        out.write("\n")

def place_block(nfrees, line, idx, desc, n):
    found = True  
    for i in range(nfrees+1):
        ok = True
        for j in range(i):
            if pix_used(line[idx+j]):
                ok = False
                break
        for j in range(desc[0]):
            if pix_emp(line[idx+i+j]):
                ok = False
                break
        if not ok or (idx+i+desc[0] < n and pix_used(line[idx+i+desc[0]])):
            continue
        if len(desc) == 1:
            ok = True
            for j in range(idx+i+desc[0]+1, n):
                if pix_used(line[j]):
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

def fill_line(n, line, desc, emp, used):
    still_ok = line_still_possible(n, line, desc)
    if not still_ok:
        return (still_ok, 0)
    found = 0
    for i in range(n):
        if line[i] == -1:
            line[i] = used
            p1 = line_still_possible(n, line, desc)
            if not p1:
                line[i] = emp
                found += 1
            else:
                line[i] = emp
                p2 = line_still_possible(n, line, desc)
                if not p2:
                    line[i] = used
                    found += 1
                else:
                    line[i] = -1
    return (True, found)

def first_empty(drawing):
    for i in range(nrows):
        for j in range(ncolumns):
            if drawing[i][j] == -1:
                return (i, j)

def restore(drawing, guess_val, pos):  
    cnt = 0
    for i in range(nrows):
        for j in range(ncolumns):
            if drawing[i][j] == guess_val or drawing[i][j] == guess_val + 1:
                cnt+=1
                drawing[i][j] = -1
    drawing[pos[0]][pos[1]] = guess_val - 2
    return cnt-1
    

def solve(rows, columns):
    drawing = [[-1 for x in range(ncolumns)] for y in range(nrows)]
    left = ncolumns*nrows
    guess = []
    guess_val = 0
    pr = False
    while left > 0:
        beg = left
        wr = False
        for i in range(nrows):
            line = drawing[i]
            res = fill_line(ncolumns, line, rows[i], guess_val, guess_val+1)
            if not res[0]:
                wr = True
                cnt = restore(drawing, guess_val, guess.pop())
                left += cnt
                guess_val -= 2
                break
            else:
                left -= res[1]
        for i in range(ncolumns):
            line = [drawing[j][i] for j in range(nrows)]
            res = fill_line(nrows, line, columns[i], guess_val, guess_val+1)
            if not res[0]:
                cnt = restore(drawing, guess_val, guess.pop())
                left += cnt
                guess_val -= 2
                wr = True
                break
            elif res[1]>0:
                left -= res[1]
                for j in range(nrows):
                    drawing[j][i] = line[j]
        if left == beg and not wr:
            pr = True
            elem = first_empty(drawing)
            guess.append(elem)
            guess_val += 2
            drawing[elem[0]][elem[1]] = guess_val + 1
            left -= 1
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
