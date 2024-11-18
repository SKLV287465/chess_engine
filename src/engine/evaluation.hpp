#ifndef EVALUATION_HPP
#define EVALUATION_HPP

#include <array>
#include "Board.hpp"

std::array<int, 6> piece_values = {
    1000,
    3000,
    3250,
    5000,
    9000,
    30000
};

/**
 * evaluates the advantage white has over black.
 * - this is an overly simplified version of this. Need to add tables
 */

#endif