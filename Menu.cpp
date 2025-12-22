#include "Menu.h"

Move Menu::take_input(){
    bool input_taken = false;
    while(!input_taken){
        // uses game -> move validator
        // move is valid and not causes a check situation
    }
    return Move(pair<int,int>(),pair<int,int>());
}

void Menu::game_loop(){
    
    while(game.get_game_state()){
        game.update_round();
        game.print_board();

        break;
        
        Move round_move = take_input();

        game.apply_move(round_move); 

        game.check_game_end(); // updates game state 
    } 

    //game.result();
}


Menu::Menu(){
    game = Game();
    game_loop();
}