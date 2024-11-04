#include "LiChessUCI.hpp"

int main() {
    auto uciengine = LiChessUCI();
    uciengine.loop();
};