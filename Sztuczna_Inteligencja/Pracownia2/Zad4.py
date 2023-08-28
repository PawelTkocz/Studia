'''
Przed wyknaniem BFS wykonuje proces zmniejszenia niepewności.
Proces ten wykonuje się w pętli aż do momentu, gdy w labiryncie
pozostaną tylko dwie możliwe pozycje komandosa. Przebiega on w
następujący sposób: sprawdzam, czy 
(*) wykonując pewną liczbę ruchów tylko w poziomie lub tylko w pionie
    pewne pozycje komandosa pokryją się
jeśli tak, to wykonuję te ruchy. Jeśli nie, szukam możliwie najkrótszej
kombinacji losowych ruchów, która sprawi, że (*) będzie możliwa
'''

import random
inp = open('zad_input.txt', 'r')
out = open('zad_output.txt', 'w')
maze = [[]]
positions = set()
random.seed(100)

def start_point(m):
    return m == 'S' or m == 'B'

def print_maze(w, h):
    return 0
    for i in range(h):
        for j in range(w):
            print(maze[i][j], end="")
        print("")

def moves_vertical(w, h):
    max_u = 0
    max_d = 0
    found = False
    for x in range(1, w-1):
        cur_u = 0
        cur_d = 0
        d = 0
        s = False
        for y in range(h):
            if maze[y][x] == '#':
                if cur_d > max_d:
                    max_d = cur_d
                cur_d = 0
                cur_u = 0
                d = 0
                s = False
            else:
                cur_d += d
                if start_point(maze[y][x]):
                    if s == True:
                        found = True
                    else:
                        s = True
                    d = 1
                    if cur_u > max_u:
                        max_u = cur_u
                cur_u += 1
    if max_u < max_d:
        return (max_u, 'U', found)
    else:
        return (max_d, 'D', found)

def modify_maze_vertic(w, h, dir):
    st = h-2
    dif = -1
    if dir == 'D':
        st = 1
        dif = 1

    for x in range(1, w-1):
        found = False
        for y in range(st, st+dif*(h-1), dif):
            if start_point(maze[y][x]):
                found = True
                if maze[y][x] == 'S':
                    maze[y][x] = ' '
                else:
                    maze[y][x] = 'G'
            elif maze[y][x] == '#':
                if found:
                    if maze[y-dif][x] == ' ':
                        maze[y-dif][x] = 'S'
                    else:
                        maze[y-dif][x] = 'B'
                found = False

def moves_horizon(w, h):
    max_l = 0
    max_r = 0
    found = False
    for y in range(1, h-1):
        cur_l = 0
        cur_r = 0
        r = 0
        s = False
        for x in range(w):
            if maze[y][x] == '#':
                if cur_r > max_r:
                    max_r = cur_r
                cur_r = 0
                cur_l = 0
                r = 0
                s = False
            else:
                cur_r += r
                if start_point(maze[y][x]):
                    if s == True:
                        found = True
                    else:
                        s = True
                    r = 1
                    if cur_l > max_l:
                        max_l = cur_l
                cur_l += 1
    if max_l < max_r:
        return (max_l, 'L', found)
    else:
        return (max_r, 'R', found)

def modify_maze_horizon(w, h, dir):
    st = w-2
    dif = -1
    if dir == 'R':
        st = 1
        dif = 1
    for y in range(1, h-1):
        found = False
        for x in range(st, st+dif*(w-1), dif):
            if start_point(maze[y][x]):
                found = True
                if maze[y][x] == 'S':
                    maze[y][x] = ' '
                else:
                    maze[y][x] = 'G'
            elif maze[y][x] == '#':
                if found:
                    if maze[y][x-dif] == ' ':
                        maze[y][x-dif] = 'S'
                    else:
                        maze[y][x-dif] = 'B'
                found = False

def get_starts(w, h):
    starts = []
    for y in range(h):
        for x in range(w):
            if start_point(maze[y][x]):
                starts.append((y, x))
    return starts

def random_moves(n):
    dirs = ['U', 'D', 'L', 'R']
    res = []
    for i in range(n):
        d = random.choice(dirs)
        res.append(d)
    return res

def make_horizon_moves(w, h):
    res = []
    horizon = moves_horizon(w, h)
    if horizon[2] == False:
        return (False, res)
    for i in range(horizon[0]):
        res.append(horizon[1])
    modify_maze_horizon(w, h, horizon[1])
    print_maze(w, h)
    return (True, res)

def make_vertic_moves(w, h):
    res = []
    vertic = moves_vertical(w, h)
    if vertic[2] == False:
        return (False, res)
    for i in range(vertic[0]):
        res.append(vertic[1])
    modify_maze_vertic(w, h, vertic[1])
    print_maze(w, h)
    return (True, res)

def move_if_free(cur, new):
    if maze[new[0]][new[1]] != '#':
        return new
    else:
        return cur

def make_move(st, m):
    cur_pos = st
    if m=='U':
        new_pos = move_if_free(cur_pos, (cur_pos[0]-1, cur_pos[1]))
    elif m=='D':
        new_pos = move_if_free(cur_pos, (cur_pos[0]+1, cur_pos[1]))
    elif m=='L':
        new_pos = move_if_free(cur_pos, (cur_pos[0], cur_pos[1]-1))
    else:
        new_pos = move_if_free(cur_pos, (cur_pos[0], cur_pos[1]+1))
    return new_pos  

def make_nmoves(s, moves):
    cur_pos = s
    for m in moves:
        cur_pos = make_move(cur_pos, m)
    return cur_pos

def end(starts):
    for s in starts:
        if maze[s[0]][s[1]] != 'G':
            return False
    return True

def fill_new_starts(old_starts, new_starts):
    for s in old_starts:
        if maze[s[0]][s[1]] == 'S':
            maze[s[0]][s[1]] = ' '
        else:
            maze[s[0]][s[1]] = 'G'
    starts = set(new_starts)
    for s in starts:
        if maze[s[0]][s[1]] == ' ':
            maze[s[0]][s[1]] = 'S'
        else:
            maze[s[0]][s[1]] = 'B'            

def move_all_starts(starts, moves):
    new_starts = []
    for s in starts:
        new_starts.append(make_nmoves(s, moves))
    return new_starts

def add_if_new(starts, queue, dict, desc):
    s = frozenset(starts)
    if not s in positions:
        queue.append(starts)
        positions.add(s)
        dict[s] = desc

def solve(h, w):
    res = []
    s = len(get_starts(w, h))
    while s>2:
        a = make_horizon_moves(w, h)
        if a[0]:
            res += a[1]
        b = make_vertic_moves(w, h)
        if b[0]:
            res += b[1]
        if not a[0] and not b[0]:
            tries = [x for x in range(1, 50)]
            found = False
            for i in range(len(tries)):
                if found:
                    break
                for j in range(tries[i]*tries[i]):
                    randoms = random_moves(tries[i])
                    s1 = get_starts(w, h)
                    s2 = move_all_starts(s1, randoms)
                    fill_new_starts(s1, s2)
                    a2 = make_horizon_moves(w, h)
                    b2 = make_vertic_moves(w, h)
                    if a2[0] or b2[0]:
                        res += randoms
                        res += a2[1]
                        res += b2[1]
                        found = True
                        break
                    else:
                        fill_new_starts(s2, s1)
        s = len(get_starts(w, h))

    queue = []
    moves_dict = {}
    starts = get_starts(w, h)
    starts = list(dict.fromkeys(starts))
    positions.add(frozenset(starts))
    queue.append(starts)
    moves_dict[frozenset(starts)] = ''.join(res)
    dirs = ['U', 'D', 'L', 'R']

    found = False
    while queue and not found:
        st = queue.pop(0)
        desc = moves_dict[frozenset(st)]
        for i in range(4):
            new_starts = move_all_starts(st, [dirs[i]])
            new_starts = list(dict.fromkeys(new_starts))
            add_if_new(new_starts, queue, moves_dict, desc+dirs[i])
            if end(new_starts):
                out.write(desc+dirs[i])
                found = True

line =  inp.readline()
width = len(line)-1
height = 1
for i in range(width):
    maze[0].append('#')
line = inp.readline()
while len(line)-1 == width:
    row = []
    for i in range(width):
        row.append(line[i])
    maze.append(row)
    height += 1
    line = inp.readline()

solve(height, width)

inp.close()
out.close()
