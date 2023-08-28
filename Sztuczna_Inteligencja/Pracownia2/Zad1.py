'''
Rozwiązanie analogiczne do tego z poprzedniej listy
'''

import random

inp = open('zad_input.txt', 'r')
out = open('zad_output.txt', 'w')
random.seed(100)

def draw(drawing, row, col):
    for i in range(row):
        for j in range(col):
            if drawing[i][j] == 1:
                out.write("#")
            else:
                out.write(".")
        out.write("\n")

def opt_dist_zero(list, blcks, beg):
    blocks = blcks.copy()
    l = len(list)
    i = beg
    while i<l:
        if list[i] == 1:
            if len(blocks)==0 or i+blocks[0]>l:
                return False
            for j in range(blocks[0]):
                if list[i] != 1:
                    return False
                i += 1
            if i<l and list[i] != 0:
                return False
            blocks.pop(0)
        i += 1
    return len(blocks)==0

def opt_dist(list, blocks, beg):
    l = len(list)
    if len(blocks) == 1:
        ones = [0] * (l+1)
        for i in range(l-1, beg-1, -1):
            if list[i]==1:
                ones[i] = ones[i+1] + 1
            else:
                ones[i] = ones[i+1]
        d = blocks[0]
        minimum = d - ones[beg] + 2*ones[beg+d]
        for i in range(l-beg-d+1):
            val = d - 2*ones[beg+i] + 2*ones[beg+i+d] + ones[beg]
            if val < minimum:
                minimum = val
        return minimum
    else:
        zero_pos = opt_dist_zero(list, blocks, beg)
        if zero_pos:
            return 0
        blocks_len = sum(blocks)
        frees = l-beg - blocks_len - len(blocks) + 1
        new_blocks = blocks[1:]
        min = 20
        for i in range(frees+1):
            cur = 0
            for j in range(i):
                cur += list[beg+j]
            for j in range(blocks[0]):
                if list[beg+i+j] == 0:
                    cur += 1
            cur += list[beg+i+blocks[0]]
            cur += opt_dist(list, new_blocks, beg+i+blocks[0]+1)
            if cur < min:
                min = cur
                if min == 1:
                    return min
        return min


def solve(nrows, ncolumns, rows, columns):
    drawing = [[random.randint(0,1) for x in range(ncolumns)] for y in range(nrows)]
    wr_row = []
    wr_col = []
    for i in range(ncolumns):
        column_i = [drawing[j][i] for j in range(nrows)]
        if opt_dist(column_i, columns[i], 0) != 0:
            wr_col.append(i)
    for i in range(nrows):
        if opt_dist(drawing[i], rows[i], 0) != 0:
            wr_row.append(i)

    count = 0
    while(wr_col or wr_row):
        count += 1
        if count >= ncolumns*nrows*10:
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
                old = opt_dist(drawing[rand_row], rows[rand_row], 0) + opt_dist(column_i, columns[i], 0)
                drawing[rand_row][i] ^= 1
                column_i[rand_row] ^= 1
                new = opt_dist(drawing[rand_row], rows[rand_row], 0) + opt_dist(column_i, columns[i], 0)
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
            if opt_dist(drawing[rand_row], rows[rand_row], 0) == 0:
                wr_row.remove(rand_row)
            if opt_dist(column_i, columns[max_pos], 0) == 0 and max_pos in wr_col:
                wr_col.remove(max_pos)
            if opt_dist(column_i, columns[max_pos], 0) > 0 and max_pos not in wr_col:
                wr_col.append(max_pos)
        else:
            rand_col = random.choice(wr_col)
            maximum = -1*(nrows + ncolumns)
            max_pos = -1
            column = [drawing[j][rand_col] for j in range(nrows)]
            for i in range(nrows):
                old = opt_dist(drawing[i], rows[i], 0) + opt_dist(column, columns[rand_col], 0)
                drawing[i][rand_col] ^= 1
                column[i] ^= 1
                new = opt_dist(drawing[i], rows[i], 0) + opt_dist(column, columns[rand_col], 0)
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
            if opt_dist(drawing[max_pos], rows[max_pos], 0) == 0 and max_pos in wr_row:
                wr_row.remove(max_pos)
            if opt_dist(drawing[max_pos], rows[max_pos], 0) > 0 and max_pos not in wr_row:
                wr_row.append(max_pos)
            if opt_dist(column, columns[rand_col], 0) == 0:
                wr_col.remove(rand_col)
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

solve(nrows, ncolumns, rows, columns)

inp.close()
out.close()
