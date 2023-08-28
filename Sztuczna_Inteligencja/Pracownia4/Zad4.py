import random
import sys
from copy import deepcopy

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

class Jungle:
    #każda figura ma przypisaną szacunkową wartość
    PIECE_VALUES = {
        0: 4,
        1: 1,
        2: 2,
        3: 3,
        4: 5,
        5: 7,
        6: 8,
        7: 10
    }
    #maksymalna liczba ruchów obu graczy bez zbicia jakiejkolwiek figury
    #gra kończy się jeśli ta wartość zostanie przekroczona
    MAXIMAL_PASSIVE = 30
    #nie wiadomo co to jest
    DENS_DIST = 0.1
    #rozmiary planszy
    MX = 7
    MY = 9
    #pola i dozowolone ruchy
    traps = {(2, 8), (4, 8), (3, 7), (2, 0), (4, 0), (3, 1)}
    traps_arr = [(2, 8), (4, 8), (3, 7), (2, 0), (4, 0), (3, 1)]
    near_traps = {(2, 8): [(1, 8), (2, 7)],
                  (4, 8): [(5, 8), (4, 7)],
                  (3, 7): [(2, 7), (4, 7), (3, 6)],
                  (2, 0): [(1, 0), (2, 1)],
                  (4, 0): [(4, 1), (5, 0)],
                  (3, 1): [(2, 1), (4, 1), (3, 2)]}
    ponds = {(x, y) for x in [1, 2, 4, 5] for y in [3, 4, 5]}
    dens = [(3, 8), (3, 0)]
    dirs = [(0, 1), (1, 0), (-1, 0), (0, -1)]
    nmoves = 0

    #każda figura jest zmienną o wartości z zakresu 0-7
    rat, cat, dog, wolf, jaguar, tiger, lion, elephant = range(8)

    def __init__(self):
        #plansza ma postać dwuwymiarowej tablicy, gdzie jeśli board[y][x] jest niezajmowane przez żadną figurę,
        #to board[y][x] = None, wpp. board[y][x] = (p, f), gdzie p to gracz 0 lub 1, a f to figura [0, 7]
        self.board = self.initial_board()
        #pieces to słownik przechowujący pozycje figur każdego z graczy. Każdy z graczy dla każdej figury ma wpis 
        #postaci f: (x_f, y_f)
        self.pieces = {0: {}, 1: {}}

        for y in range(Jungle.MY):
            for x in range(Jungle.MX):
                C = self.board[y][x]
                if C:
                    pl, pc = C
                    self.pieces[pl][pc] = (x, y)
        self.curplayer = 0
        self.peace_counter = 0
        self.winner = None

    def initial_board(self):
        pieces = """
        L.....T
        .D...C.
        R.J.W.E
        .......
        .......
        .......
        e.w.j.r
        .c...d.
        t.....l
        """

        B = [x.strip() for x in pieces.split() if len(x) > 0]
        T = dict(zip('rcdwjtle', range(8)))

        res = []
        for y in range(9):
            raw = 7 * [None]
            for x in range(7):
                c = B[y][x]
                if c != '.':
                    if 'A' <= c <= 'Z':
                        player = 1
                    else:
                        player = 0
                    raw[x] = (player, T[c.lower()])
            res.append(raw)
        return res

    def random_move(self, player):
        #wybiera losowy ruch ze wszystich możliwych ruchów
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return None

    def can_beat(self, p1, p2, pos1, pos2):
        if pos1 in Jungle.ponds and pos2 in Jungle.ponds:
            return True  # rat vs rat
        if pos1 in Jungle.ponds:
            return False  # rat in pond cannot beat any piece on land
        if p1 == Jungle.rat and p2 == Jungle.elephant:
            return True
        if p1 == Jungle.elephant and p2 == Jungle.rat:
            return False
        if p1 >= p2:
            return True
        if pos2 in Jungle.traps:
            return True
        return False

    def pieces_comparison(self):
        #zwraca gracza który posiada najsilniejszą figurę
        #lub None jeśli takiego gracza nie ma
        for i in range(7,-1,-1):
            ps = []
            for p in [0,1]:
                if i in self.pieces[p]:
                    ps.append(p)
            if len(ps) == 1:
                return ps[0]
        return None
                
    def rat_is_blocking(self, player, pos, dx, dy):     
        # w implementacji z random nie można skakać nad żadnym szczurem, nawet swoim   
        x, y = pos
        nx = x + dx
        if Jungle.rat not in self.pieces[1-player]:
            return False
        rx, ry = self.pieces[1-player][Jungle.rat]
        if (rx, ry) not in self.ponds:
            return False
        if dy != 0:
            if x == rx:
                return True
        if dx != 0:
            if y == ry and abs(x-rx) <= 2 and abs(nx-rx) <= 2:
                return True
        return False

    def draw(self):
        #rysuje planszę
        TT = {0: 'rcdwjtle', 1: 'RCDWJTLE'}
        for y in range(Jungle.MY):

            L = []
            for x in range(Jungle.MX):
                b = self.board[y][x]
                if b:
                    pl, pc = b
                    L.append(TT[pl][pc])
                else:
                    L.append('.')
            print(''.join(L))
        print('')

    def moves(self, player):
        res = []
        for p, pos in self.pieces[player].items():
            #dla każdej figury w słowniku pieces[player]
            x, y = pos
            for (dx, dy) in Jungle.dirs:
                pos2 = (nx, ny) = (x+dx, y+dy)
                if 0 <= nx < Jungle.MX and 0 <= ny < Jungle.MY:
                    #sprawdzamy czy nowy ruch nie opuszcza planszy
                    if Jungle.dens[player] == pos2:
                        #ruch do swojej jamy jest niedozwolony
                        continue
                    if pos2 in self.ponds:
                        if p not in (Jungle.rat, Jungle.tiger, Jungle.lion):
                            continue
                        #if self.board[ny][nx] is not None: #czyli jeśli jest tam jakiś szczur
                        #    continue  # WHY?? - uniemożliwia bicie szczura z lądu w wodę oraz
                        #                        skakanie nad swoim szczurem ???
                        if p == Jungle.tiger or p == Jungle.lion:
                            if dx != 0:
                                dx *= 3
                            if dy != 0:
                                dy *= 4
                            if self.rat_is_blocking(player, pos, dx, dy):
                                continue
                            pos2 = (nx, ny) = (x+dx, y+dy)
                    if self.board[ny][nx] is not None:
                        pl2, piece2 = self.board[ny][nx]
                        if pl2 == player:
                            #nie można wejść na pole zajmowane przez swojego pionka
                            continue
                        if not self.can_beat(p, piece2, pos, pos2):
                            #nie można wejśc na pole zajmowane przez silniejszego wrogiego pionka
                            continue
                    res.append((pos, pos2))
        return res

    def pre_victory(self, player):
        opp = 1 - player
        c = 3*opp
        t1, t2, t3 = self.traps_arr[c+0], self.traps_arr[c+1], self.traps_arr[c+2]
        tab = [t1, t2, t3]
        p1 = self.board[t1[1]][t1[0]]
        p2 = self.board[t2[1]][t2[0]]
        p3 = self.board[t3[1]][t3[0]]
        ps = [p1, p2, p3]
        for i in range(3):
            if ps[i] and ps[i][0] == player:
                ok = True
                for e in self.near_traps[tab[i]]:
                    if self.board[e[1]][e[0]] and self.board[e[1]][e[0]][0] == opp:
                        ok = False
                if ok:
                    return True
        return False
        
    def victory(self, player):
        oponent = 1-player        
        if len(self.pieces[oponent]) == 0:
            self.winner = player
            return True

        x, y = self.dens[oponent]
        if self.board[y][x]:
            self.winner = player
            return True
        
        if self.peace_counter >= Jungle.MAXIMAL_PASSIVE:
            self.winner = None
            return True
            r = self.pieces_comparison()
            if r is None:
                self.winner = 1 # draw is second player's victory 
            else:
                self.winner = r
            return True
        return False

    def do_move(self, m):
        self.curplayer = 1 - self.curplayer
        if m is None:
            return
        pos1, pos2 = m
        x, y = pos1
        #(m, self.curplayer)
        pl, pc = self.board[y][x]

        x2, y2 = pos2
        if self.board[y2][x2]:  # piece taken!
            pl2, pc2 = self.board[y2][x2]
            del self.pieces[pl2][pc2]
            self.peace_counter = 0
        else:
            self.peace_counter += 1    

        self.pieces[pl][pc] = (x2, y2)
        self.board[y2][x2] = (pl, pc)
        self.board[y][x] = None

    def assess_sit(self, pl):
        return self.board_situation(pl)
    
    def pawn_points(self, pl):
        res = [0, 0]
        for i in range(7,-1,-1):
            for p in [0,1]:
                if i in self.pieces[p]:
                    res[p] += self.PIECE_VALUES[i]
        if pl == 0:
            return res[0] - res[1]
        else:
            return res[1] - res[0]

    def manh_dist(self, x1, y1, x2, y2):
        return abs(x1 - x2) + abs(y1 - y2)

    attack = [elephant, wolf, lion, jaguar]
    deffence = [cat, dog, tiger]

    def pawn_positions(self, pl):
        sum = 0
        opp = 1-pl
        opp_den = self.dens[opp]
        for i in self.attack:
            if i in self.pieces[pl]:
                x = self.pieces[pl][i][0]
                y = self.pieces[pl][i][1]
                sum += self.manh_dist(opp_den[0], opp_den[1], x, y)

        if self.elephant in self.pieces[opp] and self.rat in self.pieces[pl]:
            ex = self.pieces[opp][self.elephant][0]
            ey = self.pieces[opp][self.elephant][1]
            rx = self.pieces[pl][self.rat][0]
            ry = self.pieces[pl][self.rat][1]
            sum += self.manh_dist(ex, ey, rx, ry)*5 
        if self.elephant in self.pieces[pl] and self.nmoves < 10:
            ex = self.pieces[pl][self.elephant][0]
            sum -= abs(3-ex)*5
        my_den = self.dens[pl]
        min = 1000
        min_x = -1
        min_y = -1
        my_min = 1000
        for i in range(8):
            if i in self.pieces[opp]:
                x = self.pieces[opp][i][0]
                y = self.pieces[opp][i][1]
                dist = self.manh_dist(my_den[0], my_den[1], x, y)
                if dist < min:
                    min = dist
                    min_x = x
                    min_y = y
            if i in self.pieces[pl]:
                x = self.pieces[pl][i][0]
                y = self.pieces[pl][i][1]
                dist = self.manh_dist(opp_den[0], opp_den[1], x, y)
                if dist < my_min:
                    my_min = dist
        late = False
        if my_min > min or (my_min == min and self.curplayer != pl):
            late = True
        if self.tiger in self.pieces[pl]:
            tiger_dist = self.manh_dist(my_den[0], my_den[1], self.pieces[pl][self.tiger][0], self.pieces[pl][self.tiger][1])
            if tiger_dist > min + 6:
                sum += tiger_dist*100
                sum += self.manh_dist(min_x, min_y, self.pieces[pl][self.tiger][0], self.pieces[pl][self.tiger][1]) * 100
        return (sum*-1, late)

    def board_situation(self, pl):
        pawn_points= self.pawn_points(pl)
        if self.victory(pl):
            if self.winner == pl:
                pawn_points += 100
            elif self.winner == 1 - pl:
                pawn_points -= 100
            else:
                pawn_points -= 100
        if self.pre_victory(pl):
            pawn_points += 50
        if self.pre_victory(1-pl):
            pawn_points -= 50
    
        pawn_pos, late = self.pawn_positions(pl)
        if late:
            pawn_points -= 5
        return (pawn_points, pawn_pos)

    def update(self, player, move_string):
        #sprawdza czy ruch jest dozwolony i jeśli jest to zmienia stan planszy
        #zwraca zwycięskiego gracza jeśli taki jest
        assert player == self.curplayer
        move = tuple(int(m) for m in move_string.split())
        if len(move) != 4:
            raise WrongMove
        possible_moves = self.moves(player)
        if not possible_moves:
            if move != (-1, -1, -1, -1):
                raise WrongMove
            move = None
        else:
            move = ((move[0], move[1]), (move[2], move[3]))
            if move not in possible_moves:
                raise WrongMove
        self.nmoves += 1
        self.do_move(move)
        
        if self.victory(player):
            assert self.winner is not None
            return 2 * self.winner - 1
        else:
            return None



class Player(object):
    def __init__(self):
        self.reset()

    def reset(self):
        self.game = Jungle()
        self.my_player = 1
        self.say('RDY')

    def say(self, what):
        sys.stdout.write(what)
        sys.stdout.write('\n')
        sys.stdout.flush()

    def hear(self):
        line = sys.stdin.readline().split()
        return line[0], line[1:]    

    def pretend_move(self, move):
        self.game.curplayer = 1 - self.game.curplayer
        if move is None:
            return (None, None, None)
        pos1, pos2 = move
        x, y = pos1
        pl, pc = self.game.board[y][x]
        x2, y2 = pos2

        beaten = None
        peaceCnt = self.game.peace_counter
        if self.game.board[y2][x2]:  # piece taken!
            beaten = self.game.board[y2][x2]
            pl2, pc2 = beaten
            del self.game.pieces[pl2][pc2]
            self.game.peace_counter = 0
        else:
            self.game.peace_counter += 1    

        self.game.pieces[pl][pc] = (x2, y2)
        self.game.board[y2][x2] = (pl, pc)
        self.game.board[y][x] = None
        return (move, beaten, peaceCnt, self.game.winner)

    def unpretend_move(self, args):
        move, beaten, peaceCnt, winner = args
        self.game.curplayer = 1 - self.game.curplayer
        self.game.winner = winner
        if move is None:
            return
        pos1, pos2 = move
        x, y = pos1
        x2, y2 = pos2
        pl, pc = self.game.board[y2][x2]
        self.game.pieces[pl][pc] =  (x, y)
        self.game.board[y][x] = (pl, pc)
        self.game.board[y2][x2] = beaten
        self.game.peace_counter = peaceCnt
        if beaten:
            pl2, pc2 = beaten
            self.game.pieces[pl2][pc2] = pos2

    def compare_score(self, a, b):
        if a[0] > b[0]:
            return True
        elif a[0] == b[0] and a[1] > b[1]:
            return True
        elif a[0] == b[0] and a[1] == b[1] and bool(random.getrandbits(1)):
                return True
        return False

    def minmax(self, d, player):
        if d == 0:
            return (self.game.assess_sit(self.my_player), None)
        ms = self.game.moves(player)
        if not ms:
            return (self.game.assess_sit(self.my_player), None)
        if player == self.my_player:
            #max
            mscore = (-10000, -10000)
            bmove = None
            for m in ms:
                #zrob ruch
                args = self.pretend_move(m)
                sc, mov = self.minmax(d-1, 1-player)
                #cofnij ruch
                self.unpretend_move(args)
                if self.compare_score(sc, mscore):
                    mscore = sc
                    bmove = m
            return (mscore, bmove)
        else:
            mscore = (10000, 10000)
            bmove = None
            for m in ms:
                #zrob ruch
                args = self.pretend_move(m)
                sc, mov = self.minmax(d-1, 1-player)
                #cofnij ruch
                self.unpretend_move(args)
                if self.compare_score(mscore, sc):
                    mscore = sc
                    bmove = m
            return (mscore, bmove)

    def choose_move(self):
        depth = 2
        move = self.minmax(depth, self.my_player)
        return move[1]

    def loop(self):
        while True:
            cmd, args = self.hear()
            if cmd == 'HEDID':
                unused_move_timeout, unused_game_timeout = args[:2]
                move = tuple((int(m) for m in args[2:]))
                if move == (-1, -1, -1, -1):
                    move = None
                else:
                    xs, ys, xd, yd = move
                    move = ( (xs, ys), (xd, yd))
                        
                self.game.do_move(move)
            elif cmd == 'ONEMORE':
                self.reset()
                continue
            elif cmd == 'BYE':
                break
            else:
                assert cmd == 'UGO'
                self.my_player = 0

            move = self.choose_move()
            self.game.do_move(move)
            if move:
                move = (move[0][0], move[0][1], move[1][0], move[1][1])
            else:
                move = (-1, -1, -1, -1)
            self.say('IDO %d %d %d %d' % move)


if __name__ == '__main__':
    player = Player()
    player.loop()
