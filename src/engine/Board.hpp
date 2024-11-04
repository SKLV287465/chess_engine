#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>
#include <constants.hpp>
#include <string>

class Board {
    public:
    Board(std::string fen);
    // get and set pieces
    inline U64 wpawns() const{return bitboards[0];}
	inline U64 wknights() const{return bitboards[1];}
	inline U64 wbishops() const{return bitboards[2];}
	inline U64 wrooks() const{return bitboards[3];}
	inline U64 wqueens() const{return bitboards[4];}
	inline U64 wking() const{return bitboards[5];}
	inline U64 bpawns() const{return bitboards[6];}
	inline U64 bknights() const{return bitboards[7];}
	inline U64 bbishops() const{return bitboards[8];}
	inline U64 brooks() const{return bitboards[9];}
	inline U64 bqueens() const{return bitboards[10];}
	inline U64 bking() const{return bitboards[11];}
    inline void set_wpawns(U64 new_board) {bitboards[0] = new_board;}
	inline void set_wknights(U64 new_board) {bitboards[1] = new_board;}
	inline void set_wbishops(U64 new_board) {bitboards[2] = new_board;}
	inline void set_wrooks(U64 new_board) {bitboards[3] = new_board;}
	inline void set_wqueens(U64 new_board) {bitboards[4] = new_board;}
	inline void set_wking(U64 new_board) {bitboards[5] = new_board;}
	inline void set_bpawns(U64 new_board) {bitboards[6] = new_board;}
	inline void set_bknights(U64 new_board) {bitboards[7] = new_board;}
	inline void set_bbishops(U64 new_board) {bitboards[8] = new_board;}
	inline void set_brooks(U64 new_board) {bitboards[9] = new_board;}
	inline void set_bqueens(U64 new_board) {bitboards[10] = new_board;}
	inline void set_bking(U64 new_board) {bitboards[11] = new_board;}

    // move generation
    std::vector<Board> generate_wmoves();
    std::vector<Board> generate_bmoves();

    // get and set board info
    inline bool wking_in_check() {return (b_info >> 31) & 0b1;};
    inline bool bking_in_check() {return (b_info >> 30) & 0b1;};
    inline void check_wking() {b_info |= static_cast<uint32_t>(1 << 31);};
    inline void uncheck_wking() {b_info &= 0b01111111111111111111111111111111;};
    inline void check_bking() {b_info |= static_cast<uint32_t>(1 << 30);};
    inline void uncheck_bking() {b_info &= 0b10111111111111111111111111111111;};

    inline bool can_wlcastle() {return !((b_info >> 29) & 0b1);};
    inline bool can_wrcastle() {return !((b_info >> 28) & 0b1);};
    inline bool can_blcastle() {return !((b_info >> 27) & 0b1);};
    inline bool can_brcastle() {return !((b_info >> 26) & 0b1);};
    inline void disable_wlcastle() {b_info |= 0b00100000000000000000000000000000;};
    inline void disable_wrcastle() {b_info |= 0b00010000000000000000000000000000;};
    inline void disable_blcastle() {b_info |= 0b00001000000000000000000000000000;};
    inline void disable_brcastle() {b_info |= 0b00000100000000000000000000000000;};
    inline U64 pm_op_f() {return FILES[(b_info >> 9) & 0b111];};
    inline U64 pm_op_r() {return RANKS[(b_info >> 6) & 0b111];};
    inline U64 pm_np_f() {return FILES[(b_info >> 3) & 0b111];};
    inline U64 pm_np_r() {return RANKS[b_info & 0b111];};
    inline void set_pm_op_f(uint8_t new_move) {b_info = (b_info & 0b11111111111111111111000111111111) | static_cast<uint32_t>(new_move << 9);};
    inline void set_pm_op_r(uint8_t new_move) {b_info = (b_info & 0b11111111111111111111111000111111) | static_cast<uint32_t>(new_move << 6);};
    inline void set_pm_np_f(uint8_t new_move) {b_info = (b_info & 0b11111111111111111111111111000111) | static_cast<uint32_t>(new_move << 3);};
    inline void set_pm_np_r(uint8_t new_move) {b_info = (b_info & 0b11111111111111111111111111111000) | new_move;};
    inline bool get_turn() {return (b_info >> 25) & 0b1;};
    inline void white_turn() {b_info &= 0b11111101111111111111111111111111;};
    inline void black_turn() {b_info |= 0b00000010000000000000000000000000;};
    // /**
    //  * at end of every turn, this function runs to update the flags for checks
    //  */
    void update_check();

    // // DEBUGGING:
    void print_board();
    void set_bitboards(std::array<U64, 12> new_board) {
        bitboards = new_board;
    }
    Board negamax_next_move();
    Board MCTS_next_move();
    // friends for easier implementation
    friend Board do_move(U64 origin, U64 dest, int piece_type, Board& old_board);
    friend Board do_attack(U64 origin, U64 dest, int piece_type, Board& old_board);
    friend void white_special_moves(Board& board, std::vector<Board>& moves, U64 occupied);
    friend void white_pawn_moves(Board& board, std::vector<Board>& moves, U64 occupied, U64 boccupied);
    friend void black_special_moves(Board& board, std::vector<Board>& moves, U64 occupied);
    friend void black_pawn_moves(Board& board, std::vector<Board>& moves, U64 occupied, U64 woccupied);
    double evaluate_advantage(Board& board);
    private:
    /**
     * bitboard representation of the chessboard
     * 0 - white pawns
     * 1 - white knights
     * 2 - white bishops
     * 3 - white rooks
     * 4 - white queens
     * 5 - white king
     * 6 - black pawns
     * 7 - black knights
     * 8 - black bishops
     * 9 - black rooks
     * 10 - black queens
     * 11 - black kings
     */
    std::array<U64, 12> bitboards;
    /**
     * General information
     * 0 - white king in check
     * 1 - black king in check
     * 2 - white left castle
     * 3 - white right castle
     * 4 - black left castle
     * 5 - black right castle
     * 6 - turn (0 for white, 1 for black)
     *
     * Previous move
     * 20-22 - file of original position
     * 23-25 - rank of original position
     * 26-28 - file of new position
     * 29-31 - rank of new position
     */
    uint32_t b_info;
};

#endif