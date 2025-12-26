#pragma once
#include <vector>
#include <utility>
#include <iostream>
#include "Move.h"
#include "Piece.h"

const int board_size = 8;

class Game {
    private:

    int game_round; // odd white
    int game_state; // 0 continue , 1 checkmate white win , 2 checkmate black win , 3 4 statlemate
    int winner;  // 1 white wins 2 black wins 0 draw -1 not ended
    
    std::vector<std::vector<Piece>> game_board; // pos -> piece 
    std::vector<std::vector<std::pair<int,int>>> white_pieces; // piece -> position , if piece gone -1 -1 
    std::vector<std::vector<std::pair<int,int>>> black_pieces; // piece -> position , if piece gone -1 -1

    void init_game_board_and_pieces();

    bool points_legal_move(const Move move) const;
    bool piece_able_to_move(const Move move) const;
    bool king_checked_move(const Move move,bool in_state=false) const;
    
    
    bool in_range(const std::pair<int,int>& position) const;
    /** checks wheter any piece of current player can make any valid move */
    bool any_possible_move() const;

    public:    
    /* constructor of game */
    Game();
    /* gives a move and a copy of the game board to the validator in order to check wheter the move is valid*/
    bool is_valid_move(const Move move) const;
    bool is_ended();
    void apply_move(const Move move);
    void update_round();
    void print_board() const;
    void result() const;

//--------------------------------Getter,Setter--------------------------------------//

    /* returns a copy of game board*/
    std::vector<std::vector<Piece>> get_game_board() const;
    bool get_game_state() const;
    int get_game_round() const;

};

