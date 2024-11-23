#include "Board.hpp"
#include <limits>
#include <vector>
#include <constants.hpp>
#include <unordered_map>
#include "algorithms.hpp"

Board::Board(std::string fen) {
    bitboards = {0,0,0,0,0,0,0,0,0,0,0,0};
    b_info = 0;
    // Extract only the board setup part of the FEN string
    std::string boardSetup = fen.substr(0, fen.find(' '));
    
    int rank = 7;  // Start from the 8th rank (index 7)
    int file = 0;  // Start from the 'a' file (index 0)

    for (char ch : boardSetup) {
        if (ch == '/') {
            // Move to the next rank
            rank--;
            file = 0;
        } else if (isdigit(ch)) {
            // Skip the specified number of squares
            file += ch - '0';
        } else {
            // Calculate the position in the bitboard (0 to 63)
            int position = rank * 8 + file;

            // Set the bit in the correct bitboard based on the piece character
            switch (ch) {
                case 'P': bitboards[white_pawn] |= (1ULL << position); break;
                case 'N': bitboards[white_knight] |= (1ULL << position); break;
                case 'B': bitboards[white_bishop] |= (1ULL << position); break;
                case 'R': bitboards[white_rook] |= (1ULL << position); break;
                case 'Q': bitboards[white_queen] |= (1ULL << position); break;
                case 'K': bitboards[white_king] |= (1ULL << position); break;
                case 'p': bitboards[black_pawn] |= (1ULL << position); break;
                case 'n': bitboards[black_knight] |= (1ULL << position); break;
                case 'b': bitboards[black_bishop] |= (1ULL << position); break;
                case 'r': bitboards[black_rook] |= (1ULL << position); break;
                case 'q': bitboards[black_queen] |= (1ULL << position); break;
                case 'k': bitboards[black_king] |= (1ULL << position); break;
            }
            // Move to the next file
            ++file;
        }
    }
}


Board Board::negamax_next_move(int wpieces, int bpieces) {
    std::deque<Board> moves;
    if (get_turn()) {
        moves = generate_bmoves_no_stalemate();
        
    } else {
        moves = generate_wmoves_no_stalemate();
    }
    double max_score = -std::numeric_limits<double>::infinity();
    int index = 0;
    auto scores = std::vector<int>{};
    scores.reserve(moves.size());
    #pragma omp parallel for
    for (size_t i = 0; i < moves.size(); ++i) {
        double score = -algorithms::negamax(moves[i], -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), NEGAMAX_DEPTH, wpieces, bpieces);
        scores[i] = score;
    }

    for (auto i = 0; i < scores.size(); ++i) {
        if (scores[i] > max_score) {
            max_score = scores[i];
            index = i;
        }
    }
    std::cout << max_score << std::endl;
    return moves[index];
}

// incomplete
Board Board::MCTS_next_move() {
    return algorithms::MCTS(*this, 1000);
}

void Board::update_check() {
    if (get_turn()) {
        uncheck_wking();
        auto next_turns = generate_wmoves();
        for (auto& m : next_turns) {
            if (!m.bitboards[black_king]) {
                check_bking();
                return;
            }
        }
    } else {
        uncheck_bking();
        auto next_turns = generate_bmoves();
        for (auto& m : next_turns) {
            if (!m.bitboards[white_king]) {
                check_wking();
                return;
            }
        }
    }
    
}