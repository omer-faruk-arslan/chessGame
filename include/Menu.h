#pragma once
#include <bits/stdc++.h>
#include "Game.h"
#include "Move.h"
using namespace std;

class Menu {
    private:
    
    Game game;
    Move take_input();
    void game_loop();

    public:
    Menu();
};