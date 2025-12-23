#include "Move.h"
#include <vector>
#include "Piece.h"

class MoveValidator{
    public:
    static bool is_valid(bool round_player_white,Move move,std::vector<std::vector<Piece>> board);

    static bool is_ended(bool round_player_white,std::vector<std::vector<Piece>> board);
};