import heapq
import math

inp = open('zad_input.txt', 'r')
out = open('zad_output.txt', 'w')
maze = [[]]
goals = []
positions = set()

distance = []

def start_point(m):
    return m == 'S' or m == 'B'

def goal_point(m):
    return m == 'G' or m == 'B'

def get_starts(w, h):
    starts = []
    for y in range(h):
        for x in range(w):
            if start_point(maze[y][x]):
                starts.append((y, x))
    return starts

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

def end(starts):
    for s in starts:
        if not goal_point(maze[s[0]][s[1]]):
            return False
    return True        

def move_all_starts(starts, m):
    new_starts = []
    for s in starts:
        new_starts.append(make_move(s, m))
    return new_starts

def count_h(starts):
    max = 0
    for s in starts:
        d = distance[s[0]][s[1]]
        if d > max:
            max = d
    return max

def pop_min(q):
    mini_ind = 0
    mini_val = q[0][0]
    for e in range(len(q)):
        if q[e][0] < mini_val:
            mini_val = q[e][0]
            mini_ind = e
    res = q.pop(mini_ind)
    return res

def count_real_dist(w, h):
    found = [[0 for i in range(w)] for j in range(h)]
    for g in goals:  
        distance[g[0]][g[1]] = 0
    queue = []
    for i in range(h):
        for j in range(w):
            if maze[i][j] != '#':
                queue.append((distance[i][j], (i, j)))
    while queue:
        p = pop_min(queue)
        y = p[1][0]
        x = p[1][1]
        found[y][x] = 1
        if maze[y+1][x] != '#' and found[y+1][x] == 0:
            alt = distance[y][x] + 1
            if alt < distance[y+1][x]:
                queue.remove((distance[y+1][x], (y+1, x)))
                queue.append((alt, (y+1, x)))
                distance[y+1][x] = alt
        if maze[y-1][x] != '#' and found[y-1][x] == 0:
            alt = distance[y][x] + 1
            if alt < distance[y-1][x]:
                queue.remove((distance[y-1][x], (y-1, x)))
                queue.append((alt, (y-1, x)))
                distance[y-1][x] = alt
        if maze[y][x+1] != '#' and found[y][x+1] == 0:
            alt = distance[y][x] + 1
            if alt < distance[y][x+1]:
                queue.remove((distance[y][x+1], (y, x+1)))
                queue.append((alt, (y, x+1)))
                distance[y][x+1] = alt
        if maze[y][x-1] != '#' and found[y][x-1] == 0:
            alt = distance[y][x] + 1
            if alt < distance[y][x-1]:
                queue.remove((distance[y][x-1], (y, x-1)))
                queue.append((alt, (y, x-1)))
                distance[y][x-1] = alt

def count_distance(w, h):
    for i in range(h):
        row = []
        for j in range(w):
            row.append(100000)
        distance.append(row)
    count_real_dist(w, h)

def add_if_new(starts, queue, desc):
    s = frozenset(starts)
    if not s in positions:
        heapq.heappush(queue, (1.4*count_h(starts) + len(desc), starts, desc))
        positions.add(s)

def solve(h, w):
    count_distance(w, h)
    queue = []
    heapq.heapify(queue)
    starts = get_starts(w, h)
    starts = list(dict.fromkeys(starts))
    positions.add(frozenset(starts))
    heapq.heappush(queue, (count_h(starts), starts, ""))
    dirs = ['U', 'D', 'L', 'R']

    found = False
    while queue and not found:
        st = heapq.heappop(queue)
        desc = st[2]
        for i in range(4):
            new_starts = move_all_starts(st[1], dirs[i])
            new_starts = list(dict.fromkeys(new_starts))
            add_if_new(new_starts, queue, desc+dirs[i])
            if end(new_starts):
                out.write(desc+dirs[i])
                found = True
                break

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
        if goal_point(line[i]):
            goals.append((height, i))
    maze.append(row)
    height += 1
    line = inp.readline()

solve(height, width)

inp.close()
out.close()
