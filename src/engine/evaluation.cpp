#include "Board.hpp"
#include "evaluation.hpp"
#include <limits>
#include "evaluation_tables.hpp"

int calculate_distance_from_corners(uint64_t bitboard) {
    int pos = __builtin_ffsll(bitboard) - 1;
    if (pos < 0) return -1;
    int rank = pos / 8;
    int file = pos % 8;
    std::array<std::pair<int, int>, 4> corners = {
        std::make_pair(0, 0),
        std::make_pair(0, 7),
        std::make_pair(7, 0),
        std::make_pair(7, 7)
    };

    // Calculate Manhattan distance to each corner
    int totalDistance = 0;
    for (const auto& corner : corners) {
        int cornerRank = corner.first;
        int cornerFile = corner.second;
        totalDistance += std::abs(rank - cornerRank) + std::abs(file - cornerFile);
    }

    return totalDistance;
}

double Board::evaluate_advantage(Board& board, int wpieces, int bpieces) {
    int gamestate = 0;
    if (board.get_turn()) {
        if (!board.bking()) return -std::numeric_limits<double>::infinity();
        if (!board.wking()) return std::numeric_limits<double>::infinity();
        if (wpieces < 8) gamestate = 1;
        int black_advantage = 0;
        for (int i = 0; i < 6; ++i) {
            U64 piece_positions = board.bitboards[i];
            while (piece_positions) {
                U64 location = piece_positions & -piece_positions;
                black_advantage -= piece_values[i];
                auto positional_advantage = AllPSQT[0][gamestate][i][__builtin_ctzll(location)];
                black_advantage -= positional_advantage;
                piece_positions ^= -location;
            }
        }
        for (int i = 6; i < 12; ++i) {
            U64 piece_positions = board.bitboards[i];
            while (piece_positions) {
                U64 location = piece_positions & -piece_positions;
                black_advantage += piece_values[i - 6];
                auto positional_advantage = AllPSQT[1][gamestate][i - 6][__builtin_ctzll(location)];
                black_advantage += positional_advantage;
                piece_positions ^= -location;
            }
        }
        if (wpieces < 5) {
            black_advantage += 100;
            black_advantage -= calculate_distance_from_corners(board.wking());
        }
        return black_advantage;
    } else {
        if (!board.wking()) return -std::numeric_limits<double>::infinity();
        if (!board.bking()) return std::numeric_limits<double>::infinity();
        if (bpieces < 8) gamestate = 1;
        int white_advantage = 0;
        for (int i = 0; i < 6; ++i) {
            U64 piece_positions = board.bitboards[i];
            while (piece_positions) {
                U64 location = piece_positions & -piece_positions;
                white_advantage += piece_values[i];
                auto positional_advantage = AllPSQT[0][gamestate][i][__builtin_ctzll(location)];
                white_advantage += positional_advantage;
                piece_positions ^= -location;
            }
        }
        for (int i = 6; i < 12; ++i) {
            U64 piece_positions = board.bitboards[i];
            while (piece_positions) {
                U64 location = piece_positions & -piece_positions;
                white_advantage -= piece_values[i - 6];
                auto positional_advantage = AllPSQT[1][gamestate][i][__builtin_ctzll(location)];
                white_advantage -= positional_advantage;
                piece_positions ^= -location;
            }
        }
        if (bpieces < 5) {
            white_advantage += 100;
            white_advantage -= calculate_distance_from_corners(board.bking());
        }
        return white_advantage;
    }
}

// double Board::evaluate_advantage(Board& board) {
//     if (board.get_turn()) {
//         int black_advantage = 0;
//         for (int i = 0; i < 6; ++i) {
//             black_advantage -= piece_values[i] * __builtin_popcountll(board.bitboards[i]);
//         }
//         for (int i = 6; i < 12; ++i) {
//             black_advantage += piece_values[i - 6] * __builtin_popcountll(board.bitboards[i]);
//         }
//         return black_advantage;
//     } else {
//         int white_advantage = 0;
//         for (int i = 0; i < 6; ++i) {
//             white_advantage += piece_values[i] * __builtin_popcountll(board.bitboards[i]);
//         }
//         for (int i = 6; i < 12; ++i) {
//             white_advantage -= piece_values[i - 6] * __builtin_popcountll(board.bitboards[i]);
//         }
//         return white_advantage;
//     }
// }