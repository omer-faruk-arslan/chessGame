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

bool Game::points_legal_move(const Move move) const{
    if(!in_range(move.from) || !in_range(move.to)) return false;
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
                if(di != -1) return false;
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
                if(di != 1) return false;
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
        if(abs(di) != abs(dj)) return false;
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
            if(abs(di) != abs(dj)) return false;
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
        if (abs(di) > 1 || abs(dj) > 1) return false;
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


std::pair<int,std::pair<int,int>> Game::king_checked_move(const Move move, bool in_state)
{
    int check_count = 0;
    std::pair<int,int> check_pos;

    const bool player_white = game_round % 2 == 1;
    const Color player_color   = player_white ? Color::white : Color::black;
    const Color opponent_color = player_white ? Color::black : Color::white;

    Piece rewind_from(PieceType::empty);
    Piece rewind_to(PieceType::empty);

    std::pair<int,int> king_pos;
    std::pair<int,int> threat_pos;

    bool rewound = false;

    auto rewind = [&]() {
        if(!rewound && !in_state){
            game_board[move.from.first][move.from.second] = rewind_from;
            game_board[move.to.first][move.to.second] = rewind_to;
            rewound = true;
        }
    };

    // ---- simulate move if needed ----
    if(!in_state){
        rewind_from = game_board[move.from.first][move.from.second];
        rewind_to   = game_board[move.to.first][move.to.second];

        if(rewind_from.get_piece_type() == PieceType::king){
            king_pos = move.to;
        } else {
            king_pos = player_white
                ? white_pieces[static_cast<int>(PieceType::king)][0]
                : black_pieces[static_cast<int>(PieceType::king)][0];
        }

        game_board[move.to.first][move.to.second] = rewind_from;
        game_board[move.from.first][move.from.second] = Piece(PieceType::empty);
    }
    else {
        king_pos = player_white
            ? white_pieces[static_cast<int>(PieceType::king)][0]
            : black_pieces[static_cast<int>(PieceType::king)][0];
    }

    // ---- pawn threats ----
    int pawn_dir = player_white ? -1 : 1;
    for(int i : {-1, +1}){
        threat_pos = {king_pos.first + pawn_dir, king_pos.second + i};
        if(in_range(threat_pos) &&
           game_board[threat_pos.first][threat_pos.second].get_piece_type() == PieceType::pawn &&
           game_board[threat_pos.first][threat_pos.second].get_color() == opponent_color)
        {
            if(++check_count > 1){
                rewind();
                return {2, {}};
            }
            check_pos = threat_pos;
        }
    }

    // ---- king threats ----
    for(int a : {-1,0,1}){
        for(int b : {-1,0,1}){
            if(!a && !b) continue;
            threat_pos = {king_pos.first + a, king_pos.second + b};
            if(in_range(threat_pos) &&
               game_board[threat_pos.first][threat_pos.second].get_piece_type() == PieceType::king)
            {
                if(++check_count > 1){
                    rewind();
                    return {2, {}};
                }
                check_pos = threat_pos;
            }
        }
    }

    // ---- knight threats ----
    for(int a : {-1,1}){
        for(int b : {-2,2}){
            for(auto [di,dj] : std::initializer_list<std::pair<int,int>>{{a,b},{b,a}}){
                threat_pos = {king_pos.first + di, king_pos.second + dj};
                if(in_range(threat_pos) &&
                   game_board[threat_pos.first][threat_pos.second].get_piece_type() == PieceType::horse &&
                   game_board[threat_pos.first][threat_pos.second].get_color() == opponent_color)
                {
                    if(++check_count > 1){
                        rewind();
                        return {2, {}};
                    }
                    check_pos = threat_pos;
                }
            }
        }
    }

    // ---- rook / queen (horizontal & vertical) ----
    for(int slope : {-1, 1}){
        for(int dj = slope; ; dj += slope){
            threat_pos = {king_pos.first, king_pos.second + dj};
            if(!in_range(threat_pos)) break;
            Piece p = game_board[threat_pos.first][threat_pos.second];
            if(p.get_piece_type() == PieceType::empty) continue;
            if(p.get_color() == player_color) break;
            if(p.get_piece_type() == PieceType::rook || p.get_piece_type() == PieceType::queen){
                if(++check_count > 1){
                    rewind();
                    return {2, {}};
                }
                check_pos = threat_pos;
            }
            break;
        }
    }

    for(int slope : {-1, 1}){
        for(int di = slope; ; di += slope){
            threat_pos = {king_pos.first + di, king_pos.second};
            if(!in_range(threat_pos)) break;
            Piece p = game_board[threat_pos.first][threat_pos.second];
            if(p.get_piece_type() == PieceType::empty) continue;
            if(p.get_color() == player_color) break;
            if(p.get_piece_type() == PieceType::rook || p.get_piece_type() == PieceType::queen){
                if(++check_count > 1){
                    rewind();
                    return {2, {}};
                }
                check_pos = threat_pos;
            }
            break;
        }
    }

    // ---- bishop / queen (diagonals) ----
    for(int si : {-1,1}){
        for(int sj : {-1,1}){
            for(int step = 1; ; ++step){
                threat_pos = {king_pos.first + si*step, king_pos.second + sj*step};
                if(!in_range(threat_pos)) break;
                Piece p = game_board[threat_pos.first][threat_pos.second];
                if(p.get_piece_type() == PieceType::empty) continue;
                if(p.get_color() == player_color) break;
                if(p.get_piece_type() == PieceType::bishop || p.get_piece_type() == PieceType::queen){
                    if(++check_count > 1){
                        rewind();
                        return {2, {}};
                    }
                    check_pos = threat_pos;
                }
                break;
            }
        }
    }

    rewind();

    if(check_count == 1) return {1, check_pos};
    return {0, {}};
}


bool Game::in_range(const std::pair<int,int>& position) const{
    return( (position.first >= 0 && position.first < board_size) && (position.second >= 0 && position.second < board_size));
}

bool Game::any_possible_move(){
    bool player_is_white = game_round%2==1;
    const std::vector<std::vector<std::pair<int,int>>>& player_pieces = player_is_white ? white_pieces : black_pieces;
    
    // king 
    std::pair<int,int> current_piece_position; 
    std::pair<int,int> current_target_position; 
    current_piece_position = player_pieces[static_cast<int>(PieceType::king)][0];
    std::vector<int> ways = {-1,0,1};

    for(int a:ways){        
        for(int b:ways){
            if(!a && !b) continue;
            current_target_position = {current_piece_position.first+a,current_piece_position.second+b};
            if(is_valid_move(Move(current_piece_position,current_target_position))) return true;
        }
    }

    // pawns
    for(const std::pair<int,int>& pawn_position: player_pieces[static_cast<int>(PieceType::pawn)]){
        if(pawn_position.first == -1) continue;
        int b = player_is_white ? -1 : 1;
        if(is_valid_move(Move(pawn_position,{pawn_position.first+1*b,pawn_position.second}))) return true;
        if(is_valid_move(Move(pawn_position,{pawn_position.first+2*b,pawn_position.second}))) return true;
        if(is_valid_move(Move(pawn_position,{pawn_position.first+1*b,pawn_position.second+1}))) return true;
        if(is_valid_move(Move(pawn_position,{pawn_position.first+1*b,pawn_position.second-1}))) return true;
    }
    
    // rook
    std::vector<std::pair<int,int>> rook_dirs = {{1,0},{-1,0},{0,1},{0,-1}};
    for(const std::pair<int,int>& rook_position: player_pieces[static_cast<int>(PieceType::rook)]){
        if(rook_position.first == -1) continue;
        for(auto dir:rook_dirs){
            Move move;move.from = rook_position;
            for(int step=1;;step++){
                move.to.first = rook_position.first+step*dir.first;
                move.to.second = rook_position.second+step*dir.second;
                if(!points_legal_move(move) || !piece_able_to_move(move)) break;
                else if(is_valid_move(move)) return true;
            }
        }
    }
    
    // horse 
    for(const std::pair<int,int>& horse_position: player_pieces[static_cast<int>(PieceType::horse)]){
        if(horse_position.first == -1) continue;
        for(int a:{-1,1}){
            for(int b:{-2,2}){
                if(is_valid_move(Move(horse_position,{horse_position.first+a,horse_position.second+b}))) return true;
                if(is_valid_move(Move(horse_position,{horse_position.first+b,horse_position.second+a}))) return true;
            }
        }
    }
    
    // bishop
    std::vector<std::pair<int,int>> bishop_dirs = {{1,1},{1,-1},{-1,1},{-1,-1}};
    for(const std::pair<int,int>& bishop_position: player_pieces[static_cast<int>(PieceType::bishop)]){
        if(bishop_position.first == -1) continue;
        for(auto dir:bishop_dirs){
            Move move;move.from = bishop_position;
            for(int step=1;;step++){
                move.to.first = bishop_position.first+step*dir.first;
                move.to.second = bishop_position.second+step*dir.second;
                if(!points_legal_move(move) || !piece_able_to_move(move)) break;
                else if(is_valid_move(move)) return true;
            }
        }
    }
    
    // queen
    std::vector<std::pair<int,int>> queen_dirs = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
    for(const std::pair<int,int>& queen_position: player_pieces[static_cast<int>(PieceType::queen)]){
        if(queen_position.first == -1) continue;
        for(auto dir:queen_dirs){
            Move move;move.from = queen_position;
            for(int step=1;;step++){
                move.to.first = queen_position.first+step*dir.first;
                move.to.second = queen_position.second+step*dir.second;
                if(!points_legal_move(move) || !piece_able_to_move(move)) break;
                else if(is_valid_move(move)) return true;
            }
        }
    }
    return false;
}

bool Game::is_reachable(const std::pair<int,int>& position){
    bool player_is_white = game_round%2==1;
    const std::vector<std::vector<std::pair<int,int>>>& player_pieces = player_is_white ? white_pieces : black_pieces;
    // exclude king 
    for(size_t i=0;i<player_pieces.size()-1;i++){
        for(auto piece_pos:player_pieces[i]){
            if(piece_pos.first==-1 && piece_pos.second==-1) continue;
            else{
                if(is_valid_move(Move(piece_pos,position))) return true;
            }
        }
    }
    return false;
}

Game::Game(){
    game_round = 1;
    game_state = 0;
    winner = -1;
    init_game_board_and_pieces();
}

bool Game::is_valid_move(const Move move){

    // check1
    // moving piece 
    // target piece 
    if(!points_legal_move(move)){
        return false; 
    }

    // check2
    // piece ability to move
    if(!piece_able_to_move(move)){
        return false; 
    }

    // check3 
    // does players king has checked
    if(king_checked_move(move).first){
        return false; 
    }

    return true;
}

bool Game::is_ended(){

    auto check_info = king_checked_move(Move(),true); // instate check
    if(check_info.first == 0){ // no check , possible stalemate
        if(any_possible_move()) return false;
        else{
            game_state = 3;
            return true;
        }
    }else if(check_info.first == 2){ //  
        // TODO :  double check , king escape
        std::pair<int,int> king_pos = game_round%2==1 ? (white_pieces[static_cast<int>(PieceType::king)][0]) : (black_pieces[static_cast<int>(PieceType::king)][0]);
        std::vector<int> ways = {-1,0,1};
        for(int a:ways){
            for(int b:ways){
                if(!a && !b) continue;
                if(is_valid_move(Move(king_pos,{king_pos.first+a,king_pos.second+b}))) {
                    return false;
                }
            }
        }
        // cur player = w -> b win , visa versa
        game_state = game_state%2==1 ? 2 : 1; 
        return true;
    }else if(check_info.first == 1){
        // TODO : king escape or capture or check block
        std::pair<int,int> king_pos = game_round%2==1 ? (white_pieces[static_cast<int>(PieceType::king)][0]) : (black_pieces[static_cast<int>(PieceType::king)][0]);
        std::vector<int> ways = {-1,0,1};
        for(int a:ways){
            for(int b:ways){
                if(!a && !b) continue;
                if(is_valid_move(Move(king_pos,{king_pos.first+a,king_pos.second+b}))) {
                    return false;
                }
            }
        }

        // know we need to examine checker 
        // single point or line check
        // single point(unblockable) : pawn, horse,  
        // line check(blockable) : rook, bishop, queen  
        Piece checker_piece = game_board[check_info.second.first][check_info.second.second];
        std::pair<int,int> checker_pos = check_info.second;
        if(checker_piece.get_piece_type() == PieceType::pawn 
        || checker_piece.get_piece_type() == PieceType::horse)
        {
            if(is_reachable(check_info.second)) return false;
        }
        else if(checker_piece.get_piece_type() == PieceType::rook
             || checker_piece.get_piece_type() == PieceType::bishop
             || checker_piece.get_piece_type() == PieceType::queen)
        {
            int di = (king_pos.first-checker_pos.first);
            int dj = (king_pos.second-checker_pos.second);
            // we already know that di and dj valid this info came from king check control
            // slopes are diag if bishop , hori,vert if rook , queen both
            int slope_i = di ? di/abs(di) : 0;
            int slope_j = dj ? dj/abs(dj) : 0;
            for(auto cur_pos = checker_pos;cur_pos != king_pos;cur_pos.first+=slope_i,cur_pos.second+=slope_j){
                if(is_reachable(cur_pos)) return false;
            }
        }
        else
        {
            throw std::runtime_error("unexpected piece type for single check mate control");
        }

        game_state = game_round%2==1 ? 2 : 1; 
        return true;
    }else{
        throw std::runtime_error("unexpected state");
    }
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
    if(!game_state)
    std::cout << "Player : " << ((game_round%2)?"white ":"black " ) << 
                    "| Round : " << (game_round+1)/2 << std::endl;

}

void Game::result() const{
    std::cout << "--Game Has Ended--" << std::endl ; 
    if(game_state == 3){
        std::cout << "Result: Stalemate !" << std::endl ; 
    }else{
        std::cout << "Result: " << (game_state == 1 ? "White" : "Black ") << " has won the game !" << std::endl ; 
    }
    print_board();
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




