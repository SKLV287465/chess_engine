#include <array>
#include "Board.hpp"

std::array<int, 6> piece_values = {
    100,
    300,
    325,
    500,
    900,
    400
};

/**
 * evaluates the advantage white has over black.
 * - this is an overly simplified version of this. Need to add tables
 */
int evaluate_advantage(Board& board) {
    int white_advantage = 0;
    for (int i = 0; i < 6; ++i) {
        white_advantage += piece_values[i] * __builtin_popcountll(board.bitboards[i]);
    }
    for (int i = 6; i < 12; ++i) {
        white_advantage -= piece_values[i - 6] * __builtin_popcountll(board.bitboards[i]);
    }
    return white_advantage;
}
