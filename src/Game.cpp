#include "../include/Game.h"


void Game::init_game_board_and_pieces(){
    game_board.resize(board_size,std::vector<Piece>(board_size,Piece(PieceType::empty)));
    black_pieces.resize(6);
    white_pieces.resize(6);
    // piece type empty
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){
            game_board[i][j] = Piece(PieceType::empty,Color::none,-1);
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


bool Game::is_valid_move(const Move move) const{

    // check1
    // moving piece 
    // target piece 
    if(!points_legal_move(move)){
        std::cout << "Invalid Move!\n";
        return false; 
    }

    // check2
    // piece ability to move
    if(!piece_able_to_move(move)){{
        std::cout << "Invalid piece move!\n";
        return false; 
    }}
    // check3 
    // does players king has checked
    if(king_checked_move(move)){
        std::cout << "King is checked!\n";
        return false; 
    }

    return true;
}

bool Game::is_ended() const{
    return false;
}


void Game::apply_move(Move move){
    
    Piece playing_piece = game_board[move.from.first][move.from.second];
    Piece target_piece = game_board[move.to.first][move.to.second];

    // update piece lists !!!
    if(target_piece.get_piece_type() != PieceType::empty){
        if(target_piece.get_color() == Color::white){
            white_pieces[static_cast<int>(target_piece.get_piece_type())][target_piece.get_piece_number()] = {-1,-1}; 
        }else{
            black_pieces[static_cast<int>(target_piece.get_piece_type())][target_piece.get_piece_number()] = {-1,-1}; 
        }
    }
    
    if(playing_piece.get_color() == Color::white){
        white_pieces[static_cast<int>(playing_piece.get_piece_type())][playing_piece.get_piece_number()] = {move.to.first,move.to.second}; 
    }else{
        black_pieces[static_cast<int>(playing_piece.get_piece_type())][playing_piece.get_piece_number()] = {move.to.first,move.to.second}; 
    }
    
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
    std::cout << "Player : " << ((game_round%2)?"white ":"black " ) << 
                    "| Round : " << (game_round+1)/2 << std::endl;

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

bool Game::points_legal_move(const Move move) const{
    Piece playing_piece = game_board[move.from.first][move.from.second];
    Piece target_piece = game_board[move.to.first][move.to.second];
    bool player_is_white = (game_round%2==1);

    if(playing_piece.get_piece_type() == PieceType::empty) return false;
    if(playing_piece.get_color() != (player_is_white ? Color::white : Color::black ))  return false;
    if(target_piece.get_color() == (player_is_white ? Color::white : Color::black ))  return false;

    return true;
}

bool Game::piece_able_to_move(const Move move) const{

    Piece playing_piece = game_board[move.from.first][move.from.second];
    Piece target_piece = game_board[move.to.first][move.to.second];
    const bool player_is_white = (game_round%2==1);
    const Color opponent_color = player_is_white ? Color::black : Color::white;

    const int di = move.to.first - move.from.first; 
    const int dj = move.to.second - move.from.second; 
    
    switch (playing_piece.get_piece_type())
    {
    case PieceType::pawn :
    {
        if(player_is_white){
            if(abs(dj) > 1) return false;
            else if(abs(dj) == 1){ // pawn attack
                if(target_piece.get_color() != opponent_color) return false;
            }
            else{
                if(move.from.first == board_size-2 ){
                    if(di == -1){
                        if(target_piece.get_piece_type() != PieceType::empty) return false;
                    }else if(di == -2){
                        if(target_piece.get_piece_type() != PieceType::empty) return false;
                        else if(game_board[move.from.first-1][move.from.second].get_piece_type() != PieceType::empty) return false;
                    }else return false;
                }else{
                    if(di != -1) return false;
                    if(target_piece.get_piece_type() != PieceType::empty) return false;
                }
            }

        }else{
            if(abs(dj) > 1) return false;
            else if(abs(dj) == 1){ // pawn attack
                if(target_piece.get_color() != opponent_color) return false;
            }
            else{
                if(move.from.first == 1 ){
                    if(di == 1){
                        if(target_piece.get_piece_type() != PieceType::empty) return false;
                    }else if(di == 2){
                        if(target_piece.get_piece_type() != PieceType::empty) return false;
                        else if(game_board[move.from.first+1][move.from.second].get_piece_type() != PieceType::empty) return false;
                    }else return false;
                }else{
                    if(di != 1) return false;
                    if(target_piece.get_piece_type() != PieceType::empty) return false;
                }
            }

        }
        break;
    }
        
    case PieceType::rook :
    {
        
        if(di && dj) return false;
        if(di){
            int slope = di/(abs(di));
            for(int i=move.from.first+slope;i!=move.to.first;i+=slope){
                if(game_board[i][move.from.second].get_piece_type() != PieceType::empty) return false;
            }
        }else if(dj){
            int slope = dj/(abs(dj));
            for(int j=move.from.second+slope;j!=move.to.second;j+=slope){
                if(game_board[move.from.first][j].get_piece_type() != PieceType::empty) return false;
            }
        }
        break;
    }
        
    case PieceType::horse :
    {
        if(di*di + dj*dj != 5) return false; 
        break;
    }

        
    case PieceType::bishop :
    {
        if(dj==0 || abs(di/dj) != 1) return false;
        int sl_row = di/abs(di);
        int sl_col = dj/abs(dj);
        for(int c_i=move.from.first+sl_row,c_j=move.from.second+sl_col;
            c_i!=move.to.first;
            c_i+=sl_row,c_j+=sl_col)
        {
            if(game_board[c_i][c_j].get_piece_type() != PieceType::empty) return false;
        }
        break;
    }   
            
    case PieceType::queen :
    {
        if(di && dj){ // diagonel
            if(dj==0 || abs(di/dj) != 1) return false;
            int sl_row = di/abs(di);
            int sl_col = dj/abs(dj);
            for(int c_i=move.from.first+sl_row,c_j=move.from.second+sl_col;
                c_i!=move.to.first;
                c_i+=sl_row,c_j+=sl_col)
            {
                if(game_board[c_i][c_j].get_piece_type() != PieceType::empty) return false;
            }
        }
        else{ // horizontal
            if(di){
            int slope = di/(abs(di));
            for(int i=move.from.first+slope;i!=move.to.first;i+=slope){
                if(game_board[i][move.from.second].get_piece_type() != PieceType::empty) return false;
            }
            }else if(dj){
                int slope = dj/(abs(dj));
                for(int j=move.from.second+slope;j!=move.to.second;j+=slope){
                    if(game_board[move.from.first][j].get_piece_type() != PieceType::empty) return false;
                }
            }
        }
        
        
        break;
    }
        
    case PieceType::king :
    {
        if( !(abs(di)+abs(dj) == 1 || (abs(di)==1 && abs(dj)==1)) ) return false;
        break;
    }
        
    default:
    {
        throw std::runtime_error("Unexpected type");
        break;
    }
    }//switch ends

    return true;
}

bool Game::king_checked_move(const Move move) const{

    // we apply the move to copied game board(not copy of pieces yet ?? );
    // ! didnt applied to original 
    std::vector<std::vector<Piece>> copy_game_board = game_board;
    copy_game_board[move.to.first][move.to.second] = game_board[move.from.first][move.from.second];
    copy_game_board[move.from.first][move.from.second] = Piece(PieceType::empty);
    
    const bool player_white = game_round%2==1;
    const Color player_color = player_white ? Color::white : Color::black;
    const Color opponent_color = player_white ? Color::black : Color::white;

    // we detect the players kings location
    std::pair<int,int> king_pos;
    std::pair<int,int> threat_pos;
    if(game_board[move.from.first][move.from.second].get_piece_type() == PieceType::king){
        king_pos = {move.to.first,move.to.second};
    }else{
        king_pos = player_white ? (white_pieces[static_cast<int>(PieceType::king)][0]) : (black_pieces[static_cast<int>(PieceType::king)][0]) ;  
    }
    std::cout << (player_white ? "white king pos: " : "black king pos: " ) << king_pos.first << "," << king_pos.second << "\n";
    
    // think like king as a super piece and make all moves 
    


    // threat of pawn
    int pawn_dir = player_white ? -1 : 1 ;
    threat_pos = {king_pos.first+pawn_dir,king_pos.second+1};
    if(in_range(threat_pos) && copy_game_board[threat_pos.first][threat_pos.second].get_piece_type() == PieceType::pawn && copy_game_board[threat_pos.first][threat_pos.second].get_color() == opponent_color) return true;
    threat_pos = {king_pos.first+pawn_dir,king_pos.second-1};
    if(in_range(threat_pos) && copy_game_board[threat_pos.first][threat_pos.second].get_piece_type() == PieceType::pawn && copy_game_board[threat_pos.first][threat_pos.second].get_color() == opponent_color) return true;

    // threat of other king
    std::vector<int> ways = {-1,0,1};
    for(int a:ways){
        for(int b:ways){
            if(!a && !b) continue;
            threat_pos = {king_pos.first+a,king_pos.second+b};
            if(in_range(threat_pos) && copy_game_board[threat_pos.first][threat_pos.second].get_piece_type() == PieceType::king) return true;
        }
    }
    
    
    // threat of horse 
    std::vector<int> l1 = {-1,1};
    std::vector<int> l2 = {-2,2};
    for(int a:l1){
        for(int b:l2){
            threat_pos = {king_pos.first+a,king_pos.second+b};
            if(in_range(threat_pos) && copy_game_board[threat_pos.first][threat_pos.second].get_piece_type() == PieceType::horse && copy_game_board[threat_pos.first][threat_pos.second].get_color() == opponent_color) return true;
            
            threat_pos = {king_pos.first+b,king_pos.second+a};
            if(in_range(threat_pos) && copy_game_board[threat_pos.first][threat_pos.second].get_piece_type() == PieceType::horse && copy_game_board[threat_pos.first][threat_pos.second].get_color() == opponent_color) return true;
        }
    }
    
    
    // threat of horizontal or vert rook or queen
    for(int slope:{-1,1}){
        for(int dj=slope;true;dj+=slope){
            threat_pos = {king_pos.first,king_pos.second+dj};
            if(!in_range(threat_pos)) break;
            Piece current_piece = copy_game_board[threat_pos.first][threat_pos.second];
    
            if(current_piece.get_piece_type() == PieceType::empty) continue;
            else if(current_piece.get_color() == player_color) break;
            else if(current_piece.get_piece_type() == PieceType::rook || current_piece.get_piece_type() == PieceType::queen) return true;
            else break;
        }
    }
    for(int slope:{-1,1}){
        for(int di=slope;true;di+=slope){
            threat_pos = {king_pos.first+di,king_pos.second};
            if(!in_range(threat_pos)) break;
            Piece current_piece = copy_game_board[threat_pos.first][threat_pos.second];
            
            if(current_piece.get_piece_type() == PieceType::empty) continue;
            else if(current_piece.get_color() == player_color) break;
            else if(current_piece.get_piece_type() == PieceType::rook || current_piece.get_piece_type() == PieceType::queen) return true;
            else break;
        }
    }
    // threat of diagonal bishop or queen
    for(int si:{-1,+1}){
        for(int sj:{-1,+1}){
            int di = si,dj=sj;
            while(true){
                threat_pos = {king_pos.first+di,king_pos.second+dj};
                di+=si;
                dj+=sj;
                if(!in_range(threat_pos)) break;
                Piece current_piece = copy_game_board[threat_pos.first][threat_pos.second];
                if(current_piece.get_piece_type() == PieceType::empty) continue;
                else if(current_piece.get_color() == player_color) break;
                else if(current_piece.get_piece_type() == PieceType::bishop || current_piece.get_piece_type() == PieceType::queen) return true;
                else break;
            }
        }
    }
    

    return false;
}

bool Game::in_range(const std::pair<int,int>& position) const{
    return( (position.first >= 0 && position.first < board_size) && (position.second >= 0 && position.second < board_size));
}