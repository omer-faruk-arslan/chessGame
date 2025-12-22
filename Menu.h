#pragma once
#include <bits/stdc++.h>
#include "Game.h"
#include "Move.h"
using namespace std;

class Menu {
    private:
    Game game;

    /**
     * Takes input from user 
    */
    Move take_input();

    void game_loop();

    public:
    Menu();
};