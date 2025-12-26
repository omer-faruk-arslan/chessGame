#include "../include/Menu.h"

Move Menu::take_input(){
    bool input_taken = false;
    std::pair<int,int> from_pair;
    std::pair<int,int> to_pair;

    while(!input_taken){
        
        std::cout << "Enter coordinates (from to): " ;
        std::string from,to;std::cin>>from>>to;
        
        if(from.size() != 2 || to.size() != 2 ) {
            std::cout << "Invalid input! Enter (letter)(number). " << std::endl;
            continue;
        }
        from_pair = {board_size-(from[1]-'0'),from[0]-'a'};
        to_pair = {board_size-(to[1]-'0'),to[0]-'a'};
        if(        from_pair.first<0 || from_pair.first>=board_size
                || from_pair.second<0 || from_pair.second>=board_size 
                || to_pair.first<0 || to_pair.first>=board_size
                || to_pair.second<0 || to_pair.second>=board_size) 
        {
            std::cout << "Invalid input! input out of board. " << std::endl;
            continue;
        }

        input_taken = true;
    }
    return Move(from_pair,to_pair);
}

void Menu::game_loop(){
    
    bool is_ended = false;
    while(!is_ended){
        game.print_board();
        Move round_move;
        bool move_is_valid = false;
        while(!move_is_valid){
            round_move = take_input();
            if(game.is_valid_move(round_move)) move_is_valid = true;
            else std::cout << "Move is invalid!" << std::endl;
        }
        game.apply_move(round_move); 
        game.update_round();
        is_ended = game.is_ended(); // updates game state 
    } 
    game.result();
}


Menu::Menu(){
    game = Game();
    game_loop();
}