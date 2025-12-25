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
    black,
    none
};

class Piece{
    private:

    PieceType type;
    Color color;
    std::string represent;
    int piece_number; // !CONST which piece is this pawn 0 - 7 , other 0-1 , queen king 0

    public:

    Piece(const Piece& other){
        this->type = other.type;
        this->color = other.color;
        this->represent = other.represent;
        this->piece_number = other.piece_number;
    }

    Piece(PieceType type_,Color color_=Color::none,int piece_number_=-1): type(type_), color(color_), piece_number(piece_number_) {
        if(type == PieceType::empty) represent = " o ";
        else represent = ((color == Color::white) ? "w" : "b" ) + representList[static_cast<int>(type)];    
    }

    std::string get_represent() const{
        return this->represent;
    }

    PieceType get_piece_type() const{
        return this->type;
    }
    
    Color get_color() const{
        return this->color;
    }

    int get_piece_number() const{
        return this->piece_number;
    }

    void print_piece_info() const{
        std::cout << this->type << std::endl;
        std::cout << this->color << std::endl;
        std::cout << this->represent << std::endl;
    }
};


