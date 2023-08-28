import random
import sys
import chess

draw_val = 0
win_val = 10000
lose_val = -10000
pawn = 1
knight = 3
bishop = 3
rook = 5
king = 2
queen = 9

square_vals = [
    [1, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 3, 3, 3, 3, 1, 1],
    [1, 1, 3, 6, 6, 3, 1, 1],
    [1, 1, 3, 6, 6, 3, 1, 1],
    [1, 1, 3, 3, 3, 3, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1]
]

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

class Chess:
    def __init__(self):
        self.board = chess.Board()
        
    def make_move(self, uci_move):
        try:
            move = chess.Move.from_uci(uci_move)
        except ValueError:
            raise WrongMove

        if move not in self.board.legal_moves:
            raise WrongMove
            
        self.board.push(move)
        out = self.board.outcome()
        if out is None:
            return None
        if out.winner is None:
            return -1
        return out.winner
    
    def unmake_move(self):
        self.board.pop()

    def moves(self):
        return [str(m) for m in self.board.legal_moves]
        
    def draw(self):
        eprint (self.board)    

    #chyba ok
    def material_balance(self, player):
        opp = 1-player
        player_bitmap = self.board.occupied_co[player]
        opp_bitmap = self.board.occupied_co[opp]
        p1 = chess.popcount(player_bitmap & self.board.pawns)
        p2 = chess.popcount(opp_bitmap & self.board.pawns)
        k1 = chess.popcount(player_bitmap & self.board.knights)
        k2 = chess.popcount(opp_bitmap & self.board.knights)
        b1 = chess.popcount(player_bitmap & self.board.bishops)
        b2 = chess.popcount(opp_bitmap & self.board.bishops)
        r1 = chess.popcount(player_bitmap & self.board.rooks)
        r2 = chess.popcount(opp_bitmap & self.board.rooks)
        q1 = chess.popcount(player_bitmap & self.board.queens)
        q2 = chess.popcount(opp_bitmap & self.board.queens)
        p_dif = p1-p2
        k_dif = k1-k2
        b_dif = b1-b2
        r_dif = r1-r2
        q_dif = q1-q2
        s = (p1+p2)*pawn + (k1+k2)*knight + (b1+b2)*bishop + (r1+r2)*rook + (q1+q2)*queen
        if s == 0:
            return 0
        return 100 * (p_dif*pawn + k_dif*knight + b_dif*bishop + r_dif*rook + q_dif*queen)/s

    #chyba ok
    def mobility(self, player):
        mob1 = len(self.moves())
        self.board.push(chess.Move.null())
        mob2 = len(self.moves())
        self.board.pop()
        if player == 1-self.board.turn:
            return 100 * (mob2 - mob1)/(mob1 + mob2)
        return 100 * (mob1 - mob2)/(mob1 + mob2)

    #chyba ok
    def pieces_thread(self, player):
        opp = 1-player
        pl_res = 0
        opp_res = 0
        for i in range(64):
            if self.board.piece_at(i):
                if self.board.piece_at(i).color == opp:
                    if self.board.is_attacked_by(player, i):
                        pl_res += 1
                if self.board.piece_at(i).color == player:
                    if self.board.is_attacked_by(opp, i):
                        opp_res +=1
        if pl_res + opp_res == 0:
            return 0
        return 100 * (pl_res - opp_res) / (pl_res + opp_res)

    #chyba ok
    def space_control(self, player):
        opp = 1-player
        pl_res = 0
        opp_res = 0
        for i in range (64):
            w = square_vals[i//8][i%8]
            pl_v = len(self.board.attackers(player, i))
            opp_v = len(self.board.attackers(opp, i))
            if pl_v < opp_v:
                opp_res += w
            elif pl_v > opp_v:
                pl_res += w
        if pl_res+opp_res == 0:
            return 0
        return 100 * (pl_res-opp_res)/(pl_res+opp_res)

    #chyba ok
    def king_safety(self, player):
        opp = 1-player
        my_king_pos = -1
        opp_king_pos = -1
        for i in range(64):
            if self.board.piece_at(i):
                if self.board.piece_type_at(i) == chess.KING:
                    if self.board.color_at(i) == player:
                        my_king_pos = i
                    elif self.board.color_at(i) == opp:
                        opp_king_pos = i
        my_king_rank = my_king_pos // 8
        my_king_file = my_king_pos % 8
        opp_king_rank = opp_king_pos // 8
        opp_king_file = opp_king_pos % 8
        my_king_sqr =  chess.square_name(my_king_pos)
        opp_king_sqr = chess.square_name(opp_king_pos)

        my_king_safe = 0
        my_king_attack = 0
        opp_king_safe = 0
        opp_king_attack = 0
        for i in range(64):
            if not self.board.piece_at(i):
                continue
            type = self.board.piece_type_at(i)
            color = self.board.color_at(i)
            rank = i // 8
            file = i % 8
            my_distane = max(abs(my_king_rank-rank), abs(my_king_file-file))
            opp_distane = max(abs(opp_king_rank-rank), abs(opp_king_file-file))
            w = 0
            if type == chess.PAWN:
                w = pawn
            elif type == chess.KNIGHT:
                w = knight
            elif type == chess.BISHOP:
                w = bishop
            elif type == chess.ROOK:
                w = rook
            elif type == chess.QUEEN:
                w = queen
            elif type == chess.KING:
                w = king

            if color == player:
                opp_king_attack += w*(8-opp_distane)
                my_king_safe += w*(8-my_distane)
            else:
                my_king_attack += w*(8-my_distane)
                opp_king_safe += w*(8-opp_distane)

        my_score = my_king_safe - my_king_attack
        opp_score = opp_king_safe - opp_king_attack

        ms1 = self.moves()
        self.board.push(chess.Move.null())
        ms2 = self.moves()
        self.board.pop()
        my_king_moves = 0
        opp_king_moves = 0
        if player == 1-self.board.turn:
            ar1 = [s for s in ms2 if my_king_sqr in s]
            ar2 = [s for s in ms1 if opp_king_sqr in s]
            my_king_moves = len(ar1)
            opp_king_moves = len(ar2)
        else:
            ar1 = [s for s in ms1 if my_king_sqr in s]
            ar2 = [s for s in ms2 if opp_king_sqr in s]
            my_king_moves = len(ar1)
            opp_king_moves = len(ar2)

        my_res = 6*(10-opp_king_moves) + my_score//30
        opp_res = 6*(10-my_king_moves) + opp_score//30

        if self.board.is_check():
            if self.board.turn == player:
                opp_res += 5
            else:
                my_res += 5

        if my_res + opp_res == 0:
            return 0
        return 100 * (my_res - opp_res) / (my_res + opp_res)

    #chyba ok
    def pawn_structure(self, player):
        my_pawns = []
        opp_pawns = []
        for i in range(64):
            if self.board.piece_at(i):
                if self.board.piece_type_at(i) == chess.PAWN:
                    if self.board.color_at(i) == player:
                        my_pawns.append((i//8, i%8))
                    else:
                        opp_pawns.append((i//8, i%8))
        my_res = 0
        opp_res = 0
        if player == chess.WHITE:
            for py, px in my_pawns:
                if (py-1, px-1) in my_pawns or (py-1, px+1) in my_pawns:
                    my_res += 8
                    my_res += py
                else:
                    my_res += py//2
            for py, px in opp_pawns:
                if (py+1, px-1) in opp_pawns or (py+1, px+1) in opp_pawns:
                    opp_res += 8                
                    opp_res += 8-py
                else:
                    opp_res += (8-py)//2
        else:
            for py, px in my_pawns:
                if (py+1, px-1) in my_pawns or (py+1, px+1) in my_pawns:
                    my_res += 8                
                    my_res += 8-py
                else:
                    my_res += (8-py)//2 
            for py, px in opp_pawns:
                if (py-1, px-1) in opp_pawns or (py-1, px+1) in opp_pawns:
                    opp_res += 8
                    opp_res += py
                else:
                    opp_res += py//2           
        if my_res + opp_res == 0:
            return 0
        return 100 * (my_res - opp_res) / (my_res + opp_res)

    def move_val(self, move, player):
        res = self.make_move(move)
        if res is not None:
            self.unmake_move()
            if res == player:
                return win_val
            elif res == 1-player:
                return lose_val
            else:
                return draw_val
        mat_bal = self.material_balance(player)
        mobil = self.mobility(player)
        piec_thread = self.pieces_thread(player)
        spc_ctrl = self.space_control(player)
        king_saf = self.king_safety(player)
        pawn_struct = self.pawn_structure(player)
        self.unmake_move()
        return 7*mat_bal + mobil + piec_thread + spc_ctrl + 5*king_saf + pawn_struct



class Player():
    def __init__(self):
        self.reset()

    def reset(self):
        self.game = Chess()
        self.my_player = 1
        self.say('RDY')

    def say(self, what):
        sys.stdout.write(what)
        sys.stdout.write('\n')
        sys.stdout.flush()

    def hear(self):
        line = sys.stdin.readline().split()
        return line[0], line[1:]

    def player_to_color(self, pl):
        return 1-pl

    def color_to_player(self, c):
        return 1-int(c)

    def max_arg(self, tab):
        m = tab[0]
        equals = []
        for i in range(len(tab)):
            v = tab[i]
            if v > m:
                m = v
                equals.clear()
                equals.append(i)
            elif v == m:
                equals.append(i)               
        return random.choice(equals)
    
    def min_arg(self, tab):
        m = tab[0]
        equals = []
        for i in range(len(tab)):
            v = tab[i]
            if v < m:
                m = v
                equals.clear()
                equals.append(i)
            elif v == m:
                equals.append(i)   
        return random.choice(equals)

    def minmax(self, d, alpha, beta):
        ms = self.game.moves()
        player = self.color_to_player(self.game.board.turn)
        if d == 1:
            moves_val = [self.game.move_val(m, self.player_to_color(self.my_player)) for m in ms]
            if player == self.my_player:
                arg = self.max_arg(moves_val)
                return (moves_val[arg], ms[arg])
            else:
                arg = self.min_arg(moves_val)
                return (moves_val[arg], ms[arg])
        if player == self.my_player:
            #max
            mscore = lose_val-1
            bmove = None
            for m in ms:
                res = self.game.make_move(m)
                sc, mov = 0, None
                if res is None:
                    sc, mov = self.minmax(d-1, alpha, beta)
                else:
                    winner = self.color_to_player(res)
                    if winner == self.my_player:
                        sc = win_val
                    elif winner == 1-self.my_player:
                        sc = lose_val
                    else:
                        sc = draw_val
                self.game.unmake_move()
                if sc > mscore:
                    mscore = sc
                    bmove = m
                if mscore > alpha:
                    alpha = mscore
                if beta <= alpha:
                    break
            return (mscore, bmove)
        else:
            #min
            mscore = win_val + 1
            bmove = None
            for m in ms:
                res = self.game.make_move(m)
                sc, mov = 0, None
                if res is None:
                    sc, mov = self.minmax(d-1, alpha, beta)
                else:
                    winner = self.color_to_player(res)
                    if winner == self.my_player:
                        sc = win_val
                    elif winner == 1-self.my_player:
                        sc = lose_val
                    else:
                        sc = draw_val                    
                self.game.unmake_move()
                if sc < mscore:
                    mscore = sc
                    bmove = m
                if mscore < beta:
                    beta = mscore
                if beta <= alpha:
                    break
            return (mscore, bmove)

    def choose_move(self):
        min = lose_val
        max = win_val
        depth = 2
        move = self.minmax(depth, min, max)
        self.game.make_move(move[1])
        return move[1]

    def loop(self):
        while True:
            cmd, args = self.hear()
            if cmd == 'HEDID':
                unused_move_timeout, unused_game_timeout = args[:2]
                move = args[2]                
                self.game.make_move(move)
            elif cmd == 'ONEMORE':
                self.reset()
                continue
            elif cmd == 'BYE':
                break
            else:
                assert cmd == 'UGO'
                self.my_player = 0

            move = self.choose_move()
            self.say('IDO ' + move)


if __name__ == '__main__':
    player = Player()
    player.loop()
