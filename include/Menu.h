#pragma once
#include "Game.h"
#include "Move.h"

class Menu {
    private:
    
    Game game;
    Move take_input();
    void game_loop();

    public:
    Menu();
};