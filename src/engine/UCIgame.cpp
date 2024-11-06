#include "LiChessUCI.hpp"
#include "Board.hpp"

int main() {
    // auto b = Board("rnbqkbnr/1ppppppp/8/p7/4P3/8/PPPP1PPP/RNBQKBNR");
    // b.print_board();
    // b.generate_wmoves();
    
    auto uciengine = LiChessUCI();
    uciengine.loop();
};