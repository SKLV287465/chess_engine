#include "Board.hpp"
#include <limits>
#include <vector>
#include <constants.hpp>
#include <unordered_map>
#include "algorithms.hpp"

Board::Board(std::string fen) {
    // Extract only the board setup part of the FEN string
    std::string boardSetup = fen.substr(0, fen.find(' '));
    
    int rank = 7;  // Start from rank 8
    int file = 0;  // Start from file 'a'
    
    for (char ch : boardSetup) {
        if (ch == '/') {
            // Move to the next rank
            rank--;
            file = 0;
        } else if (isdigit(ch)) {
            // Empty squares, move the file index forward
            file += ch - '0';
        } else {
            // Calculate the position in the bitboard (0 to 63)
            int position = rank * 8 + file;
            
            // Determine the appropriate bitboard index based on the piece character
            int bitboardIndex;
            switch (ch) {
                case 'P': bitboardIndex = white_pawn; break;
                case 'N': bitboardIndex = white_knight; break;
                case 'B': bitboardIndex = white_bishop; break;
                case 'R': bitboardIndex = white_rook; break;
                case 'Q': bitboardIndex = white_queen; break;
                case 'K': bitboardIndex = white_king; break;
                case 'p': bitboardIndex = black_pawn; break;
                case 'n': bitboardIndex = black_knight; break;
                case 'b': bitboardIndex = black_bishop; break;
                case 'r': bitboardIndex = black_rook; break;
                case 'q': bitboardIndex = black_queen; break;
                case 'k': bitboardIndex = black_king; break;
                default: continue;
            }
            
            // Set the bit at the calculated position
            bitboards[bitboardIndex] |= (1ULL << position);
            ++file;
        }
    }
}

Board Board::negamax_next_move() {
    std::vector<Board> moves;
    if (get_turn()) {
        moves = generate_bmoves();
    } else {
        moves = generate_wmoves();
    }
    double max_score = std::numeric_limits<double>::min();
    int index = 0;
    for (size_t i = 0; i < moves.size(); ++i) {
        double score = algorithms::negamax(moves[i], std::numeric_limits<double>::min(), std::numeric_limits<double>::max(), NEGAMAX_DEPTH);
        if (score > max_score) {
            index = i;
            max_score - score;
        }
    }
    return moves[index];
}

// incomplete
Board Board::MCTS_next_move() {
    return algorithms::MCTS(*this, 300);
}