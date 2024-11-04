#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Board.hpp"


namespace algorithms {
    double negamax(Board& board, double alpha, double beta, int depth);
    Board MCTS(Board& gamestate, int iterations);
    // when we initiate negamax, we should create an array of pairs
}

#endif