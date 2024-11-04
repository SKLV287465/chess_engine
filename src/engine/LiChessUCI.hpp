#ifndef LICHESSUCI_HPP
#define LICHESSUCI_HPP

#include "Board.hpp"
#include <constants.hpp>
#include <string>
class LiChessUCI {
    public:
    LiChessUCI() {
        *board = Board("");
        board->set_bitboards(STARTING_POSITIONS);
    }

    LiChessUCI(std::string s) {
        *board = Board(s);
    }
    void loop();
    void search();
    void updatePosition(std::istringstream& is);

    private:

	unsigned int wtime;
	unsigned int btime;
	unsigned int winc;
	unsigned int binc;
	unsigned int movestogo;
	Board* board;
};

#endif