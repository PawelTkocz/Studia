'''
Postępuję zgodnie z krokami opisanymi w poleceniu
'''

import random

inp = open('zad5_input.txt', 'r')
random.seed()

def draw(drawing, row, col):
    for i in range(row):
        for j in range(col):
            if drawing[i][j] == 1:
                out.write("#")
            else:
                out.write(".")
        out.write("\n")

def opt_dist(list, d):
    l = len(list)
    ones = [0] * (l+1)

    for i in range(l-1, -1, -1):
        if list[i]==1:
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

def solve(nrows, ncolumns, rows, columns):
    drawing = [[random.randint(0,1) for x in range(ncolumns)] for y in range(nrows)]
    wr_row = []
    wr_col = []
    for i in range(ncolumns):
        column_i = [drawing[j][i] for j in range(nrows)]
        if opt_dist(column_i, columns[i]) != 0:
            wr_col.append(i)
    for i in range(nrows):
        if opt_dist(drawing[i], rows[i]) != 0:
            wr_row.append(i)

    count = 0
    while(wr_col or wr_row):
        count += 1
        if count >= 100:
            return solve(nrows, ncolumns, rows, columns)

        if not wr_col:
            change_row = True
        elif not wr_row:
            change_row = False
        else:
            change_row = (random.randint(0,1)==0)

        if change_row:
            rand_row = random.choice(wr_row)
            maximum = -1*(nrows + ncolumns)
            max_pos = -1
            for i in range(ncolumns):
                column_i = [drawing[j][i] for j in range(nrows)]
                old = opt_dist(drawing[rand_row], rows[rand_row]) + opt_dist(column_i, columns[i])
                drawing[rand_row][i] ^= 1
                column_i[rand_row] ^= 1
                new = opt_dist(drawing[rand_row], rows[rand_row]) + opt_dist(column_i, columns[i])
                drawing[rand_row][i] ^= 1
                column_i[rand_row] ^= 1
                val = old-new
                if val > maximum:
                    maximum = val
                    max_pos = i
                elif val == maximum and random.randint(0,1):
                    maximum = val
                    max_pos = i                    
            drawing[rand_row][max_pos] ^= 1
            column_i = [drawing[j][max_pos] for j in range(nrows)]
            if opt_dist(drawing[rand_row], rows[rand_row]) == 0:
                wr_row.remove(rand_row)
            if opt_dist(column_i, columns[max_pos]) == 0 and max_pos in wr_col:
                wr_col.remove(max_pos)
            if opt_dist(column_i, columns[max_pos]) > 0 and max_pos not in wr_col:
                wr_col.append(max_pos)
        else:
            rand_col = random.choice(wr_col)
            maximum = -1*(nrows + ncolumns)
            max_pos = -1
            column = [drawing[j][rand_col] for j in range(nrows)]
            for i in range(nrows):
                old = opt_dist(drawing[i], rows[i]) + opt_dist(column, columns[rand_col])
                drawing[i][rand_col] ^= 1
                column[i] ^= 1
                new = opt_dist(drawing[i], rows[i]) + opt_dist(column, columns[rand_col])
                drawing[i][rand_col] ^= 1
                column[i] ^= 1
                val = old-new
                if val > maximum:
                    maximum = val
                    max_pos = i
                elif val == maximum and random.randint(0,1):
                    maximum = val
                    max_pos = i              
            drawing[max_pos][rand_col] ^= 1
            column[max_pos] ^= 1
            if opt_dist(drawing[max_pos], rows[max_pos]) == 0 and max_pos in wr_row:
                wr_row.remove(max_pos)
            if opt_dist(drawing[max_pos], rows[max_pos]) > 0 and max_pos not in wr_row:
                wr_row.append(max_pos)
            if opt_dist(column, columns[rand_col]) == 0:
                wr_col.remove(rand_col)
    draw(drawing, nrows, ncolumns)


out = open('zad5_output.txt', 'w')

line =  inp.readline()
args = line.split()
nrows = eval(args[0])
ncolumns = eval(args[1])
rows = [0] * nrows
columns = [0] * ncolumns

for i in range(nrows):
    line =  inp.readline()
    args = line.split()
    val = eval(args[0])
    rows[i] = val

for i in range(ncolumns):
    line =  inp.readline()
    args = line.split()
    val = eval(args[0])
    columns[i] = val

solve(nrows, ncolumns, rows, columns)

inp.close()
out.close()
