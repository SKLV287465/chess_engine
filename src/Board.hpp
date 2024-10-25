#include <array>
#include <vector>
#include <constants.hpp>

class Board {
    public:
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

    std::vector<Board> generate_wmoves();
    std::vector<Board> generate_bmoves();


    /**
     * at end of every turn, this function runs to update the flags for checks
     */
    void update_check();

    // DEBUGGING:
    void print_board();

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
     * last move original position
     * - first 3 bits -> file
     * - last 3 bits -> rank
     */
    unsigned char lm_op;
    /**
     * last move new position
     * - first 3 bits -> file
     * - last 3 bits -> rank
     */
    unsigned char lm_np;
    /**
     * miscellaneous information about the board
     * 0 - white king in check
     * 1 - black king in check
     * 2 - white left castle
     * 3 - white right castle
     * 4 - black left castle
     * 5 - black right castle
     * 
     */
    unsigned char binfo;
};