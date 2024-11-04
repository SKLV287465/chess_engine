#ifndef ALGORITHMS_CPP
#define ALGORITHMS_CPP

#include "Board.hpp"
#include "MCnode.hpp"
#include <limits>
#include <vector>
#include <random>
#include "algorithms.hpp"
double algorithms::negamax(Board& board, double alpha, double beta, int depth) {
    if (depth == 0) return board.evaluate_advantage(board); // or game is over
    double max = std::numeric_limits<double>::min();
    if (board.get_turn()) {
        // black
        if (!board.wking()) {
            return std::numeric_limits<double>::max();
        }
        for (auto move : board.generate_bmoves()) {
            double score = algorithms::negamax(move, -beta, -alpha, depth - 1);
            max = (score > max) ? score : max;
            alpha = (score > alpha) ? score : alpha;
            if (alpha >= beta) {
                break;
            }
        }
    } else {
        if (!board.bking()) {
            return std::numeric_limits<double>::max();
        }
        for (auto move : board.generate_wmoves()) {
            double score = algorithms::negamax(move, -beta, -alpha, depth - 1);
            max = (score > max) ? score : max;
            alpha = (score > alpha) ? score : alpha;
            if (alpha >= beta) {
                break;
            }
        }
    }
    return max;
}

MCnode* MCnode::selection() {
    if (!_children.size()) {
        return this;
    }
    double maxuct = std::numeric_limits<double>::min();
    int maxindex = 0;
    for (auto i = 0; i < _children.size(); ++i) {
        if (maxuct < _children[i]->UCT()) {
            maxindex = i;
            maxuct = _children[i]->UCT();
        }
    }
    return _children[maxindex]->selection();
} // compute UCT
MCnode* MCnode::expansion() {
    std::vector<Board> possible_moves;
    if (_gamestate.get_turn()) {
        possible_moves = _gamestate.generate_bmoves();
    } else {
        possible_moves = _gamestate.generate_wmoves();
    }

    for (auto &move : possible_moves) {
        auto node = new MCnode(this, move);
        _children.push_back(node);
    }
    if (_children.size() == 0) {
        return this;
    }
    std::random_device rd; // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister engine for generating random numbers
    std::uniform_int_distribution<> dis(0, _children.size() - 1); // Define range

    return _children[dis(gen)];
}
double MCnode::simulation() {
    return algorithms::negamax(_gamestate, std::numeric_limits<double>::min(), std::numeric_limits<double>::max(), 3);
}
void MCnode::backpropagation(double score) {
    if (score > 0) {
        ++_w;
    } else {
        --_w;
    }
    ++_n;
    if (_parent) {
        ++_N;
        (*_parent)->backpropagation(score);
    }
}

Board algorithms::MCTS(Board gamestate, int iterations) {
    auto root = MCnode(std::nullopt, gamestate);
    for (auto i = 0; i < iterations; ++i) {
        auto leaf = root.selection();
        auto chosen = leaf->expansion();
        auto score = chosen->simulation();
        chosen->backpropagation(score);
    }
    return root.get_next_move();
}
// when we initiate negamax, we should create an array of pairs


#endif
