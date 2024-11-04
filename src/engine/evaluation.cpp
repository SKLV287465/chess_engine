#include "Board.hpp"
#include "evaluation.hpp"

double Board::evaluate_advantage(Board& board) {
    if (board.get_turn()) {
        int black_advantage = 0;
        for (int i = 0; i < 6; ++i) {
            black_advantage -= piece_values[i] * __builtin_popcountll(board.bitboards[i]);
        }
        for (int i = 6; i < 12; ++i) {
            black_advantage += piece_values[i - 6] * __builtin_popcountll(board.bitboards[i]);
        }
        return black_advantage;
    } else {
        int white_advantage = 0;
        for (int i = 0; i < 6; ++i) {
            white_advantage += piece_values[i] * __builtin_popcountll(board.bitboards[i]);
        }
        for (int i = 6; i < 12; ++i) {
            white_advantage -= piece_values[i - 6] * __builtin_popcountll(board.bitboards[i]);
        }
        return white_advantage;
    }
}