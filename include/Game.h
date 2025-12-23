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
    bool game_state; // true active , false pasive(ended)
    int winner;  // 1 white wins 2 black wins 0 draw -1 not ended
    
    std::vector<std::vector<Piece>> game_board; // pos -> piece 
    std::vector<std::vector<std::pair<int,int>>> white_pieces; // piece -> position
    std::vector<std::vector<std::pair<int,int>>> black_pieces; // piece -> position

    void init_game_board_and_pieces();
    
    public:    
    
    /* constructor of game */
    Game();
    /* gives a move and a copy of the game board to the validator in order to check wheter the move is valid*/
    bool is_valid_move(Move move) const;
    bool is_ended() const;
    void apply_move(Move move);
    void update_round();
    void print_board() const;

//--------------------------------Getter,Setter--------------------------------------//

    /* returns a copy of game board*/
    std::vector<std::vector<Piece>> get_game_board() const;
    bool get_game_state() const;
    int get_game_round() const;

};

