#include "MCnode.hpp"
#include <optional>
MCnode::MCnode(std::optional<MCnode*> parent, Board gamestate) {
    _parent = parent;
    _gamestate = gamestate;
    _w = 0;
    // number of simulations for this node
    _n = 0;
    // total number of simulations for the parent node
    if (parent) {
        _N = (parent.value())->_n;
    }
    
    _children = std::vector<std::unique_ptr<MCnode>>{};
}

Board MCnode::get_next_move() {
    double maxuct = -std::numeric_limits<double>::infinity();
    int maxindex = 0;
    for (auto i = 0; i < _children.size(); ++i) {
        if (maxuct < _children[i]->_n) {
            maxindex = i;
            maxuct = _children[i]->_n;
        }
        std::cout << _children[i]->_n << std::endl;
    }
    return (_children[maxindex]->_gamestate);
}