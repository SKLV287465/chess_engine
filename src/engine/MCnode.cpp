#include "MCnode.hpp"

MCnode::MCnode(MCnode* parent, Board* gamestate) {
    _parent = parent;
    _gamestate = gamestate;
    _w = 0;
    // number of simulations for this node
    _n = 0;
    // total number of simulations for the parent node
    _N = (*parent)._n;
    _children = std::vector<MCnode>{};
}

Board MCnode::get_next_move() {
    double maxuct = std::numeric_limits<double>::min();
    int maxindex = 0;
    for (auto i = 0; i < _children.size(); ++i) {
        if (maxuct < _children[i].UCT()) {
            maxindex = i;
            maxuct = _children[i].UCT();
        }
    }
    return *(_children[maxindex]._gamestate);
}