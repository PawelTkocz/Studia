import random
import sys
import numpy as np
import copy
from collections import defaultdict

traps = {(2, 0), (4, 0), (3, 1), (2, 8), (4, 8), (3, 7)}
ponds = {(x, y) for x in [1, 2, 4, 5] for y in [3, 4, 5]}
dens = [(3, 8), (3, 0)]
dirs = [(0, 1), (1, 0), (-1, 0), (0, -1)]
rat, cat, dog, wolf, jaguar, tiger, lion, elephant = range(8)
pieces_values = [4, 1, 2, 3, 5, 7, 8, 10]
MAXIMAL_PASSIVE = 30

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def distance(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)

class MCTSNode():
    def __init__(self, board, pieces, curplayer, peace_counter, my_player, move_val=0, parent=None, parent_move=None):
        self.board = copy.deepcopy(board)
        self.pieces = copy.deepcopy(pieces)
        self.my_player = my_player
        self.curplayer = curplayer
        self.peace_counter = peace_counter
        self.parent = parent
        self.parent_move = parent_move
        self.children = []
        self.number_of_visits = move_val
        self.results = defaultdict(int)
        self.results[1] = move_val
        self.results[-1] = 0
        self.untried_moves = self.get_moves(self.board, self.pieces, self.curplayer)
        return
      
    def diff(self):
        wins = self.results[1]
        loses = self.results[-1]
        return wins - loses

    def n(self):
        return self.number_of_visits
    
    def expand(self):
        #wybiera jeden z niewypróbowanych ruchów i tworzy dziecko poprzez wykonanie tego ruchu	
        move = self.untried_moves.pop()
        new_board = copy.deepcopy(self.board)
        new_pieces = copy.deepcopy(self.pieces)
        new_curplayer = self.curplayer
        new_peace_counter = self.peace_counter
        move_val = self.move_value(new_board, new_pieces, move, self.curplayer)
        new_board,new_pieces,new_curplayer,new_peace_counter=self.move(new_board, new_pieces, new_curplayer, new_peace_counter, move)
        child_node = MCTSNode(new_board, new_pieces, new_curplayer, new_peace_counter, self.my_player, move_val = move_val, parent=self, parent_move=move)
        self.children.append(child_node)
        return child_node 
    
    def is_terminal_node(self):
        return self.is_game_over(self.board, self.pieces, self.peace_counter)
    
    def rollout(self):
        #cr = current_rollout
        cr_board = copy.deepcopy(self.board)
        cr_pieces = copy.deepcopy(self.pieces)
        cr_curplayer = self.curplayer
        cr_peace_counter = self.peace_counter    
        while not self.is_game_over(cr_board, cr_pieces, cr_peace_counter):
            possible_moves = self.get_moves(cr_board, cr_pieces, cr_curplayer)
            move = self.rollout_move(possible_moves, cr_board, cr_pieces, cr_curplayer)
            cr_board, cr_pieces, cr_curplayer, cr_peace_counter = self.move(cr_board, cr_pieces, cr_curplayer, cr_peace_counter, move)
        return self.game_result(cr_board, cr_pieces, cr_peace_counter)
    
    def backpropagate(self, result):
        self.number_of_visits += 1.
        self.results[result] += 1.
        if self.parent:
            self.parent.backpropagate(result)

    def is_fully_expanded(self):
        return len(self.untried_moves) == 0
    
    def best_child(self):
        #wywoływana kiedy węzeł rozwinął już wszystkie możliwe ruchy/dzieci
        #ma za zadanie wybranie które z dzieci jest najlepiej zasymulować
        c_param=0.1
        choices_weights = [(c.diff() / c.n()) + c_param * np.sqrt((2 * np.log(self.n()) / c.n())) for c in self.children]
        return self.children[np.argmax(choices_weights)]
    
    def final_child(self):
        move_vals = [c.n() for c in self.children]
        return self.children[np.argmax(move_vals)]

    def rollout_move(self, possible_moves, board, pieces, curplayer):
        #return possible_moves[np.random.randint(len(possible_moves))]
        if not possible_moves:
            return None
        move_vals = [self.move_value(board, pieces, m, curplayer) for m in possible_moves]
        return possible_moves[np.argmax(move_vals)]
    
    def tree_policy(self):
        #ma za zadanie znalezienie węzła do symulacji
        #zaczyna szukanie zawsze od korzenia
        #jeśli natrafi na węzeł który nie jest końcem gry:
        #jeśli jest jeszcze ruch którego nie rozważał to zwraca ten ruch w nowym węźle
        #wpp wybiera najabardziej nadający się do symulacji spośród tych ruchów
        #jeśli natrafi na węzeł oznaczający koniec gry to go zwraca
        current_node = self
        while not current_node.is_terminal_node():
            if not current_node.is_fully_expanded():
                return current_node.expand()
            else:
                current_node = current_node.best_child()
        return current_node
    
    def best_move(self, n):
        #wykonywany tylko raz, jako wywołanie symulacji MCTS
        #n razy wykonuje trzy kroki: 
        #1) v = wynik selekcji węzła
        #2) wykonuje rollout czyli sumulacje na v
        #3) propaguje wynik symulacji w górę aż do korzenia
        #na koniec wybiera najlepszy z możliwych ruchów
        simulation_no = n
        for i in range(simulation_no):
            v = self.tree_policy()
            reward = v.rollout()
            v.backpropagate(reward)
        
        return self.final_child()
    
    def get_moves(self, board, pieces, player): 
        res = []
        for p, pos in pieces[player].items():
            x, y = pos
            for (dx, dy) in dirs:
                pos2 = (nx, ny) = (x+dx, y+dy)
                if 0 <= nx < 7 and 0 <= ny < 9:
                    if dens[player] == pos2:
                        continue
                    if pos2 in ponds:
                        if p not in (rat, tiger, lion):
                            continue
                        if p == tiger or p == lion:
                            if dx != 0:
                                dx *= 3
                            if dy != 0:
                                dy *= 4
                            if self.rat_is_blocking(pieces, player, pos, dx, dy):
                                continue
                            pos2 = (nx, ny) = (x+dx, y+dy)
                    if board[ny][nx] is not None:
                        pl2, piece2 = board[ny][nx]
                        if pl2 == player:
                            continue
                        if not self.can_beat(p, piece2, pos, pos2):
                            continue
                    res.append((pos, pos2))
        return res

    def is_game_over(self, board, pieces, peace_counter):        
        if len(pieces[0]) == 0 or len(pieces[1]) == 0:
            return True
        x, y = dens[0]
        if board[y][x]:
            return True
        x, y = dens[1]
        if board[y][x]:
            return True
        if peace_counter >= MAXIMAL_PASSIVE:
            return True

    def game_result(self, board, pieces, peace_counter):
        player = self.my_player
        oponent = 1-player        
        if len(pieces[oponent]) == 0:
            return 1
        if len(pieces[player]) == 0:
            return -1

        x, y = dens[oponent]
        if board[y][x]:
            return 1
        x, y = dens[player]
        if board[y][x]:
            return -1
        
        if peace_counter >= MAXIMAL_PASSIVE:
            return -1

    def move(self, board, pieces, curplayer, peace_counter, m):
        new_cur_player = 1 - curplayer
        if m is None:
            return (board, pieces, new_cur_player, peace_counter)
        new_peace_counter = peace_counter
        pos1, pos2 = m
        x, y = pos1
        pl, pc = board[y][x]
        x2, y2 = pos2
        if board[y2][x2]:  # piece taken!
            pl2, pc2 = board[y2][x2]
            del pieces[pl2][pc2]
            new_peace_counter = 0
        else:
            new_peace_counter += 1    

        pieces[pl][pc] = (x2, y2)
        board[y2][x2] = (pl, pc)
        board[y][x] = None
        return (board, pieces, new_cur_player, new_peace_counter)
    
    def rat_is_blocking(self, pieces, player, pos, dx, dy):       
        x, y = pos
        nx = x + dx
        if rat not in pieces[1-player]:
            return False
        rx, ry = pieces[1-player][rat]
        if (rx, ry) not in ponds:
            return False
        if dy != 0:
            if x == rx:
                return True
        if dx != 0:
            if y == ry and abs(x-rx) <= 2 and abs(nx-rx) <= 2:
                return True
        return False

    def move_value(self, board, pieces, move, curplayer):
        res = 0
        opp = 1-curplayer
        dx, dy = dens[opp]
        x1, y1 = move[0]
        x2, y2 = move[1]
        d1 = distance(dx, dy, x1, y1)
        d2 = distance(dx, dy, x2, y2)
        if(d2<d1):
            res += 1
        if(board[y2][x2]):
            res += (pieces_values[board[y2][x2][1]]+1)//2
        mini = 100
        for i in pieces[curplayer]:
                x = pieces[curplayer][i][0]
                y = pieces[curplayer][i][1]
                dist = distance(dx, dy, x, y)
                if(dist < mini):
                    mini = dist
        if(d2 < mini):
            res += 1
        return res
        
    def can_beat(self, p1, p2, pos1, pos2):
        if pos1 in ponds and pos2 in ponds:
            return True  # rat vs rat
        if pos1 in ponds:
            return False  # rat in pond cannot beat any piece on land
        if p1 == rat and p2 == elephant:
            return True
        if p1 == elephant and p2 == rat:
            return False
        if p1 >= p2:
            return True
        if pos2 in traps:
            return True
        return False


class Jungle:
    def __init__(self):
        self.board = self.initial_board()
        self.pieces = {0: {}, 1: {}}
        for y in range(9):
            for x in range(7):
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

    def do_move(self, m):
        self.curplayer = 1 - self.curplayer
        if m is None:
            return
        pos1, pos2 = m
        x, y = pos1
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


mcts_param = 400

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

    def choose_move(self):
        root = MCTSNode(self.game.board, self.game.pieces, self.game.curplayer, self.game.curplayer, self.my_player)
        best_node = root.best_move(mcts_param)   
        return best_node.parent_move

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
