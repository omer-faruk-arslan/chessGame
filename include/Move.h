#pragma once
#include <utility>

struct Move {
    std::pair<int,int> from;
    std::pair<int,int> to;
    Move(){}
    Move(std::pair<int,int> from,std::pair<int,int> to): from(from), to(to) {}
};
