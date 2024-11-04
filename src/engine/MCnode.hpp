#ifndef MCNODE_HPP
#define MCNODE_HPP

#include <cmath>
#include <vector>
#include <queue>
#include "Board.hpp"
class MCnode {
    public:
    MCnode(MCnode* parent, Board* gamestate);
    double UCT() {
        return (_w / _n) + C * sqrt(log10(_N) / _n);
    }
    Board get_next_move();
    MCnode selection(); // compute UCT
    MCnode expansion();
    double simulation(); // negmax with alpha beta pruning
    void backpropagation(double score);
    private:
    // supposed to be wins, but is the score from negmax here.
    double _w;
    // number of simulations for this node
    double _n;
    // total number of simulations for the parent node
    double _N;
    Board* _gamestate;
    MCnode* _parent;
    const double C = std::sqrt(2);
    std::vector<MCnode> _children;
};

// UCT = w/n + C * sqrt((lnN)/n)
// selection -> finding the leaf node with the highest UCT
// Expansion -> move generation
// Simulation do negmax algo to simulate score.
// Backpropagation -> update the tree.

#endif