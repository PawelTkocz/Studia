import random
import sys

M = 8

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

class Reversi:
    dirs  = [ (0,1), (1,0), (-1,0), (0,-1), (1,1), (-1,-1), (1,-1), (-1,1) ] 
    
    def pawns(self, player):
        if player == 0:
            return 100 * (self.npawns0 - self.npawns1) / (self.npawns0 + self.npawns1)
        else:
            return 100 * (self.npawns1 - self.npawns0) / (self.npawns0 + self.npawns1)

    def mobility(self, player):
        p = len(self.moves(player))
        o = len(self.moves(1-player))
        if p + o == 0:
            return 0
        return 100 * (p - o) / (p + o)

    def corners(self, player):
        opp = 1 - player
        p = 0
        o = 0
        xs = [0, 7]
        for i in range(2):
            for j in range(2):
                v = self.board[xs[i]][xs[j]]
                if (v is not None and v == opp) or (v is None and not self.move_legal(xs[j], xs[i], player)):
                    p -= 1
                elif v is not None and v == player:
                    p += 1    
                elif v is None and self.move_legal(xs[j], xs[i], player):
                    p += 0.5                
        for i in range(2):
            for j in range(2):
                v = self.board[xs[i]][xs[j]]
                if (v is not None and v == player) or (v is None and not self.move_legal(xs[j], xs[i], opp)):
                    o -= 1
                elif v is not None and v == opp:
                    o += 1    
                elif v is None and self.move_legal(xs[j], xs[i], opp):
                    o += 0  
        if abs(p) + abs(o) == 0:
            return 0
        return 100 * (p - o) / (abs(p) + abs(o))

#    def count_stables(self):


    def stability(self, player):        
        res = [0, 0]
        c1 = self.board[0][0]
        c2 = self.board[7][0]
        c3 = self.board[0][7]
        c4 = self.board[7][7]

        last = 8
        if c1 is not None:
            for i in range(8):
                if self.board[i][0] == c1:
                    res[c1] += 1
                else:
                    last = i
                    break
        if c2 is not None:
            for i in range(7, last-1, -1):
                if self.board[i][0] == c2:
                    res[c2] += 1
                else:
                    break

        last = 8
        if c3 is not None:
            for i in range(8):
                if self.board[i][7] == c3:
                    res[c3] += 1
                else:
                    last = i
                    break
        if c4 is not None:
            for i in range(7, last-1, -1):
                if self.board[i][7] == c4:
                    res[c4] += 1
                else:
                    break        

        last = 8
        if c1 is not None:
            for i in range(8):
                if self.board[0][i] == c1:
                    res[c1] += 1
                else:
                    last = i
                    break
        if c3 is not None:
            for i in range(7, last-1, -1):
                if self.board[0][i] == c3:
                    res[c3] += 1
                else:
                    break  

                last = 8
        
        last = 8
        if c2 is not None:
            for i in range(8):
                if self.board[7][i] == c2:
                    res[c2] += 1
                else:
                    last = i
                    break
        if c4 is not None:
            for i in range(7, last-1, -1):
                if self.board[7][i] == c4:
                    res[c4] += 1
                else:
                    break  

        p = res[player]
        o = res[player-1]

        if p + o == 0:
            return 0
        return 100 * (p - o) / (p + o)

    def initial_stables(self):
        S = [ [0] * (M+2) for i in range(M+2)]
        for i in range(M+2):
            S[0][i] = 1
            S[i][0] = 1
            S[M+1][i] = 1
            S[i][M+1] = 1
        S[1][1] = 1
        S[1][M-2] = 1
        S[M-2][1] = 1
        S[M-2][M-2] = 1
        return S

    def initial_board(self):
        B = [ [None] * M for i in range(M)]
        B[3][3] = 1
        B[4][4] = 1
        B[3][4] = 0
        B[4][3] = 0
        return B
    
    def move_legal(self, x, y, player):
        if any( self.can_beat(x,y, direction, player) for direction in self.dirs):
            return True
        return False

    def __init__(self):
        self.board = self.initial_board()
        self.stables = self.initial_stables()
        self.fields = set()
        self.move_list = []
        self.winner = None
        self.curplayer = 0
        self.npawns0 = 2
        self.npawns1 = 2
        for i in range(M):
            for j in range(M):
                if self.board[i][j] == None:   
                    self.fields.add( (j,i) )
                                                
    def draw(self):
        for i in range(M):
            res = []
            for j in range(M):
                b = self.board[i][j]
                if b == None:
                    res.append('.')
                elif b == 1:
                    res.append('#')
                else:
                    res.append('o')
            print(''.join(res)) 
        print()            
                                   
    def moves(self, player):
        res = []
        for (x,y) in self.fields:
            if any( self.can_beat(x,y, direction, player) for direction in self.dirs):
                res.append( (x,y) )
        if not res:
            return [None]
        return res               
    
    def can_beat(self, x,y, d, player):
        dx,dy = d
        x += dx
        y += dy
        cnt = 0
        while self.get(x,y) == 1-player:
            x += dx
            y += dy
            cnt += 1
        return cnt > 0 and self.get(x,y) == player
    
    def get(self, x,y):
        if 0 <= x < M and 0 <=y < M:
            return self.board[y][x]
        return None
                        
    def do_move(self, move, player):
        self.curplayer = 1 - self.curplayer
        self.move_list.append(move)
        
        if move == None:
            return
        x,y = move
        x0,y0 = move
        self.board[y][x] = player
        if player == 0:
            self.npawns0 += 1
        else:
            self.npawns1 += 1
        self.fields -= set([move])
        for dx,dy in self.dirs:
            x,y = x0,y0
            to_beat = []
            x += dx
            y += dy
            while self.get(x,y) == 1-player:
              to_beat.append( (x,y) )
              x += dx
              y += dy
            if self.get(x,y) == player:              
                for (nx,ny) in to_beat:
                    self.board[ny][nx] = player
                if player == 0:
                    self.npawns0 += len(to_beat)
                    self.npawns1 -= len(to_beat)
                else:
                    self.npawns1 += len(to_beat)
                    self.npawns0 -= len(to_beat)
                                                     
    def victory(self, player):
        opponent = 1 - player
        res = 0
        for y in range(M):
            for x in range(M):
                b = self.board[y][x]                
                if b == opponent:
                    res -= 1
                elif b == player:
                    res += 1
        if res > 0:
            self.winner = player
        else:
            self.winner = opponent
        return res > 0
                
    def terminal(self):
        if not self.fields:
            return True
        if len(self.move_list) < 2:
            return False
        return self.move_list[-1] == self.move_list[-2] == None 
    
    def update(self, player, move_string):
        assert player == self.curplayer
        move = tuple(int(m) for m in move_string.split())
        if len(move) != 2:
            raise WrongMove
        possible_moves = self.moves(player)
        if not possible_moves:
            if move != (-1, -1):
                raise WrongMove
            move = None
        elif move not in possible_moves:
                raise WrongMove
        self.do_move(move, player)
        
        if self.terminal():
            assert self.winner is not None
            return 2 * self.winner - 1
        else:
            return None
        
    def assess_sit(self, player):
        c = self.corners(player)
        m = self.mobility(player)
        s = self.stability(player)
        p = self.pawns(player)
        return 30*c + 5*m + 25*s + 25*p

class Player(object):
    def __init__(self):
        self.reset()

    def reset(self):
        self.game = Reversi()
        self.my_player = 1
        self.moves_left = (M*M - 4)//2
        self.say('RDY')

    def say(self, what):
        sys.stdout.write(what)
        sys.stdout.write('\n')
        sys.stdout.flush()

    def hear(self):
        line = sys.stdin.readline().split()
        return line[0], line[1:]

    def pretend_move(self, move, player):
        self.game.move_list.append(move)
        if move == None:
            return (None, None, None)
        x,y = move
        x0,y0 = move
        self.game.board[y][x] = player
        self.game.fields -= set([move])
        changes = []
        for dx,dy in self.game.dirs:
            x,y = x0,y0
            to_beat = []
            x += dx
            y += dy
            while self.game.get(x,y) == 1-player:
              to_beat.append( (x,y) )
              x += dx
              y += dy
            if self.game.get(x,y) == player:              
                for (nx,ny) in to_beat:
                    self.game.board[ny][nx] = player
                    changes.append((ny, nx))
        if player == 0:
            self.game.npawns0 += (1 + len(changes))
            self.game.npawns1 -= len(changes)
        else:
            self.game.npawns1 += (1 + len(changes))
            self.game.npawns0 -= len(changes)
        return (move, changes, player)

    def unpretend_move(self, args):
        self.game.winner = None
        self.game.move_list.pop()
        move, changes, player = args
        x, y = move
        self.game.board[y][x] = None
        self.game.fields.add(move)
        for e in changes:
            self.game.board[e[0]][e[1]] = 1-player
        if player == 0:
            self.game.npawns0 -= (1 + len(changes))
            self.game.npawns1 += len(changes)
        else:
            self.game.npawns1 -= (1 + len(changes))
            self.game.npawns0 += len(changes)       

    def minmax(self, d, player, alpha, beta):
        if d == 0:
            return (self.game.assess_sit(self.my_player), None)
        ms = self.game.moves(player)
        if ms[0] is None:
            return (self.game.assess_sit(self.my_player), None)
        if player == self.my_player:
            #max
            mscore = -10000
            bmove = None

            for m in ms:
                #zrob ruch
                args = self.pretend_move(m, player)
                sc, mov = self.minmax(d-1, 1-player, alpha, beta)
                #cofnij ruch
                self.unpretend_move(args)

                if sc > mscore:
                    mscore = sc
                    bmove = m
                if mscore > alpha:
                    alpha = mscore
                if beta <= alpha:
                    break
            return (mscore, bmove)
        else:
            mscore = 10000
            bmove = None
            for m in ms:
                #zrob ruch
                args = self.pretend_move(m, player)
                sc, mov = self.minmax(d-1, 1-player, alpha, beta)
                #cofnij ruch
                self.unpretend_move(args)
                if sc < mscore:
                    mscore = sc
                    bmove = m
                if mscore < beta:
                    beta = mscore
                if beta <= alpha:
                    break
            return (mscore, bmove)

    def choose_move(self):
        min = -100000
        max = 100000
        depth = 1
        if self.moves_left < 7:
            depth = 2
        elif self.moves_left < 5:
            depth = 4

        move = self.minmax(depth, self.my_player, min, max)
        self.moves_left -= 1
        return move[1]

    def loop(self):
        while True:
            cmd, args = self.hear()
            if cmd == 'HEDID':
                unused_move_timeout, unused_game_timeout = args[:2]
                move = tuple((int(m) for m in args[2:]))
                if move == (-1, -1):
                    move = None
                self.game.do_move(move, self.game.curplayer)
            elif cmd == 'ONEMORE':
                self.reset()
                continue
            elif cmd == 'BYE':
                break
            else:
                assert cmd == 'UGO'
                #assert not self.game.move_list
                self.my_player = 0

            move = self.choose_move()
            self.game.do_move(move, self.my_player)
            if not move:
                move = (-1, -1)
            self.say('IDO %d %d' % move)


if __name__ == '__main__':
    player = Player()
    player.loop()
