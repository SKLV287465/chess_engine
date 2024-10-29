#include <catch2/catch_test_macros.hpp>
#include "../src/engine/Board.hpp"
#include <constants.hpp>
#include <iostream> 
TEST_CASE("general tests") {
    auto board = Board{};
    board.set_bitboards(STARTING_POSITIONS);
    // check that there are 20 moves generated initially.
    std::cout << board.generate_bmoves().size() << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}
// TEST_CASE("pawns") {
//     // single push
//     // double push
//     // single push promotions and attack

//     // attack out of square
    
//     // en passant (can test)
// }

// TEST_CASE("knights") {
//     // no spillover
// }

// TEST_CASE("bishops") {

// }

// TEST_CASE("rooks") {

// }

// TEST_CASE("kings") {

// }

// TEST_CASE("queens") {

// }