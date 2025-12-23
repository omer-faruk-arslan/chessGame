#include "../include/Game.h"


void Game::init_game_board_and_pieces(){
    game_board.resize(board_size,std::vector<Piece>(board_size));
    black_pieces.resize(6);
    white_pieces.resize(6);
    // piece type empty
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){
            game_board[i][j] = Piece(PieceType::empty,Color::black,-1);
        }
    }

    // pawns 
    for(int j=0;j<board_size;j++){
        game_board[1][j] = Piece(PieceType::pawn,Color::black,j);
        black_pieces[static_cast<int>(PieceType::pawn)].push_back({1,j});
    }
    for(int j=0;j<board_size;j++){
        game_board[6][j] = Piece(PieceType::pawn,Color::white,j);
        white_pieces[static_cast<int>(PieceType::pawn)].push_back({6,j});
    }
    
    // rook
    game_board[0][0] = Piece(PieceType::rook,Color::black,0);
    game_board[0][7] = Piece(PieceType::rook,Color::black,1);
    black_pieces[static_cast<int>(PieceType::rook)].push_back({0,0});
    black_pieces[static_cast<int>(PieceType::rook)].push_back({0,7});

    game_board[7][0] = Piece(PieceType::rook,Color::white,0);
    game_board[7][7] = Piece(PieceType::rook,Color::white,1);
    white_pieces[static_cast<int>(PieceType::rook)].push_back({7,0});
    white_pieces[static_cast<int>(PieceType::rook)].push_back({7,7});
    
    //horse
    game_board[0][1] = Piece(PieceType::horse,Color::black,0);
    game_board[0][6] = Piece(PieceType::horse,Color::black,1);
    black_pieces[static_cast<int>(PieceType::horse)].push_back({0,1});
    black_pieces[static_cast<int>(PieceType::horse)].push_back({0,6});

    game_board[7][1] = Piece(PieceType::horse,Color::white,0);
    game_board[7][6] = Piece(PieceType::horse,Color::white,1);
    white_pieces[static_cast<int>(PieceType::horse)].push_back({7,1});
    white_pieces[static_cast<int>(PieceType::horse)].push_back({7,6});
    
    //bishop
    game_board[0][2] = Piece(PieceType::bishop,Color::black,0);
    game_board[0][5] = Piece(PieceType::bishop,Color::black,1);
    black_pieces[static_cast<int>(PieceType::bishop)].push_back({0,2});
    black_pieces[static_cast<int>(PieceType::bishop)].push_back({0,5});

    game_board[7][2] = Piece(PieceType::bishop,Color::white,0);
    game_board[7][5] = Piece(PieceType::bishop,Color::white,1);
    white_pieces[static_cast<int>(PieceType::bishop)].push_back({7,2});
    white_pieces[static_cast<int>(PieceType::bishop)].push_back({7,5});
    
    // queen
    game_board[0][3] = Piece(PieceType::queen,Color::black,0);
    black_pieces[static_cast<int>(PieceType::queen)].push_back({0,3});

    game_board[7][3] = Piece(PieceType::queen,Color::white,0);
    white_pieces[static_cast<int>(PieceType::queen)].push_back({7,3});

    // king
    game_board[0][4] = Piece(PieceType::king,Color::black,0);
    black_pieces[static_cast<int>(PieceType::king)].push_back({0,4});

    game_board[7][4] = Piece(PieceType::king,Color::white,0);
    white_pieces[static_cast<int>(PieceType::king)].push_back({7,4});

}

Game::Game(){
    game_round = 0;
    game_state = true;
    winner = -1;
    init_game_board_and_pieces();
}


bool Game::is_valid_move(Move move) const{
    return true;
}

bool Game::is_ended() const{
    return false;
}


void Game::apply_move(Move move){
    game_board[move.to.first][move.to.second] = game_board[move.from.first][move.from.second];
    game_board[move.from.first][move.from.second] = Piece(PieceType::empty);
}

void Game::update_round(){
    this->game_round++;
}

void Game::print_board() const{
    std::cout << "-------Game Board-------" << std::endl;
    std::cout << "  " ;
    for(int i=0;i<board_size;i++){
        std::cout << " " << char('a'+i) << "  "; 
    }std::cout << std::endl;
    for(int i=0;i<board_size;i++){
        std::cout << board_size-i << " " ;
        for(int j=0;j<board_size;j++){
            std::cout  << game_board[i][j].get_represent() << " " ;
        }std::cout << std::endl;
    }

}

bool Game::get_game_state() const{
    return this->game_state;
}

std::vector<std::vector<Piece>> Game::get_game_board() const{
    return game_board;
}

int Game::get_game_round() const{
    return this->game_round;
}