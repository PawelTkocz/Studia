import sys

def B(i,j):
    return 'B_%d_%d' % (i,j)
    
def domains(Bs):
    return [ q + ' in 0..1' for q in Bs ]

def writeln(s):
    output.write(s + '\n')

def write_out(s):
    output.write(s)
    
def sum_line(Qs, v):
    return 'sum([' + ', '.join(Qs) + '], #=, ' + str(v) + ')'

def three_ok(Qs):
    return str(Qs[0]) + ' + 2 * ' + str(Qs[1]) + ' + 3 * ' + str(Qs[2]) + ' #\= 2'

def four_ok_1(Qs):
    return 'sum([' + ', '.join(Qs) + '], #\=, 3)'

def four_ok_2(Qs):
    return '( ' + str(Qs[0]) + ' + ' + str(Qs[3]) + ' + 1 ) * ( ' + str(Qs[1]) + ' + ' + str(Qs[2]) + ' + 1 ) #\= 3'

def get_column(ncolumn, nrows):
    return [B(i,ncolumn) for i in range(nrows)] 
            
def get_raw(nrow, ncolumns):
    return [B(nrow,j) for j in range(ncolumns)] 
                        
def horizontal(nrows, ncolumns, rows):   
    return [ sum_line(get_raw(i, ncolumns), rows[i]) for i in range(nrows)]

def vertical(nrows, ncolumns, columns):
    return [ sum_line(get_column(j, nrows), columns[j]) for j in range(ncolumns)]

def thrs_from_line(line, l):
    res = []
    for i in range(2, l):
        res.append((line[i-2], line[i-1], line[i]))
    return res

def get_all_threes(nrows, ncolumns):
    res = []
    for y in range(nrows):
        r = get_raw(y, ncolumns)
        thrs = thrs_from_line(r, ncolumns)
        res.extend(thrs)
    for x in range(ncolumns):
        c = get_column(x, nrows)
        thrs = thrs_from_line(c, nrows)
        res.extend(thrs)
    return res

def get_all_fours(nrows, ncolumns):
    res = []
    for y in range(2, nrows):
        for x in range(2, ncolumns):
            res.append((B(y-1, x-1), B(y-1, x), B(y, x-1), B(y, x)))
    return res

def forbiden_threes(nrows, ncolumns):
    threes = get_all_threes(nrows, ncolumns)
    return [ three_ok(t) for t in threes]

def forbiden_fours_1(nrows, ncolumns):
    fours = get_all_fours(nrows, ncolumns)
    return [ four_ok_1(f) for f in fours]

def forbiden_fours_2(nrows, ncolumns):
    fours = get_all_fours(nrows, ncolumns)
    return [ four_ok_2(f) for f in fours]

def print_constraints(Cs, indent, d):
    position = indent
    write_out(indent * ' ')
    for c in Cs:
        write_out(c + ', ')
        position += len(c)
        if position > d:
            position = indent
            writeln('')
            write_out(indent * ' ')


def storms(rows, cols, triples):
    writeln(':- use_module(library(clpfd)).') 
    R = len(rows)
    C = len(cols)
    bs = [ B(i,j) for i in range(R) for j in range(C)]
    writeln('solve([' + ', '.join(bs) + ']) :- ')
    
    cs = domains(bs) + horizontal(R, C, rows) + vertical(R, C, cols) + forbiden_threes(R, C) + forbiden_fours_1(R, C) + forbiden_fours_2(R, C)
    for i,j,val in triples:
        cs.append( '%s #= %d' % (B(i,j), val) )
    print_constraints(cs, 4, 70), 

    writeln('    labeling([ff], [' +  ', '.join(bs) + ']).' )
    writeln('')
    writeln(":- tell('prolog_result.txt'), solve(X), write(X), nl, told.")


txt = open('zad_input.txt').readlines()
output = open('zad_output.txt', 'w')
rows = list(map(int, txt[0].split()))
cols = list(map(int, txt[1].split()))
triples = []
for i in range(2, len(txt)):
    if txt[i].strip():
        triples.append(map(int, txt[i].split()))
storms(rows, cols, triples) 