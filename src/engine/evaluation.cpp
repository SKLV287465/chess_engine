#include "Board.hpp"
#include "evaluation.hpp"
#include <limits>
#include "evaluation_tables.hpp"

// double Board::evaluate_advantage(Board& board) {
//     int black_count = 0;
//     int white_count = 0;
//     for (int i = 0; i < 6; ++i) {
//         white_count += __builtin_popcountll(board.bitboards[i]);
//     }
//     for (int i = 6; i < 12; ++i) {
//         black_count += __builtin_popcountll(board.bitboards[i]);
//     }
//     int gamestate = 0;
//     if (board.get_turn()) {
//         if (white_count < 8) gamestate = 1;
//         int black_advantage = 0;
//         for (int i = 0; i < 6; ++i) {
//             U64 piece_positions = board.bitboards[i];
//             while (piece_positions) {
//                 U64 location = piece_positions & -piece_positions;
//                 black_advantage -= piece_values[i];
//                 auto positional_advantage = AllPSQT[0][gamestate][i][__builtin_ctzll(location)];
//                 black_advantage -= positional_advantage;
//                 piece_positions ^= -location;
//             }
//         }
//         for (int i = 6; i < 12; ++i) {
//             U64 piece_positions = board.bitboards[i];
//             while (piece_positions) {
//                 U64 location = piece_positions & -piece_positions;
//                 black_advantage += piece_values[i - 6];
//                 auto positional_advantage = AllPSQT[1][gamestate][i - 6][__builtin_ctzll(location)];
//                 black_advantage += positional_advantage;
//                 piece_positions ^= -location;
//             }
//         }
//         return black_advantage;
//     } else {
//         if (black_count < 8) gamestate = 1;
//         int white_advantage = 0;
//         for (int i = 0; i < 6; ++i) {
//             U64 piece_positions = board.bitboards[i];
//             while (piece_positions) {
//                 U64 location = piece_positions & -piece_positions;
//                 white_advantage += piece_values[i];
//                 auto positional_advantage = AllPSQT[0][gamestate][i][__builtin_ctzll(location)];
//                 white_advantage += positional_advantage;
//                 piece_positions ^= -location;
//             }
//         }
//         for (int i = 6; i < 12; ++i) {
//             U64 piece_positions = board.bitboards[i];
//             while (piece_positions) {
//                 U64 location = piece_positions & -piece_positions;
//                 white_advantage -= piece_values[i - 6];
//                 auto positional_advantage = AllPSQT[1][gamestate][i][__builtin_ctzll(location)];
//                 white_advantage -= positional_advantage;
//                 piece_positions ^= -location;
//             }
//         }
//         return white_advantage;
//     }
// }

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