#include "MCnode.hpp"
#include <optional>
#include <iostream>
MCnode::MCnode(std::optional<MCnode*> parent, Board gamestate) {
    _parent = parent;
    _gamestate = gamestate;
    _w = 0;
    // number of simulations for this node
    _n = 0;
    // total number of simulations for the parent node
    if (parent) {
        _N = (*parent)->_n;
    }
    
    _children = std::vector<MCnode*>{};
}

Board MCnode::get_next_move() {
    double maxuct = std::numeric_limits<double>::min();
    int maxindex = 0;
    std::cout << "getnextmove" << std::endl;
    for (auto i = 0; i < _children.size(); ++i) {
        if (maxuct < _children[i]->UCT()) {
            maxindex = i;
            maxuct = _children[i]->UCT();
        }
    }
    std::cout << _children.size() << std::endl;
    return (_children[maxindex]->_gamestate);
}