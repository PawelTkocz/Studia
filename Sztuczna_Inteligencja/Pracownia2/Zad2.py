inp = open('zad_input.txt', 'r')
out = open('zad_output.txt', 'w')
maze = [[]]
deadlocks = [[]]
skrzynie = []
goals = []
magazynier = (0,0)
positions = set()

def is_deadlock(y, x):
    return deadlocks[y][x] == 1

def deadlocks_for_g(visited, x, y):
    deadlocks[y][x] = 0
    visited[y][x] = 1
    if visited[y-1][x] == 0 and maze[y-1][x] != 'W' and maze[y-2][x] !='W':
        deadlocks_for_g(visited, x, y-1)
    if visited[y+1][x] == 0 and maze[y+1][x] != 'W' and maze[y+2][x] != 'W':
        deadlocks_for_g(visited, x, y+1)
    if visited[y][x-1] == 0 and maze[y][x-1] != 'W' and maze[y][x-1] != 'W':
        deadlocks_for_g(visited, x-1, y)
    if visited[y][x+1] == 0 and maze[y][x+1] != 'W' and maze[y][x+1] != 'W':
        deadlocks_for_g(visited, x+1, y)

def find_deadlocks(w, h):
    for g in goals:
        visited = [[0 for i in range (w)] for j in range(h)]
        deadlocks_for_g(visited, g[1], g[0])


def czy_skrzynia(l):
    return l=='B' or l=='*'

def czy_magazynier(l):
    return l=='K' or l=='+'

def czy_wolne(l):
    return l=='.' or l=='G'

def czy_goal(l):
    return l=='G' or l=='*' or l=='+'

def end(new_sit):
    for s in new_sit[1]:
        if not czy_goal(maze[s[0]][s[1]]):
            return False
    return True          

def add_if_new(new_sit, queue, dict, desc):
    s = frozenset(new_sit[1])
    if not (s, new_sit[2]) in positions:
        c = new_sit[1].copy()
        queue.append((c, new_sit[2]))
        positions.add((s, new_sit[2]))
        dict[(s, new_sit[2])] = desc

def move(s, mag, d):
    sk = s.copy()
    if d=='U':
        n_pos = (mag[0]-1, mag[1])
        if maze[n_pos[0]][n_pos[1]] == 'W':
            return (False, sk, mag)
        elif not n_pos in sk:
            return (True, sk, n_pos)
        else:
            za_sk = (mag[0]-2, mag[1])
            if not za_sk in sk and maze[za_sk[0]][za_sk[1]] != 'W' and not is_deadlock(za_sk[0], za_sk[1]):
                sk.remove(n_pos)
                sk.append(za_sk)
                return (True, sk, n_pos)
            else:
                return (False, sk, mag)
    elif d=='D':
        n_pos = (mag[0]+1, mag[1])
        if maze[n_pos[0]][n_pos[1]] == 'W':
            return (False, sk, mag)
        elif not n_pos in sk:
            return (True, sk, n_pos)
        else:
            za_sk = (mag[0]+2, mag[1])
            if not za_sk in sk and maze[za_sk[0]][za_sk[1]] != 'W' and not is_deadlock(za_sk[0], za_sk[1]):
                sk.remove(n_pos)
                sk.append(za_sk)
                return (True, sk, n_pos)
            else:
                return (False, sk, mag)        
    elif d=='L':
        n_pos = (mag[0], mag[1]-1)
        if maze[n_pos[0]][n_pos[1]] == 'W':
            return (False, sk, mag)
        elif not n_pos in sk:
            return (True, sk, n_pos)
        else:
            za_sk = (mag[0], mag[1]-2)
            if not za_sk in sk and maze[za_sk[0]][za_sk[1]] != 'W' and not is_deadlock(za_sk[0], za_sk[1]):
                sk.remove(n_pos)
                sk.append(za_sk)
                return (True, sk, n_pos)
            else:
                return (False, sk, mag)
    elif d=='R':
        n_pos = (mag[0], mag[1]+1)
        if maze[n_pos[0]][n_pos[1]] == 'W':
            return (False, sk, mag)
        elif not n_pos in sk:
            return (True, sk, n_pos)
        else:
            za_sk = (mag[0], mag[1]+2)
            if not za_sk in sk and maze[za_sk[0]][za_sk[1]] != 'W' and not is_deadlock(za_sk[0], za_sk[1]):
                sk.remove(n_pos)
                sk.append(za_sk)
                return (True, sk, n_pos)
            else:
                return (False, sk, mag)

def solve(h, w):
    find_deadlocks(w, h)
    res = []
    queue = []
    moves_dict = {}
    positions.add((frozenset(skrzynie), magazynier))
    queue.append((skrzynie, magazynier))
    moves_dict[(frozenset(skrzynie), magazynier)] = ''
    dirs = ['U', 'D', 'L', 'R']

    found = False
    while queue and not found:
        st = queue.pop(0)
        desc = moves_dict[(frozenset(st[0]), st[1])]
        for i in range(4):
            new_sit = move(st[0], st[1], dirs[i])
            if new_sit[0]:
                add_if_new(new_sit, queue, moves_dict, desc+dirs[i])
                if end(new_sit):
                    out.write(desc+dirs[i])
                    found = True


line =  inp.readline()
width = len(line)-1
height = 1
for i in range(width):
    maze[0].append('W')
    deadlocks[0].append(1)
line = inp.readline()
while len(line)-1 == width:
    row = []
    row2 = []
    for i in range(width):
        row.append(line[i])
        row2.append(1)
        if czy_skrzynia(line[i]):
            skrzynie.append((height, i))
        if czy_magazynier(line[i]):
            magazynier = (height, i)
        if czy_goal(line[i]):
            goals.append((height, i))
    maze.append(row)
    deadlocks.append(row2)
    height += 1
    line = inp.readline()

solve(height, width)

inp.close()
out.close()
