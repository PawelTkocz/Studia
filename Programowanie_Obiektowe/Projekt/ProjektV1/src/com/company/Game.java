package com.company;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.*;

public class Game{

    BufferedImage background_image;
    Player playerA;
    Player playerB;
    Board board;
    JFrame frame;
    GamePanel gamePanel;
    boolean build_road;
    boolean build_settlement;
    boolean build_city;
    boolean place_robber;
    boolean game_started;
    boolean player1_ready;
    boolean player2_ready;
    boolean buttons_disabled;
    boolean playerA_turn;
    Dice dice1;
    Dice dice2;

    public Game(){
        playerA = new Player(0);
        playerB = new Player(1);
        playerA_turn=true;
        frame = new JFrame("Catan");
        build_city = false;
        build_settlement = false;
        build_road = false;
        place_robber = false;
        player1_ready=true;
        player2_ready=true;
        game_started = false;
        buttons_disabled = false;
        dice1 = new Dice(6, 0);
        dice2 = new Dice(6, 1);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        try {
            background_image = ImageIO.read(new File(GraphicsInfo.bg_image_path));
        } catch (IOException e) {
            System.exit(-1);
        }
        int board_placement_x = Calculate.board_placement_x(background_image.getWidth());
        int board_placement_y = Calculate.board_placement_y();
        board = new Board(board_placement_x, board_placement_y);

        place_starting_pawns();
        start_game();
    }

    private void place_starting_pawns(){
        Settlement settlement1 = new Settlement(playerA, board.buildings_positions[17][0], board.buildings_positions[17][1], true, -1);
        board.buildings_on_board[17] = settlement1;
        Settlement settlement4 = new Settlement(playerB, board.buildings_positions[40][0], board.buildings_positions[40][1], true, -1);
        board.buildings_on_board[40] = settlement4;
        give_starting_resources();
        Settlement settlement2 = new Settlement(playerA, board.buildings_positions[31][0], board.buildings_positions[31][1], true, -1);
        board.buildings_on_board[31] = settlement2;
        Settlement settlement3 = new Settlement(playerB, board.buildings_positions[14][0], board.buildings_positions[14][1], true, -1);
        board.buildings_on_board[14] = settlement3;
        int x = board.roads_positions[25][0];
        int y = board.roads_positions[25][1];
        int building_id_1=road_building_id_1(x, y, 3);
        int building_id_2=road_building_id_2(x, y, 3);
        Road road1 = new Road(playerA, x, y, 3,true, building_id_1, building_id_2);
        board.roads_on_board[25] = road1;
        x = board.roads_positions[37][0];
        y = board.roads_positions[37][1];
        building_id_1=road_building_id_1(x, y, 2);
        building_id_2=road_building_id_2(x, y, 2);
        Road road2 = new Road(playerA, x, y, 2, true, building_id_1, building_id_2);
        board.roads_on_board[37] = road2;
        x = board.roads_positions[15][0];
        y = board.roads_positions[15][1];
        building_id_1=road_building_id_1(x, y, 1);
        building_id_2=road_building_id_2(x, y, 1);
        Road road3 = new Road(playerB, x, y, 1, true, building_id_1, building_id_2);
        board.roads_on_board[15] = road3;
        x = board.roads_positions[58][0];
        y = board.roads_positions[58][1];
        building_id_1=road_building_id_1(x, y, 1);
        building_id_2=road_building_id_2(x, y, 1);
        Road road4 = new Road(playerB, x, y, 1, true, building_id_1, building_id_2);
        board.roads_on_board[58] = road4;
    }

    private int road_building_id_1(int x, int y, int dir){
        if(dir==1)return Calculate.get_building_id(x-GraphicsInfo.terrain_width/4, (int)(y-Calculate.a/4), board.buildings_positions);
        else if(dir==2)return Calculate.get_building_id(x, (int)(y-Calculate.a/2), board.buildings_positions);
        else return Calculate.get_building_id(x-GraphicsInfo.terrain_width/4, (int)(y+Calculate.a/4), board.buildings_positions);
    }

    private int road_building_id_2(int x, int y, int dir){
        if(dir==1)return Calculate.get_building_id(x+GraphicsInfo.terrain_width/4, (int)(y+Calculate.a/4), board.buildings_positions);
        else if(dir==2)return Calculate.get_building_id(x, (int)(y+Calculate.a/2), board.buildings_positions);
        else return Calculate.get_building_id(x+GraphicsInfo.terrain_width/4, (int)(y-Calculate.a/4), board.buildings_positions);
    }


    private void give_starting_resources(){
        for(int i=2; i<=12; i++){
            give_resources(i);
        }
    }

    private void start_game(){
        gamePanel = new GamePanel(this);
        frame.add(gamePanel);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    void mouse_clicked(int x, int y){
        if(build_settlement){
            build_settlement=false;
            for(int i=0; i<54; i++){
                int x_b = board.buildings_positions[i][0];
                int y_b = board.buildings_positions[i][1];
                if(Calculate.clicked_in_area(x, y, x_b, y_b)){
                    if(board.buildings_on_board[i] == null && current_player().road_leading_to_building_id(i)){
                        if(Calculate.buildings_not_too_close(x_b, y_b, board.buildings_on_board, board.buildings_positions)){
                            Settlement settlement = new Settlement(current_player(), x_b, y_b, false, get_harbour_id(i));
                            board.buildings_on_board[i] = settlement;
                            if(current_player().game_over()){
                                show_winner();
                            }
                        }
                    }
                    refresh_board();
                    return;
                }
            }
            refresh_board();
            return;
        }
        else if(build_city){
            build_city=false;
            for(int i=0; i<54; i++){
                int x_b = board.buildings_positions[i][0];
                int y_b = board.buildings_positions[i][1];
                if(Calculate.clicked_in_area(x, y, x_b, y_b)){
                    if((board.buildings_on_board[i] != null) && (board.buildings_on_board[i] instanceof Settlement)){
                        if(board.buildings_on_board[i].player == current_player()){
                            City city = new City(current_player(), x_b, y_b, false);
                            board.buildings_on_board[i] = city;
                            if(current_player().game_over()){
                                show_winner();
                            }
                        }
                    }
                    refresh_board();
                    return;
                }
            }
            refresh_board();
            return;
        }
        else if(build_road){
            build_road = false;
            for(int i=0; i<72; i++){
                int x_b = board.roads_positions[i][0];
                int y_b = board.roads_positions[i][1];
                if(Calculate.clicked_in_area(x, y, x_b, y_b)){
                    int direction = Calculate.get_road_direction(i);
                    int building_id_1 = road_building_id_1(x_b, y_b, direction);
                    int building_id_2 = road_building_id_2(x_b, y_b, direction);
                    if(board.roads_on_board[i] == null){
                        if(current_player().road_leading_to_building_id(building_id_1) || current_player().road_leading_to_building_id(building_id_2)){
                            Road road = new Road(current_player(), x_b, y_b, direction, false, building_id_1, building_id_2);
                            board.roads_on_board[i] = road;
                        }
                    }
                   refresh_board();
                   return;
                }
            }
            refresh_board();
            return;
        }
        else if(place_robber){
            for(int i=0; i<19; i++){
                int x_b = board.terrains_positions[i][0];
                int y_b = board.terrains_positions[i][1];
                if(Calculate.terrain_clicked_in_area(x, y, x_b, y_b)){
                    if(!board.board[i].robber){
                        board.board[board.robber.terrain_id].robber = false;
                        board.robber.terrain_id = i;
                        board.board[i].robber = true;
                        board.robber.move(x_b, y_b);
                        steal_random_resource(current_player(), not_current_player(), board.board[i]);
                        place_robber=false;
                        buttons_disabled=false;
                        refresh_board();
                    }
                }
            }
        }
    }

    public void throw_dices(){
        if(game_started==false)game_started=true;
        else playerA_turn = !playerA_turn;

        int v1 = dice1.throw_dice();
        int v2 = dice2.throw_dice();
        int sum= v1+v2;
        boolean robber=false;
        if(sum!=7){
            give_resources(sum);
        }
        else {
            robber=true;
            buttons_disabled=true;
        }
        refresh_board();
        if(robber)robber_move();
    }

    int get_harbour_id(int building_id){
        for(int i=0; i<board.harbours_id_positions.length; i++){
            for(int j=0; j<board.harbours_id_positions[i].length; j++){
                if(board.harbours_id_positions[i][j]==building_id)return i;
            }
        }
        return -1;
    }

    void robber_move(){
        int cards_to_reject;
        boolean stolen = false;
        if(playerB.hand.resource_cards()>7){
            stolen = true;
            player2_ready=false;
            cards_to_reject = playerB.hand.resource_cards()/2;
            ask_to_reject_cards(playerB, cards_to_reject);
        }
        if(playerA.hand.resource_cards()>7){
            stolen = true;
            player1_ready=false;
            cards_to_reject = playerA.hand.resource_cards()/2;
            ask_to_reject_cards(playerA, cards_to_reject);
        }
        if(!stolen)place_robber=true;
    }

    private void steal_random_resource(Player thief, Player victim, Terrain terrain){
        if(victim.hand.resource_cards()==0)return;
        boolean can_steal=false;
        for(int i=0; i<6; i++){
            if(board.buildings_on_board[terrain.buildings_around_id[i]] != null){
                if(board.buildings_on_board[terrain.buildings_around_id[i]].player==victim){
                    can_steal=true;
                    break;
                }
            }
        }
        if(can_steal){
            Resources.Resource stolen_resource = victim.hand.loose_random_resource();
            thief.hand.change_resource_counter(stolen_resource, 1);
        }
    }

    public boolean player_can_trade_4_1(){
        for(int i=0; i<5; i++){
            if(current_player().hand.get_number(Resources.resource_array[i])>=4)return true;
        }
        return false;
    }

    public boolean player_can_trade_harbour(){
        Player player = current_player();
        for(int i=0; i<5; i++){
            if(player.harbours_available[i]){
                if(player.hand.get_number(Resources.resource_array[i])>=2)return true;
            }
        }
        if(player.harbours_available[5]){
            for(int i=0; i<5; i++){
                if(player.hand.get_number(Resources.resource_array[i])>=3)return true;
            }
        }
        return false;
    }

    void player_ready(Player player){
        if(player.player_id==0)player1_ready=true;
        else player2_ready=true;
    }

    private void ask_to_reject_cards(Player player, int cards){
        JFrame frame_robber = new JFrame("Robber");
        frame_robber.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        frame_robber.setResizable(false);
        RobberPanel robberPanel = new RobberPanel(this, player, cards, frame_robber);
        frame_robber.add(robberPanel);
        frame_robber.pack();
        frame_robber.setLocationRelativeTo(null);
        frame_robber.setVisible(true);
    }

    void give_resources(int sum){
        for(Terrain t : board.board){
            t.give_resources(board.buildings_on_board, sum);
        }
    }

    void refresh_board(){
        gamePanel.repaint();
    }

    boolean player_can_afford_road(){
        if(playerA_turn) return playerA.hand.can_afford_road();
        else return playerB.hand.can_afford_road();
    }

    boolean player_can_afford_settlement(){
        if(playerA_turn) return playerA.hand.can_afford_settlement();
        else return playerB.hand.can_afford_settlement();
    }

    Player current_player(){
        if(playerA_turn) return playerA;
        else return playerB;
    }

    Player not_current_player(){
        if(playerA_turn)return playerB;
        else return playerA;
    }

    boolean ready_to_end_turn(){
        return both_players_ready();
    }

    boolean both_players_ready(){
        return player1_ready && player2_ready;
    }

    void trade_3or4_1(int val){
        buttons_disabled = true;
        JFrame frame_trade = new JFrame("Trade");
        frame_trade.setResizable(false);
        Trade3or4Panel panel = new Trade3or4Panel(this, current_player(), frame_trade, val);
        frame_trade.add(panel);
        frame_trade.pack();
        frame_trade.setLocationRelativeTo(null);
        frame_trade.setVisible(true);
        refresh_board();
    }

    void player_trade(){
        buttons_disabled=true;
        JFrame frame_trade = new JFrame("Trade");
        frame_trade.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        frame_trade.setResizable(false);
        PlayerTradePanel panel = new PlayerTradePanel(this, playerA, playerB, frame_trade);
        frame_trade.add(panel);
        frame_trade.pack();
        frame_trade.setLocationRelativeTo(null);
        frame_trade.setVisible(true);
        refresh_board();
    }

    void trade_harbour(){
        buttons_disabled=true;
        JFrame frame_trade = new JFrame("Trade");
        frame_trade.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        frame_trade.setResizable(false);
        TradeHarbourPanel panel = new TradeHarbourPanel(this, current_player(), frame_trade);
        frame_trade.add(panel);
        frame_trade.pack();
        frame_trade.setLocationRelativeTo(null);
        frame_trade.setVisible(true);
        refresh_board();
    }

    boolean player_can_trade(int harbour_id){
        return current_player().harbours_available[harbour_id];
    }

    void trade_2_1(Resources.Resource resource){
        buttons_disabled = true;
        JFrame frame_trade = new JFrame("Trade");
        frame_trade.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        frame_trade.setResizable(false);
        Trade2to1Panel panel = new Trade2to1Panel(this, current_player(), frame_trade, resource);
        frame_trade.add(panel);
        frame_trade.pack();
        frame_trade.setLocationRelativeTo(null);
        frame_trade.setVisible(true);
        refresh_board();
    }

    void show_winner(){
        buttons_disabled = true;
        JFrame frame_game_over = new JFrame("Game over");
        frame_game_over.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame_game_over.setResizable(false);
        GameOverPanel panel = new GameOverPanel(this, current_player(), not_current_player(), frame);
        frame_game_over.add(panel);
        frame_game_over.pack();
        frame_game_over.setLocationRelativeTo(null);
        frame_game_over.setVisible(true);
        refresh_board();
    }

    void trade_3_1(){
        trade_3or4_1(3);
    }

    void trade_4_1(){
        trade_3or4_1(4);
    }

    boolean player_can_build_city(){
        return (current_player().playerPawns.settlements_on_board>0 && current_player().hand.can_afford_city() && current_player().playerPawns.cities_left()>0);
    }

    boolean player_can_build_settlement(){
        return player_can_afford_settlement() && player_have_place_for_settlement() && current_player().playerPawns.settlements_left()>0;
    }

    boolean player_have_place_for_settlement(){
        int[][] b_pos = board.buildings_positions;
        Building[] b_on_board = board.buildings_on_board;

        for(int i=0; i<current_player().playerPawns.roads_on_board; i++){
            int id1 = current_player().roads[i].building_id_1;
            int id2 = current_player().roads[i].building_id_2;
            if(b_on_board[id1]==null && Calculate.buildings_not_too_close(b_pos[id1][0], b_pos[id1][1], b_on_board, b_pos)){
                return true;
            }
            if(b_on_board[id2]==null && Calculate.buildings_not_too_close(b_pos[id2][0], b_pos[id2][1], b_on_board, b_pos)){
                return true;
            }
        }
        return false;
    }

    boolean player_can_build_road(){
        return (player_can_afford_road() && current_player().playerPawns.roads_left()>0);
    }
}
