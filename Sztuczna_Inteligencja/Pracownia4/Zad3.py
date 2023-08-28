import random
import sys

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
    traps = {(2, 0), (4, 0), (3, 1), (2, 8), (4, 8), (3, 7)}
    ponds = {(x, y) for x in [1, 2, 4, 5] for y in [3, 4, 5]}
    dens = [(3, 8), (3, 0)]
    dirs = [(0, 1), (1, 0), (-1, 0), (0, -1)]

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
                self.winner = None
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

    def copy_jungle(self, jgl):
        for y in range(9):
            for x in range(7):
                jgl.board[y][x] = self.game.board[y][x]
        jgl.pieces = {0: {}, 1: {}}
        for k, v in self.game.pieces[0].items():
            jgl.pieces[0][k] = v
        for k, v in self.game.pieces[1].items():
            jgl.pieces[1][k] = v
        jgl.curplayer = self.game.curplayer
        jgl.peace_counter = self.game.peace_counter
        
    def assess_situation(self, move, n):
        temp_game = Jungle()
        self.copy_jungle(temp_game)
        temp_game.do_move(move)
        while n > 0:
            pl = temp_game.curplayer
            moves = temp_game.moves(pl)
            if moves:
                move = random.choice(moves)
                temp_game.do_move(move)
            else:
                temp_game.do_move(None)
            n -= 1
            if temp_game.victory(pl):
                if self.game.curplayer == temp_game.winner:
                    return (1, n)
                elif 1 - self.game.curplayer == temp_game.winner:
                    return (-1, n)
                else:
                    return (-1, n)
        return (0, 0)
        
    def choose_move(self, moves):
        best = -10000
        best_move = None
        n = 20000
        n_sit = n // len(moves)
        for m in moves:
            cnt = n_sit
            sit = 0
            while cnt > 0:                
                res, cnt = self.assess_situation(m, cnt)
                sit += res
            if sit > best:
                best = sit
                best_move = m
            elif sit == best and bool(random.getrandbits(1)):
                best = sit
                best_move = m
        return best_move

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
                #assert not self.game.move_list
                self.my_player = 0

            moves = self.game.moves(self.my_player)
            if moves:
                move = self.choose_move(moves)
                self.game.do_move(move)
                move = (move[0][0], move[0][1], move[1][0], move[1][1])
            else:
                self.game.do_move(None)
                move = (-1, -1, -1, -1)
            self.say('IDO %d %d %d %d' % move)


if __name__ == '__main__':
    player = Player()
    player.loop()
