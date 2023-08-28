#include <bits/stdc++.h>
using namespace std;
#include <time.h>


typedef pair<int, int> pair_int;
typedef pair<pair<int, int>, pair<int, int>> jmove;
typedef pair<pair_int, jmove> val_move;
typedef tuple<jmove, pair_int, int, int> args;

class Jungle{
public:
    int pieces_values[8] = {4, 1, 2, 3, 5, 7, 8, 10};
    set<pair_int> ponds;
    set<pair_int> traps;
    map<int, pair_int> pieces0;
    map<int, pair_int> pieces1;
    map<int, map<int, pair_int>> pieces;
    pair_int dens[2] = {make_pair(3, 8), make_pair(3, 0)};
    pair_int dirs[4] = {make_pair(0, 1), make_pair(1, 0), make_pair(-1, 0), make_pair(0, -1)};
    int max_passive = 50;
    int mx = 7;
    int my = 9;
    int rat = 0;
    int cat = 1;
    int dog = 2;
    int wolf = 3;
    int jaguar = 4;
    int tiger = 5;
    int lion = 6;
    int elephant = 7;
    pair_int board[9][7];
    int curplayer = 0;
    int peace_counter = 0;
    int winner = -1;
    int found_moves_num;

    Jungle(){
        init_traps();
        init_ponds();
        init_board();
        init_pieces();
    }

    void init_pieces(){
        int player;
        int animal;
        for(int i=0; i<9; i++){
            for(int j=0; j<7; j++){
                pair_int p = board[i][j];
                if(!no_pawn(p)){
                    player = p.first;
                    animal = p.second;
                    if(player==0)
                        pieces0[animal] = make_pair(j, i);
                    else
                        pieces1[animal] = make_pair(j, i);
                }
            }
        }
        pieces[0] = pieces0;
        pieces[1] = pieces1;
    }

    bool no_pawn(pair_int p){
        return (p.first == -1);
    }

    void init_traps(){
        traps.insert(make_pair(2, 0));
        traps.insert(make_pair(4, 0));
        traps.insert(make_pair(3, 1));
        traps.insert(make_pair(2, 8));
        traps.insert(make_pair(4, 8));
        traps.insert(make_pair(3, 7));
    }

    void init_ponds(){
        int xs[4] = {1, 2, 4, 5};
        int ys[3] = {3, 4, 5};
        for(int i=0; i<4; i++){
            for(int j=0; j<3; j++)
                ponds.insert(make_pair(xs[i], ys[j]));
        }
    }

    void init_board(){
        string desc = "L.....T.D...C.R.J.W.E.....................e.w.j.r.c...d.t.....l";
        int player;
        int animal;
        for(int i=0; i<9; i++){
            for(int j=0; j<7; j++){
                char a = desc[7*i+j];
                if(a == '.'){
                    board[i][j] = make_pair(-1, -1);
                }
                else{
                    player = 0;
                    if('A' <= a && a <= 'Z')
                        player = 1;
                    animal = char_to_animal(a);
                    board[i][j] = make_pair(player, animal);
                }
            }
        }
    }

    int char_to_animal(char c){
        c = tolower(c);
        if(c=='r') return 0;
        if(c=='c') return 1;
        if(c=='d') return 2;
        if(c=='w') return 3;
        if(c=='j') return 4;
        if(c=='t') return 5;
        if(c=='l') return 6;
        if(c=='e') return 7;
        return -1;
    }

    char animal_to_char(int a, int pl){
        char answ;
        if(a==0) answ='r';
        if(a==1) answ='c';
        if(a==2) answ='d';
        if(a==3) answ='w';
        if(a==4) answ='j';
        if(a==5) answ='t';
        if(a==6) answ='l';
        if(a==7) answ='e';
        if(pl==0)
            answ = toupper(answ);
        return answ;
    }

    bool can_beat(int p1, int p2, pair_int pos1, pair_int pos2){
        if(ponds.count(pos1) && ponds.count(pos2))
            return true;
        if(ponds.count(pos1))
            return false;
        if(p1 == rat && p2 == elephant)
            return true;
        if(p1 == elephant && p2 == rat)
            return false;
        if(p1 >= p2)
            return true;
        if(traps.count(pos2))
            return true;
        return false;
    }

    bool rat_is_blocking(int player, pair_int pos, int dx, int dy){
        int x = pos.first;
        int y = pos.second;
        int nx = x + dx;
        int opp = 1-player;
        if(pieces[opp].count(rat)==0)
            return false;
        pair_int r = pieces[opp][rat];
        if(ponds.count(r)==0)
            return false;
        int rx = pieces[opp][rat].first;
        int ry = pieces[opp][rat].second;
        if(dy != 0 && x == rx)
            return true;
        if(dx != 0 && y == ry && abs(x-rx) <= 2 and abs(nx-rx) <= 2)
            return true;
        return false;
    }

    void draw(){
        for(int i=0; i<9; i++){
            for(int j=0; j<7; j++){
                pair_int p = board[i][j];
                if(no_pawn(p))
                    cout<<'.';
                else{
                    char a = animal_to_char(p.second, p.first);
                    cout<<a;
                }
            }
            cout<<"\n";
        }
        cout<<endl;
    }

    jmove * moves(int player){
        static jmove res[40];
        int found_moves = 0;
        for(auto i : pieces[player]){
            int p = i.first;
            pair_int pos = i.second;
            int x = pos.first;
            int y = pos.second;
            for(int j=0; j<4; j++){
                pair_int dir = dirs[j];
                int dx = dir.first;
                int dy = dir.second;
                int ny = y + dy;
                int nx = x + dx;
                pair_int pos2 = make_pair(nx, ny);
                if(0 <= nx && nx < 7 && 0 <= ny && ny < 9){
                    if(dens[player] == pos2)
                        continue;
                    if(ponds.count(pos2)){
                        if(p != rat && p != tiger && p != lion)
                            continue;
                        if(p == tiger || p == lion){
                            if(dx != 0)
                                dx *= 3;
                            if(dy != 0)
                                dy *= 4;
                            if(rat_is_blocking(player, pos, dx, dy))
                                continue;
                            nx = x+dx;
                            ny = y+dy;
                            pos2.first = nx;
                            pos2.second = ny;
                        }
                    }
                    if(!no_pawn(board[ny][nx])){
                        pair_int temp = board[ny][nx];
                        int pl2 = temp.first;
                        int piece2 = temp.second;
                        if(pl2 == player)
                            continue;
                        if(!can_beat(p, piece2, pos, pos2))
                            continue;
                    }
                    res[found_moves] = make_pair(pos, pos2);
                    found_moves++;
                }
            }
        }
        res[found_moves] = make_pair(make_pair(-1, -1), make_pair(-1, -1));
        found_moves_num = found_moves;
        return res;
    }

    jmove random_move(int player){
        jmove* ms = moves(player);
        int nmoves = 0;
        jmove temp = ms[0];
        while(temp.first.first != -1){
            nmoves++;
            temp = ms[nmoves];
        }
        if(nmoves == 0)
            return(ms[0]);
        int m = rand() % nmoves;
        return ms[m];
    }

    bool victory(int player){
        int opp = 1-player;
        if(pieces[opp].size() == 0){
            winner = player;
            return true;
        }
        pair_int d = dens[opp];
        int x = d.first;
        int y = d.second;
        if(!no_pawn(board[y][x])){
            winner = player;
            return true;
        }
        if(peace_counter >= max_passive){
            winner = 2;
            return true;
        }
        return false;
    }

    void do_move(jmove m){
        curplayer = 1 - curplayer;
        pair_int pos1 = m.first;
        pair_int pos2 = m.second;
        if(pos1.first == -1 && pos1.second == -1)
            return;
        int x = pos1.first;
        int y = pos1.second;
        pair_int temp = board[y][x];
        int pl = temp.first;
        int pc = temp.second;
        int x2 = pos2.first;
        int y2 = pos2.second;
        if(!no_pawn(board[y2][x2])){
            temp = board[y2][x2];
            int pl2 = temp.first;
            int pc2 = temp.second;
            pieces[pl2].erase(pc2);
            peace_counter = 0;
        }
        else
            peace_counter++;
        pieces[pl][pc] = pos2;
        board[y2][x2] = make_pair(pl, pc);
        board[y][x] = make_pair(-1, -1);
    }

    int update(int player, jmove m){
        if(player != curplayer){
            throw invalid_argument("not your turn");
        }
        jmove* ms = moves(player);
        int i = 0;
        bool found = false;
        while(ms[i].first.first != -1){
            if(m == ms[i]){
                i++;
                found = true;
                break;
            }
            i++;
        }
        if(i == 0 && m != make_pair(make_pair(-1, -1), make_pair(-1, -1))){
            throw invalid_argument("invalid move 1");
        }
        if(!found){
            throw invalid_argument("invalid move 2");
        }
        do_move(m);
        if(victory(player))
            return winner;
        return -1;
    }

    bool finished(){
        return (winner != -1);
    }

    bool tie(){
        return (winner == 2);
    }
};


class MCTSPlayer{
public:
    Jungle game;
    int my_player;

    MCTSPlayer(int num){
        Jungle game;
        my_player = num;
    }

    jmove make_move(){
        jmove m = choose_move();
        game.do_move(m);
        return m;
    }

    void copy_jungle(Jungle& j){
        for(int y=0; y<9; y++)
            for(int x=0; x<7; x++)
                j.board[y][x] = game.board[y][x];
        j.pieces[0].clear();
        j.pieces[1].clear();
        for(auto i : game.pieces[0]){
            int a = i.first;
            pair_int pos = i.second;
            int p1 = pos.first;
            int p2 = pos.second;
            j.pieces[0][a] = make_pair(p1, p2);
        }
        for(auto i : game.pieces[1]){
            int a = i.first;
            pair_int pos = i.second;
            int p1 = pos.first;
            int p2 = pos.second;
            j.pieces[1][a] = make_pair(p1, p2);
        }
        j.curplayer = game.curplayer;
        j.peace_counter = game.peace_counter;
    }

    pair_int assess_situation(jmove m, int n){
        Jungle temp_game;
        copy_jungle(temp_game);
        temp_game.do_move(m);
        while(n>0){
            int pl = temp_game.curplayer;
            jmove * moves = temp_game.moves(pl);
            if(temp_game.found_moves_num>0){
                m = temp_game.random_move(pl);
                temp_game.do_move(m);
            }
            else
                temp_game.do_move(make_pair(make_pair(-1, -1), make_pair(-1, -1)));
            n--;
            if(temp_game.victory(pl)){
                if(game.curplayer == temp_game.winner){
                    return make_pair(1, n);
                }
                else
                    return make_pair(-1, n);
            }
        }
        return make_pair(0, 0);
    }

    jmove choose_move(){
        jmove * moves = game.moves(my_player);
        int nmoves = game.found_moves_num;
        jmove temp_moves[nmoves];
        for(int i=0; i<nmoves; i++){
            temp_moves[i] = moves[i];
        }
        int best = -10000;
        jmove best_move;
        int n = 20000;
        int n_sit = n/nmoves;
        for(int i=0; i<nmoves; i++){
            jmove m = temp_moves[i];
            int cnt = n_sit;
            int sit = 0;
            while(cnt > 0){
                pair_int r = assess_situation(m, cnt);
                cnt = r.second;
                int res = r.first;
                sit += res;
            }
            if(sit>best){
                best = sit;
                best_move = m;
            }
            else if(sit == best && rand()%2 == 1){
                best = sit;
                best_move = m;
            }
        }
        return best_move;
    }

    void update_move(jmove m){
        game.do_move(m);
    }
};

class RandomPlayer{
public:
    Jungle game;
    int my_player;

    RandomPlayer(int num){
        Jungle game;
        my_player = num;
    }

    jmove make_move(){
        jmove m = game.random_move(my_player);
        game.do_move(m);
        return m;
    }

    void update_move(jmove m){
        game.do_move(m);
    }
};

class MyPlayer{
public:
    Jungle game;
    int my_player;
    pair_int traps_arr[6] = {make_pair(2, 8), make_pair(4, 8), make_pair(3, 7), make_pair(2, 0), make_pair(4, 0), make_pair(3, 1)};
    map <pair_int, pair_int*>near_traps;
    map <pair_int, int>near_traps_size;
    int nmoves = 0;

    pair_int p1[2] = {make_pair(1, 8), make_pair(2, 7)};
    pair_int p2[2] = {make_pair(5, 8), make_pair(4, 7)};
    pair_int p3[3] = {make_pair(2, 7), make_pair(4, 7), make_pair(3, 6)};
    pair_int p4[2] = {make_pair(1, 0), make_pair(2, 1)};
    pair_int p5[2] = {make_pair(4, 1), make_pair(5, 0)};
    pair_int p6[3] = {make_pair(2, 1), make_pair(4, 1), make_pair(3, 2)};

    MyPlayer(int num){
        Jungle game;
        my_player = num;
        near_traps[make_pair(2, 8)] = p1;
        near_traps[make_pair(4, 8)] = p2;
        near_traps[make_pair(3, 7)] = p3;
        near_traps[make_pair(2, 0)] = p4;
        near_traps[make_pair(4, 0)] = p5;
        near_traps[make_pair(3, 1)] = p6;
        near_traps_size[make_pair(2, 8)] = 2;
        near_traps_size[make_pair(4, 8)] = 2;
        near_traps_size[make_pair(3, 7)] = 3;
        near_traps_size[make_pair(2, 0)] = 2;
        near_traps_size[make_pair(4, 0)] = 2;
        near_traps_size[make_pair(3, 1)] = 3;
    }

    jmove make_move(){
        jmove m = choose_move();
        game.do_move(m);
        nmoves++;
        return m;
    }

    bool previctory(int player){
        int opp = 1-player;
        int c = 3*opp;
        pair_int t1 = traps_arr[c+0];
        pair_int t2 = traps_arr[c+1];
        pair_int t3 = traps_arr[c+2];
        pair_int tab[3] = {t1, t2, t3};
        pair_int p1 = game.board[t1.second][t1.first];
        pair_int p2 = game.board[t2.second][t2.first];
        pair_int p3 = game.board[t3.second][t3.first];
        pair_int ps[3] = {p1, p2, p3};
        for(int i=0; i<3; i++){
            if(!game.no_pawn(ps[i]) && ps[i].first == player){
                bool ok = true;
                for(int e=0; e<near_traps_size[tab[i]]; i++){
                    pair_int temp = near_traps[tab[i]][e];
                    int x = temp.first;
                    int y = temp.second;
                    if(!game.no_pawn(game.board[y][x]) && game.board[y][x].first == opp)
                        ok = false;
                }
                if(ok){
                    return true;
                }
            }
        }
        return false;
    }

    int pawn_points(){
        int res[2] = {0, 0};
        for(int i=7; i>=0; i--){
            for(int p=0; p<2; p++){
                if(game.pieces[p].count(i)!=0)
                    res[p] += game.pieces_values[i];
            }
        }
        if(my_player == 0)
            return res[0]-res[1];
        return res[1]-res[0];
    }

    int manh_dist(int x1, int y1, int x2, int y2){
        return abs(x1 - x2) + abs(y1 - y2);
    }

    pair_int pawn_positions(){
        int attack[4] = {game.elephant, game.wolf, game.lion, game.jaguar};
        int deffence[3] = {game.cat, game.dog, game.tiger};
        int sum = 0;
        int opp = 1-my_player;
        pair_int opp_den = game.dens[opp];
        for(int i=0; i<4; i++){
           if(game.pieces[my_player].count(attack[i])!=0){
                int x = game.pieces[my_player][attack[i]].first;
                int y = game.pieces[my_player][attack[i]].second;
                sum += manh_dist(opp_den.first, opp_den.second, x, y);
           }
        }
        if(game.pieces[opp].count(game.elephant) != 0 && game.pieces[my_player].count(game.rat) != 0){
            int ex = game.pieces[opp][game.elephant].first;
            int ey = game.pieces[opp][game.elephant].second;
            int rx = game.pieces[my_player][game.rat].first;
            int ry = game.pieces[my_player][game.rat].second;
            sum += manh_dist(ex, ey, rx, ry)*5;
        }
        if(game.pieces[my_player].count(game.elephant) != 0 && nmoves < 10){
            int ex = game.pieces[my_player][game.elephant].first;
            sum -= abs(3-ex)*5;
        }
        pair_int my_den = game.dens[my_player];
        int mini = 1000;
        int min_x = -1;
        int min_y = -1;
        int my_min = 1000;
        for(int i=0; i<8; i++){
            if(game.pieces[opp].count(i)!=0){
                int x=game.pieces[opp][i].first;
                int y=game.pieces[opp][i].second;
                int dist = manh_dist(my_den.first, my_den.second, x, y);
                if(dist<mini){
                    mini = dist;
                    min_x = x;
                    min_y = y;
                }
            }
            if(game.pieces[my_player].count(i) != 0){
                int x=game.pieces[my_player][i].first;
                int y=game.pieces[my_player][i].second;
                int dist = manh_dist(opp_den.first, opp_den.second, x, y);
                if(dist<my_min){
                    my_min = dist;
                }
            }
        }
        int late = 0;
        if(my_min > mini || (my_min == mini && game.curplayer != my_player))
            late = 1;
        if(game.pieces[my_player].count(game.tiger) != 0){
            int x_t = game.pieces[my_player][game.tiger].first;
            int y_t = game.pieces[my_player][game.tiger].second;
            int tiger_dist = manh_dist(my_den.first, my_den.second, x_t, y_t);
            if(tiger_dist>mini+6){
                sum += tiger_dist*100;
                sum += manh_dist(min_x, min_y, x_t, y_t) * 100;
            }
        }
        return make_pair(-1*sum, late);
    }

    pair_int assess_situation(){
        int pawn_pts = pawn_points();
        if(game.victory(my_player)){
            if(game.winner == my_player)
                pawn_pts += 100;
            else if(game.winner == 1-my_player)
                pawn_pts -= 100;
            else
                pawn_pts -=100;
        }
        if(previctory(my_player))
            pawn_pts += 50;
        if(previctory(1-my_player))
            pawn_pts -= 50;
        pair_int temp = pawn_positions();
        int pawn_pos = temp.first;
        int late = temp.second;
        if(late == 1)
            pawn_pts -= 5;
        return make_pair(pawn_pts, pawn_pos);
    }

    args pretend_move(jmove m){
        game.curplayer = 1 - game.curplayer;
        jmove null_move = make_pair(make_pair(-1, -1), make_pair(-1, -1));
        if(m == null_move)
            return make_tuple(null_move, make_pair(-1, -1), 0, 0);
        pair_int pos1 = m.first;
        pair_int pos2 = m.second;
        int x = pos1.first;
        int y = pos1.second;
        pair_int temp = game.board[y][x];
        int pl = temp.first;
        int pc = temp.second;
        int x2 = pos2.first;
        int y2 = pos2.second;
        pair_int beaten = make_pair(-1, -1);
        int peaceCnt = game.peace_counter;
        if(!game.no_pawn(game.board[y2][x2])){
            beaten = game.board[y2][x2];
            int pl2 = beaten.first;
            int pc2 = beaten.second;
            game.pieces[pl2].erase(pc2);
            game.peace_counter = 0;
        }
        else{
            game.peace_counter++;
        }
        game.pieces[pl][pc] = make_pair(x2, y2);
        game.board[y2][x2] = make_pair(pl, pc);
        game.board[y][x] = make_pair(-1, -1);
        return make_tuple(m, beaten, peaceCnt, game.winner);
    }

    void unpretend_move(args a){
        jmove m = get<0>(a);
        pair_int beaten = get<1>(a);
        int peaceCnt = get<2>(a);
        int winner = get<3>(a);
        game.curplayer = 1 - game.curplayer;
        game.winner = winner;
        jmove null_move = make_pair(make_pair(-1, -1), make_pair(-1, -1));
        if(m == null_move)
            return;
        pair_int pos1 = m.first;
        pair_int pos2 = m.second;
        int x = pos1.first;
        int y = pos1.second;
        int x2 = pos2.first;
        int y2 = pos2.second;
        pair_int temp = game.board[y2][x2];
        int pl = temp.first;
        int pc = temp.second;
        game.pieces[pl][pc] = make_pair(x, y);
        game.board[y][x] = make_pair(pl, pc);
        game.board[y2][x2] = beaten;
        game.peace_counter = peaceCnt;
        if(beaten != make_pair(-1, -1)){
            int pl2 = beaten.first;
            int pc2 = beaten.second;
            game.pieces[pl2][pc2] = pos2;
        }
    }

    bool compare_score(pair_int a, pair_int b){
        if(a.first > b.first)
            return true;
        if(a.first == b.first && a.second>b.second)
            return true;
        if(a.first == b.first && a.second == b.second && rand()%2==1)
            return true;
        return false;
    }

    val_move minimax(int d, int player){
        jmove null_move = make_pair(make_pair(-1, -1), make_pair(-1, -1));
        if(d==0)
            return make_pair(assess_situation(), null_move);
        jmove * ms = game.moves(player);
        int ms_len = game.found_moves_num;
        if(ms_len==0)
            return make_pair(assess_situation(), null_move);
        jmove ms_temp[ms_len];
        for(int i=0; i<ms_len; i++)
            ms_temp[i] = ms[i];
        if(player == my_player){
            //max
            pair_int mscore = make_pair(-10000, -10000);
            jmove bmove = null_move;
            for(int i=0; i<ms_len; i++){
                jmove m = ms_temp[i];
                args a = pretend_move(m);
                val_move temp = minimax(d-1, 1-player);
                pair_int sc = temp.first;
                unpretend_move(a);
                if(compare_score(sc, mscore)){
                    mscore = sc;
                    bmove = m;
                }
            }
            return make_pair(mscore, bmove);
        }
        else{
            //min
            pair_int mscore = make_pair(10000, 10000);
            jmove bmove = null_move;
            for(int i=0; i<ms_len; i++){
                jmove m = ms_temp[i];
                args a = pretend_move(m);
                val_move temp = minimax(d-1, 1-player);
                pair_int sc = temp.first;
                unpretend_move(a);
                if(compare_score(mscore, sc)){
                    mscore = sc;
                    bmove = m;
                }
            }
            return make_pair(mscore, bmove);
        }
    }

    jmove choose_move(){
        int depth = 2;
        val_move temp = minimax(depth, my_player);
        jmove m = temp.second;
        return m;
    }

    void update_move(jmove m){
        game.do_move(m);
    }
};

void play(int ngames, bool verbose){
    int stats[3] = {0, 0, 0};
    for(int i=0; i<ngames; i++){
        MyPlayer p0(0);
        MCTSPlayer p1(1);
        Jungle game;
        while(!game.finished()){
            if(verbose)
                game.draw();
            if(game.curplayer == 1){
                jmove m = p1.make_move();
                game.update(1, m);
                p0.update_move(m);
            }
            else{
                jmove m = p0.make_move();
                game.update(0, m);
                p1.update_move(m);
            }
        }
        if(game.tie()){
            cout<<"DRAW\n";
            stats[2]++;
        }
        else{
            cout<<"P"<<game.winner<<" WIN\n";
            stats[game.winner]++;
        }
    }
    cout<<"P0 "<<stats[0]<<" "<<stats[2]<<" "<<stats[1]<<" P1\n";
}

int main(){
    srand (time(NULL));
    int ngames = 10;
    bool verbose = false;
    play(ngames, verbose);
    return 0;
}
