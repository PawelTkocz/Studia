def neighbours(pos1, pos2):
    col = ord(pos1[0])
    row = int(pos1[1])
    for r in range(-1, 2, 1):
        for c in range(-1, 2, 1):
            dest_row = row + r
            dest_col = col + c
            dest_pos = chr(dest_col) + str(dest_row)
            if dest_pos == pos2:
                return True
    return False

def capture_rook(white_rook, white_king, black_king):
    if not neighbours(white_rook, black_king):
        return False
    return not neighbours(white_rook, white_king)
            
def free_square(white_rook, white_king, black_king, row, column):
    min_col = ord('a')
    max_col = ord('h')
    min_row = 1
    max_row = 8
    if row < min_row or row > max_row or column > max_col or column < min_col:
        return False
    pos = chr(column) + str(row)
    if pos == white_rook or pos == white_king or pos == black_king:
        return False
    return True

def check(white_rook, white_king, black_king):
    bk_col = ord(black_king[0])
    bk_row = int(black_king[1])
    wk_col = ord(white_king[0])
    wk_row = int(white_king[1])
    t_col = ord(white_rook[0])
    t_row = int(white_rook[1])

    if neighbours(white_king, black_king):
        return True
    
    if t_col == bk_col:
        #wieża jest w tej samej kolumnie
        if wk_col != bk_col:
            return True
        else:
            if (t_row < wk_row and wk_row < bk_row) or (bk_row < wk_row and wk_row < t_row):
                return False
            return True
    if t_row == bk_row:
        #wieża jest w tym samym wierszu
        if wk_row != bk_row:
            return True
        else:
            if (t_col < wk_col and wk_col < bk_col) or (bk_col < wk_col and wk_col < t_col):
                return False
            return True
    return False

def black_king_moves(white_rook, white_king, black_king):
    res = []
    column = ord(black_king[0])
    row = int(black_king[1])
    for r in range(-1, 2, 1):
        for c in range(-1, 2, 1):
            dest_row = row + r
            dest_column = column + c
            dest_pos = chr(dest_column) + str(dest_row)
            sq_free = free_square(white_rook, white_king, black_king, dest_row, dest_column)
            if sq_free and (not check(white_rook, white_king, dest_pos)):
                res.append(dest_pos)
    return res

def white_king_moves(white_rook, white_king, black_king):
    res = []
    column = ord(white_king[0])
    row = int(white_king[1])
    for r in range(-1, 2, 1):
        for c in range(-1, 2, 1):
            dest_row = row + r
            dest_column = column + c
            dest_pos = chr(dest_column) + str(dest_row)
            sq_free = free_square(white_rook, white_king, black_king, dest_row, dest_column)
            if sq_free and (not neighbours(black_king, dest_pos)):
                res.append(dest_pos)
    return res

def rook_moves(white_rook, white_king, black_king):
    res = []
    column = ord(white_rook[0])
    row = int(white_rook[1])
    for i in range(row+1, 9, 1):
        if free_square(white_rook, white_king, black_king, i, column):
            pos = chr(column) + str(i)
            res.append(pos)
        else:
            break
    for i in range(row-1, 0, -1):
        if free_square(white_rook, white_king, black_king, i, column):
            pos = chr(column) + str(i)
            res.append(pos)
        else:
            break
    for i in range(column+1, ord('h') + 1, 1):
        if free_square(white_rook, white_king, black_king, row, i):
            pos = chr(i) + str(row)
            res.append(pos)
        else:
            break
    for i in range(column-1, ord('a')-1, -1):
        if free_square(white_rook, white_king, black_king, row, i):
            pos = chr(i) + str(row)
            res.append(pos)
        else:
            break
    return res

def mate(white_rook, white_king, black_king):
    return check(white_rook, white_king, black_king) and not black_king_moves(white_rook, white_king, black_king) and not capture_rook(white_rook, white_king, black_king)
        
def add_move_if_new(move, queue, all_moves, moves_dict, nmoves):
    if move not in all_moves:
        all_moves.add(move)
        queue.append(move)
        moves_dict[move] = nmoves + 1

def get_next_player(moving_player):
    if moving_player == "white":
        return "black"
    return "white"

def solve(moving_player, white_rook, white_king, black_king):
    if mate(white_rook, white_king, black_king):
        return 0

    all_moves = set() 
    moves_dict = {}   
    queue = []
    start_pos = (moving_player, white_rook, white_king, black_king)
    all_moves.add(start_pos)
    queue.append(start_pos)
    moves_dict[start_pos] = 0

    while queue:
        board = queue.pop(0)
        moving_player = board[0]
        white_rook = board[1]
        white_king = board[2]
        black_king = board[3]
        nmoves = moves_dict[board]
        next_player = get_next_player(moving_player)

        if moving_player == "black":
            moves = black_king_moves(white_rook, white_king, black_king)
            for m in moves:
                add_move_if_new((next_player, white_rook, white_king, m), queue, all_moves, moves_dict, nmoves)
        else:
            moves_k = white_king_moves(white_rook, white_king, black_king)
            for m in moves_k:
                if mate(white_rook, m, black_king):
                    return nmoves + 1
                add_move_if_new((next_player, white_rook, m, black_king), queue, all_moves, moves_dict, nmoves)
            moves_t = rook_moves(white_rook, white_king, black_king)
            for m in moves_t:
                if mate(m, white_king, black_king):
                    return nmoves + 1
                add_move_if_new((next_player, m, white_king, black_king), queue, all_moves, moves_dict, nmoves)
    return -1


inp = open('zad1_input.txt', 'r')
out = open('zad1_output.txt', 'w')
line =  inp.readline()
while line:
    moving_player, white_king, white_rook, black_king = line.split()
    res = solve(moving_player, white_rook, white_king, black_king)
    if res == -1:
        out.write("INF\n")
    else:
        out.write(str(res) + "\n")
    line = inp.readline()
inp.close()
out.close()