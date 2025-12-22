#pragma once
#include <string> 

enum PieceType{
    empty = -1,
    pawn = 0,
    rook = 1,
    horse = 2,
    bishop = 3,
    queen = 4,
    king = 5
};

const std::string representList[] = {"Pw","Rk","Hr","Bs","Qn","Kg"};

enum Color{
    white,
    black
};

class Piece{
    private:

    PieceType type;
    Color color;
    std::string represent;
    int type_id;
    int piece_number; // which piece is this pawn 0 - 7 , other 0-1 , queen king 0

    public:
    Piece(){};

    Piece(PieceType type_,Color color_,int piece_number_): type(type_), color(color_), piece_number(piece_number_) {
        if(type == PieceType::empty) represent = " o ";
        else represent = ((color == Color::white) ? "w" : "b" ) + representList[static_cast<int>(type)];    
    }

    std::string get_represent() const{
        return represent;
    }
};
