import random
import sys
import chess

infinity = 10000
depth = 4

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

agents = [
    (0.46279138991357094, 10, 6, 13, 6),
    (0.9391115497477633, 10, 14, 5, 11),
    (0.26108382536775976, 9, 15, 6, 5),
    (0.9997342205366323, 2, 8, 1, 6),
    (0.2645588386639526, 3, 2, 6, 12),
    (0.28240866314582214, 7, 12, 7, 7),
    (0.7917539422665059, 3, 8, 14, 9),
    (0.2918122728772111, 15, 6, 13, 14),
    (0.14082098220017503, 5, 15, 14, 9),
    (0.86736934808208, 10, 13, 6, 12),
    (0.878886393171316, 15, 6, 7, 8),
    (0.6839236782558505, 4, 9, 4, 9),
    (0.5719052859952644, 7, 7, 10, 8),
    (0.6951576368741239, 7, 13, 3, 10),
    (0.42269161406362554, 14, 8, 6, 13),
    (0.2896263357763522, 9, 14, 8, 9),
    (0.7701043917660865, 14, 10, 2, 5),
    (0.060700220383358205, 4, 2, 13, 5),
    (0.5579929014174155, 14, 13, 8, 13),
    (0.36242292978739354, 4, 13, 2, 2),
    (0.34820406227110456, 11, 4, 9, 2),
    (0.7473922027367019, 14, 3, 10, 9),
    (0.22181052167286452, 1, 1, 6, 14),
    (0.0547297279145067, 2, 3, 8, 10),
    (0.8031183172607902, 15, 13, 1, 10),
    (0.9992379346202466, 7, 15, 2, 11),
    (0.9624494671981504, 1, 1, 9, 1),
    (0.3474092438075549, 9, 7, 13, 10),
    (0.1476579635081251, 12, 8, 13, 8),
    (0.6375061600253562, 9, 13, 6, 10),
    (0.8164901317043929, 9, 8, 4, 4),
    (0.04988483580237357, 15, 1, 4, 2),
    (0.9699631012233666, 11, 12, 9, 11),
    (0.09032921080730227, 6, 9, 3, 7),
    (0.743416307518061, 9, 11, 2, 5),
    (0.7650284527597466, 3, 10, 13, 10),
    (0.4347584174024689, 7, 4, 4, 11),
    (0.7406439714000678, 15, 10, 7, 7),
    (0.7164953476794793, 11, 4, 1, 9),
    (0.024360763304683064, 9, 8, 1, 5),
    (1.0994639078140551, 13, 14, 5, 4),
    (3.5550468806350377, 13, 6, 8, 10),
    (2.8222120970522515, 15, 15, 7, 4),
    (4.38226288946001, 1, 12, 8, 13),
    (1.0562832704688057, 6, 7, 12, 7),
    (1.7134570602082806, 14, 1, 7, 3),
    (2.722761159414105, 7, 2, 12, 11),
    (4.89897910518882, 9, 14, 5, 6),
    (2.5312527346013916, 8, 9, 3, 5),
    (1.6252192230587368, 4, 11, 3, 5),
    (1.1191150570204762, 6, 2, 13, 11),
    (3.0578593321320695, 9, 14, 12, 14),
    (1.4952833728731316, 1, 13, 3, 10),
    (2.621605439051971, 14, 5, 11, 3),
    (3.0182841948804597, 13, 5, 5, 2),
    (4.518514175052546, 7, 5, 1, 10),
    (1.6979615701102846, 12, 13, 6, 2),
    (3.546205774221759, 10, 3, 7, 7),
    (4.3122718815782495, 14, 1, 9, 4),
    (3.9755710389456898, 5, 2, 2, 9),
    (4.720148518646138, 11, 1, 7, 5),
    (3.837669299022659, 10, 8, 11, 11),
    (3.961850847090833, 2, 3, 1, 2),
    (2.124574829965293, 4, 13, 7, 5),
    (1.6862915343745595, 15, 6, 4, 15),
    (2.948362798877548, 1, 15, 13, 11),
    (1.3550594545085826, 10, 6, 11, 6),
    (2.5723001043966875, 14, 7, 4, 5),
    (1.4787019123568208, 5, 14, 3, 6),
    (3.7457904010642116, 4, 11, 6, 5),
    (6.995380630177227, 12, 2, 15, 2),
    (9.718099190922562, 8, 2, 2, 12),
    (9.963810240273098, 10, 5, 9, 13),
    (8.149317004542866, 11, 7, 8, 9),
    (8.721035256953243, 9, 8, 12, 15),
    (5.366828713447297, 10, 1, 5, 14),
    (9.860408746340582, 9, 4, 5, 9),
    (5.3471540331080565, 11, 8, 14, 11),
    (8.182712440039367, 11, 11, 10, 5),
    (7.677820866106253, 14, 14, 9, 11),
    (0.40551518724805447, 7, 4, 9, 15),
    (3.6373594703609324, 2, 8, 7, 2),
    (5.963982091754442, 4, 1, 4, 15),
    (3.2105556629347722, 5, 2, 2, 9),
    (0.8469087330637937, 7, 1, 7, 2),
    (1.8542458538542894, 13, 1, 1, 12),
    (6.2119360571235225, 9, 12, 15, 14),
    (0.9819657727564135, 2, 2, 9, 10),
    (3.4403001802604702, 6, 11, 10, 4),
    (6.531468508103945, 14, 12, 4, 15),
    (5.655123123305728, 6, 13, 10, 10),
    (3.3229906809621825, 2, 4, 11, 3),
    (0.21924722026266275, 14, 5, 2, 14),
    (5.351288250047358, 13, 2, 9, 8),
    (7.120234980362179, 15, 10, 3, 10),
    (9.009039870840654, 7, 11, 6, 15),
    (4.389023987778459, 4, 12, 9, 1),
    (7.420040703959165, 5, 6, 7, 7),
    (0.2077603704947928, 9, 8, 5, 2),
    (4.675994907306632, 1, 9, 5, 4)
]

class Chess:
    def __init__(self):
        self.board = chess.Board()
        self.k = 90
        self.nmoves = 0
        
    def finished(self):
        if self.nmoves > self.k:
            return True
        out = self.board.outcome()
        if out is not None:
            return True
        return False

    def winner(self):
        out = self.board.outcome()
        if out is not None:
            return out.winner
        white_bitmap = self.board.occupied_co[chess.WHITE]
        black_bitmap = self.board.occupied_co[chess.BLACK]
        p1 = chess.popcount(white_bitmap & self.board.pawns)
        p2 = chess.popcount(black_bitmap & self.board.pawns)
        k1 = chess.popcount(white_bitmap & self.board.knights)
        k2 = chess.popcount(black_bitmap & self.board.knights)
        b1 = chess.popcount(white_bitmap & self.board.bishops)
        b2 = chess.popcount(black_bitmap & self.board.bishops)
        r1 = chess.popcount(white_bitmap & self.board.rooks)
        r2 = chess.popcount(black_bitmap & self.board.rooks)
        q1 = chess.popcount(white_bitmap & self.board.queens)
        q2 = chess.popcount(black_bitmap & self.board.queens)
        p_dif = p1-p2
        k_dif = k1-k2
        b_dif = b1-b2
        r_dif = r1-r2
        q_dif = q1-q2
        s = p_dif + k_dif*3 + b_dif*3 + r_dif*5 + q_dif*9
        if s < 0:
            return chess.BLACK
        elif s > 0:
            return chess.WHITE
        return None

    def do_move(self, uci_move):
        try:
            move = chess.Move.from_uci(uci_move)
        except ValueError:
            raise WrongMove
        
        if move not in self.board.legal_moves:
            raise WrongMove    
        self.board.push(move)
        self.nmoves += 1

    def undo_move(self):
        self.board.pop()

    def moves(self):
        return [str(m) for m in self.board.legal_moves]
        
    def is_dynamic(self, m):
        if self.board.is_capture(chess.Move.from_uci(m)):
            return True
        if self.board.is_check():
            return True
        answ = False
        self.do_move(m)
        if self.board.is_check():
            answ = True
        self.undo_move()
        return answ

    def dynamic_moves(self):
        ms = self.moves()
        res = [m for m in ms if self.is_dynamic(m)]
        return res

    def draw(self):
        print (self.board) 
        print("")   

class Player():
    def __init__(self, nr, m_par, kn, bi, ro, qu):
        self.game = Chess()
        self.my_player = nr
        self.pawn = 1
        self.knight = kn
        self.bishop = bi
        self.rook = ro
        self.queen = qu
        self.m_param = m_par

    def material_balance(self):
        white_bitmap = self.game.board.occupied_co[chess.WHITE]
        black_bitmap = self.game.board.occupied_co[chess.BLACK]
        p1 = chess.popcount(white_bitmap & self.game.board.pawns)
        p2 = chess.popcount(black_bitmap & self.game.board.pawns)
        k1 = chess.popcount(white_bitmap & self.game.board.knights)
        k2 = chess.popcount(black_bitmap & self.game.board.knights)
        b1 = chess.popcount(white_bitmap & self.game.board.bishops)
        b2 = chess.popcount(black_bitmap & self.game.board.bishops)
        r1 = chess.popcount(white_bitmap & self.game.board.rooks)
        r2 = chess.popcount(black_bitmap & self.game.board.rooks)
        q1 = chess.popcount(white_bitmap & self.game.board.queens)
        q2 = chess.popcount(black_bitmap & self.game.board.queens)
        p_dif = p1-p2
        k_dif = k1-k2
        b_dif = b1-b2
        r_dif = r1-r2
        q_dif = q1-q2
        return p_dif*self.pawn + k_dif*self.knight + b_dif*self.bishop + r_dif*self.rook + q_dif*self.queen

    def mobility(self):
        mob1 = len(self.game.moves())
        self.game.board.push(chess.Move.null())
        mob2 = len(self.game.moves())
        self.game.board.pop()
        if self.game.board.turn == chess.BLACK:
            return self.m_param*(mob2 - mob1)
        return self.m_param*(mob1 - mob2)

    def board_val(self):
        out = self.game.board.outcome()
        if out is not None and out.winner is not None:
            if out.winner == chess.WHITE:
                return infinity
            if out.winner == chess.BLACK:
                return -1*infinity
        mat_bal = self.material_balance()
        mobil = self.mobility()
        return mat_bal + mobil

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

    def minmax_dynamic(self, d, alpha, beta):
        if d == 0:
            v = self.board_val()
            if self.my_player == chess.BLACK:
                v *= -1 
            return v
        ms = self.game.dynamic_moves()
        if not ms:
            v = self.board_val()
            if self.my_player == chess.BLACK:
                v *= -1 
            return v
        player = self.game.board.turn
        if player == self.my_player:
            #max
            mscore = -1*infinity-1
            for m in ms:
                self.game.do_move(m)
                sc = self.minmax_dynamic(d-1, alpha, beta)
                self.game.undo_move()
                if sc > mscore:
                    mscore = sc
                if mscore > alpha:
                    alpha = mscore
                if beta <= alpha:
                    break
            return mscore
        else:
            #min
            mscore = infinity + 1
            for m in ms:
                self.game.do_move(m)
                sc = self.minmax_dynamic(d-1, alpha, beta)                
                self.game.undo_move()
                if sc < mscore:
                    mscore = sc
                if mscore < beta:
                    beta = mscore
                if beta <= alpha:
                    break
            return mscore

    def minmax(self, d, alpha, beta):
        ms = self.game.moves()
        ms_val = []
        for m in ms:
            self.game.do_move(m)
            sc = self.minmax_dynamic(d-1, alpha, beta)
            self.game.undo_move()
            ms_val.append(sc)
        arg = self.max_arg(ms_val)
        return ms[arg]

    def choose_move(self):
        min = -1*infinity
        max = infinity
        global depth
        move = self.minmax(depth, min, max)
        return move

    def make_move(self):
        m = self.choose_move()
        self.game.do_move(m)
        return m

    def update_move(self, m):
        self.game.do_move(m)

def play(ngames, verbose, v1, v2):
    for i in range(ngames):
        a0 = agents[v1]
        a1 = agents[v2]
        p0 = Player(chess.BLACK, a0[0], a0[1], a0[2], a0[3], a0[4])
        p1 = Player(chess.WHITE, a1[0], a1[1], a1[2], a1[3], a1[4])
        numbers = [v1, v2]
        players = [p0, p1]
        game = Chess()
        while not game.finished():
            if verbose:
                game.draw()
            ind = int(game.board.turn)
            m = players[ind].make_move()
            game.do_move(m)
            players[1-ind].update_move(m)
        res = game.winner()
        print(str(v1) + " vs " + str(v2) + ": ", end="")
        eprint(str(v1) + " vs " + str(v2))
        if res is None:
            print("DRAW")
        else:
            print(str(numbers[int(res)]) + " WON")

ngames = 1
verbose = False
for i in range(50, 79):
    for j in range(i+1, 80):
        if bool(random.getrandbits(1)):
            play(ngames, verbose, i, j)
        else:
            play(ngames, verbose, j, i)

"""
agents = []
for i in range(40):
    m_p = random.uniform(0.0, 1.0)
    kn = random.randint(1, 15)
    bi = random.randint(1, 15)
    ro = random.randint(1, 15)
    qu = random.randint(1, 15)
    agents.append((m_p, kn, bi, ro, qu))
for i in range(30):
    m_p = random.uniform(1.0, 5.0)
    kn = random.randint(1, 15)
    bi = random.randint(1, 15)
    ro = random.randint(1, 15)
    qu = random.randint(1, 15)
    agents.append((m_p, kn, bi, ro, qu))
for i in range(10):
    m_p = random.uniform(5.0, 10.0)
    kn = random.randint(1, 15)
    bi = random.randint(1, 15)
    ro = random.randint(1, 15)
    qu = random.randint(1, 15)
    agents.append((m_p, kn, bi, ro, qu))

for i in range(80):
    print(agents[i], end="")
    print(",")
"""
