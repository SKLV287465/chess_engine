#include "Board.hpp"
#include <vector>
#include <constants.hpp>
// *** Assumes all flags are correctly updated ***

void set_pm_positions(U64 origin, U64 dest, Board& nb) {
    for (int i = 0; i < 8; ++i) {
        if (origin & FILES[i]) {
            nb.set_pm_op_f(i);
        }
        if (origin & RANKS[i]) {
            nb.set_pm_op_r(i);
        }
        if (dest & FILES[i]) {
            nb.set_pm_np_f(i);
        }
        if (dest & RANKS[i]) {
            nb.set_pm_np_r(i);
        }
    }
}

/**
 * creates a new board where a standard move is implemented
 */
inline Board do_move(U64 origin, U64 dest, int piece_type, Board& old_board) {
    auto nb = old_board;
    set_pm_positions(origin, dest, nb);
    nb.bitboards[piece_type] ^= (origin | dest);
    return nb;
}

/**
 * creates a new board where an attack move is implemented
 */
inline Board do_attack(U64 origin, U64 dest, int piece_type, Board& old_board) {
    auto nb = old_board;
    set_pm_positions(origin, dest, nb);
    nb.bitboards[piece_type] ^= (origin | dest);
    int s = 0;
    if (piece_type < 6) s = 6;
    for (int i = s; i < s + 6; ++i) {
        if (nb.bitboards[i] & dest) {
            nb.bitboards[i] ^= dest;
            break;
        }
    }
    return nb;
}

inline bool wlcastle(Board& board, U64 occupied) {
    if (board.wking_in_check() || !board.can_wlcastle() || occupied & RANK_1 & (FILE_B | FILE_C | FILE_D)) return false;
    return true;
}

inline bool wrcastle(Board& board, U64 occupied) {
    if (board.wking_in_check() || !board.can_wrcastle() || occupied & RANK_1 & (FILE_F | FILE_G)) return false;
    return true;
}

void white_special_moves(Board& board, std::vector<Board>& moves, U64 occupied) {
    // implement castling
    if (wlcastle(board, occupied)) {
        auto castlel = do_move(RANK_1 & FILE_E, RANK_1 & FILE_C, white_king, board);
        castlel.bitboards[white_rook] ^= (RANK_1 & (FILE_A | FILE_D)); 
        moves.push_back(castlel);
    }
    if (wrcastle(board, occupied)) {
        auto castler = do_move(RANK_1 & FILE_E, RANK_1 & FILE_G, white_king, board);
        castler.bitboards[white_rook] ^= (RANK_1 & (FILE_H | FILE_F));
        moves.push_back(castler);
    }
    // implement en passant
    if (board.pm_op_r() == RANK_7 && board.pm_np_r() == RANK_5) {
        // right attack
        if (board.wpawns() & RANK_5 & (board.pm_np_f() << 1) & ~FILE_H) {
            auto renpassant = board;
            renpassant.bitboards[0] ^= ((board.wpawns() & RANK_5 & (board.pm_np_f() << 1) & ~FILE_H) | (board.pm_np_f() & RANK_6));
            renpassant.bitboards[6] ^= (board.pm_np_f() & board.pm_np_r());
            set_pm_positions((board.wpawns() & RANK_5 & (board.pm_np_f() << 1) & ~FILE_H), (board.pm_np_f() & RANK_6), renpassant);
            moves.push_back(renpassant);
        }
        // left attack
        if (board.wpawns() & RANK_5 & (board.pm_np_f() >> 1) & ~FILE_A) {
            auto lenpassant = board;
            lenpassant.bitboards[0] ^= ((board.wpawns() & RANK_5 & (board.pm_np_f() >> 1) & ~FILE_A) | (board.pm_np_f() & RANK_6));
            lenpassant.bitboards[6] ^= (board.pm_np_f() & board.pm_np_r());
            set_pm_positions((board.wpawns() & RANK_5 & (board.pm_np_f() >> 1) & ~FILE_A), (board.pm_np_f() & RANK_6), lenpassant);
            moves.push_back(lenpassant);
        }
    }
}

void white_pawn_moves(Board& board, std::vector<Board>& moves) {
    U64 double_push = (board.wpawns() << 16) & RANK_4;
    while (double_push) {
        U64 dest = double_push & -double_push;
        moves.push_back(do_move(dest >> 16, dest, white_pawn, board));
        double_push ^= dest;
    }
    U64 single_push = board.wpawns() << 8;
    while (single_push) {
        U64 dest = single_push & -single_push;
        if (dest & RANK_8) {
            auto queen_promo = board;
            queen_promo.bitboards[0] ^= dest >> 8;
            auto knight_promo = queen_promo;
            queen_promo.bitboards[4] |= dest;
            knight_promo.bitboards[1] |= dest;
            moves.push_back(queen_promo);
            moves.push_back(knight_promo);
        } else {
            moves.push_back(do_move(dest >> 8, dest, white_pawn, board));
        }
        single_push ^= dest;
    }
    U64 left_attack = (board.wpawns() << 9) & ~ FILE_H;
    while (left_attack) {
        U64 dest = single_push & -single_push;
        if (dest & RANK_8) {
            auto queen_promo = board;
            queen_promo.bitboards[0] ^= dest >> 9;
            auto knight_promo = queen_promo;
            queen_promo.bitboards[4] |= dest;
            knight_promo.bitboards[1] |= dest;
            moves.push_back(queen_promo);
            moves.push_back(knight_promo);
        } else {
            moves.push_back(do_attack(dest >> 9, dest, white_pawn, board));
        }
        left_attack ^= dest;
    }
    U64 right_attack = (board.wpawns() << 7) & ~ FILE_H;
    while (right_attack) {
        U64 dest = single_push & -single_push;
        if (dest & RANK_8) {
            auto queen_promo = board;
            queen_promo.bitboards[0] ^= dest >> 7;
            auto knight_promo = queen_promo;
            queen_promo.bitboards[4] |= dest;
            knight_promo.bitboards[1] |= dest;
            moves.push_back(queen_promo);
            moves.push_back(knight_promo);
        } else {
            moves.push_back(do_attack(dest >> 7, dest, white_pawn, board));
        }
        right_attack ^= dest;
    }
}

void process_moves(Board& board, std::vector<Board>& moves, U64 destinations, U64 origin, uint8_t piece_type, U64 opoccupied) {
    switch (piece_type)
    {
    case white_king:
        board.disable_wlcastle();
        board.disable_wrcastle();
        break;
    
    case black_king:
        board.disable_blcastle();
        board.disable_brcastle();
        break;
    case white_rook:
        if ((board.wrooks() & -board.wrooks()) == origin) {
            board.disable_wrcastle();
        } else {
            board.disable_wlcastle();
        }
        break;
    case black_rook:
        if ((board.brooks() & -board.brooks()) == origin) {
            board.disable_blcastle();
        } else {
            board.disable_brcastle();
        }
        break;
    }
    while (destinations) {
        U64 dest = destinations & -destinations;
        if (dest & opoccupied) {
            moves.push_back(do_attack(origin, dest, piece_type, board));
        } else {
            moves.push_back(do_move(origin, dest, piece_type, board));
        }
        destinations ^= dest;
    }
}

U64 get_sliding_moves(U64 ptr, int direction, U64 froccupied, U64 opoccupied) {
    U64 destinations = 0;
    switch (direction)
    {
    case NW:
        while ((ptr << 9) & ~FILE_H) {
            if (ptr & froccupied) break;
            destinations |= ptr;
            if (ptr & opoccupied) break;
        }
        break;
    case W:
        while ((ptr << 1) & ~FILE_H) {
            if (ptr & froccupied) break;
            destinations |= ptr;
            if (ptr & opoccupied) break;
        }
        break;
    case SW:
        while ((ptr >> 7) & ~FILE_H) {
            if (ptr & froccupied) break;
            destinations |= ptr;
            if (ptr & opoccupied) break;
        }
        break;
    case NE:
        while ((ptr << 7) & ~FILE_A) {
            if (ptr & froccupied) break;
            destinations |= ptr;
            if (ptr & opoccupied) break;
        }
        break;
    case E:
        while ((ptr >> 1) & ~FILE_A) {
            if (ptr & froccupied) break;
            destinations |= ptr;
            if (ptr & opoccupied) break;
        }
        break;
    case SE:
        while ((ptr >> 9) & ~FILE_A) {
            if (ptr & froccupied) break;
            destinations |= ptr;
            if (ptr & opoccupied) break;
        }
        break;
    case N:
        while ((ptr << 8)) {
            if (ptr & froccupied) break;
            destinations |= ptr;
            if (ptr & opoccupied) break;
        }
        break;
    case S:
        while ((ptr >> 8)) {
            if (ptr & froccupied) break;
            destinations |= ptr;
            if (ptr & opoccupied) break;
        }
        break;
    
    }
    return destinations;
}

/**
 * generate all pseudo-legal board states after a white move
 */
// TODO TODO -> set previous move for each move made
std::vector<Board> Board::generate_wmoves() {
    // preprocessing
    U64 woccupied = 0;
    U64 boccupied = 0;
    U64 occupied = 0;
    for (int i = 0; i < 6; ++i) {
        woccupied |= bitboards[i];
    }
    for (int i = 6; i < 12; ++i) {
        boccupied |= bitboards[i];
    }
    occupied = boccupied | woccupied;
    auto moves = std::vector<Board>{};
    white_special_moves(*this, moves, occupied);
    white_pawn_moves(*this, moves);
    // knight
    U64 knights = wknights();
    while(knights) {
        U64 knight = knights & -knights;
        U64 l1 = (knight >> 1) & ~FILE_H;
        U64 l2 = (knight >> 2) & ~(FILE_H | (FILE_H >> 1));
        U64 r1 = (knight << 1) & ~FILE_A;
        U64 r2 = (knight << 2) & ~(FILE_A | (FILE_A << 1));
        U64 destinations = ((l1 << 16) | (l1 >> 16) | (r1 << 16) | (r1 >> 16) | (l2 <<  8) | (l2 >>  8) | (r2 <<  8) | (r2 >>  8)) & ~woccupied;
        process_moves(*this, moves, destinations, knight, white_knight, boccupied);
        knights ^= knight;
    }
    // king
    U64 king = wking();
    U64 destinations = 0;
    destinations |= (king & ~FILE_A) >> 1;
    destinations |= (king & ~FILE_H) << 1;
    destinations |= king << 8;
    destinations |= king >> 8;
    destinations |= (king & ~FILE_A) << 7;  // Northwest
    destinations |= (king & ~FILE_H) << 9;  // Northeast
    destinations |= (king & ~FILE_A) >> 9;  // Southwest
    destinations |= (king & ~FILE_H) >> 7;  // Southeast
    process_moves(*this, moves, destinations, king, white_king, boccupied);
    // bishop
    U64 bishops = wbishops();
    while (bishops) {
        U64 bishop = bishops & -bishop;
        U64 destinations = 0;
        // NW
        destinations |= get_sliding_moves(bishop, NW, woccupied, boccupied);
        destinations |= get_sliding_moves(bishop, NE, woccupied, boccupied);
        destinations |= get_sliding_moves(bishop, SW, woccupied, boccupied);
        destinations |= get_sliding_moves(bishop, SE, woccupied, boccupied);
        process_moves(*this, moves, destinations, bishop, white_bishop, boccupied);
        bishops ^= bishop;
    }
    // rook
    U64 rooks = wrooks();
    while (rooks) {
        U64 rook = rooks & -rooks;
        U64 destinations = 0;
        destinations |= get_sliding_moves(rook, N, woccupied, boccupied);
        destinations |= get_sliding_moves(rook, E, woccupied, boccupied);
        destinations |= get_sliding_moves(rook, W, woccupied, boccupied);
        destinations |= get_sliding_moves(rook, S, woccupied, boccupied);
        process_moves(*this, moves, destinations, rook, white_rook, boccupied);
        rooks ^= rook;
    }
    // queen
    U64 queens = wqueens();
    while (queens) {
        U64 queen = queens & -queens;
        U64 destinations = 0;
        destinations |= get_sliding_moves(queen, N, woccupied, boccupied);
        destinations |= get_sliding_moves(queen, E, woccupied, boccupied);
        destinations |= get_sliding_moves(queen, W, woccupied, boccupied);
        destinations |= get_sliding_moves(queen, S, woccupied, boccupied);
        destinations |= get_sliding_moves(queen, NE, woccupied, boccupied);
        destinations |= get_sliding_moves(queen, NW, woccupied, boccupied);
        destinations |= get_sliding_moves(queen, SE, woccupied, boccupied);
        destinations |= get_sliding_moves(queen, SW, woccupied, boccupied);
        process_moves(*this, moves, destinations, queen, white_queen, boccupied);
        queens ^= queen;
    }
}

std::vector<Board> Board::generate_bmoves() {
    
}