#ifndef LICHESSUCI_HPP
#define LICHESSUCI_HPP

#include "Board.hpp"
#include <constants.hpp>
#include <string>
#include <memory>
class LiChessUCI {
    public:
    LiChessUCI() {
        board = std::make_unique<Board>("");
        board->set_bitboards(STARTING_POSITIONS);
    }

    LiChessUCI(std::string s) {
        board = std::make_unique<Board>(s);
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
	std::unique_ptr<Board> board;
};

#endif