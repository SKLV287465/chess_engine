#include <catch2/catch_test_macros.hpp>
#include "../src/engine/Board.hpp"
#include <constants.hpp>
TEST_CASE("check king checks") {
    // ensure that starting b_info is zero
    auto board = Board{};
    CHECK(board.wking_in_check() == false);
    CHECK(board.bking_in_check() == false);
    board.check_bking();
    board.check_wking();
    CHECK(board.wking_in_check() == true);
    CHECK(board.bking_in_check() == true);
    board.uncheck_bking();
    board.uncheck_wking();
    CHECK(board.wking_in_check() == false);
    CHECK(board.bking_in_check() == false);
};

TEST_CASE("check castle stuff works") {
    auto board = Board();
    CHECK(board.can_wlcastle());
    CHECK(board.can_blcastle());
    CHECK(board.can_wrcastle());
    CHECK(board.can_brcastle());
    board.disable_blcastle();
    CHECK(board.can_wlcastle());
    CHECK(!board.can_blcastle());
    CHECK(board.can_wrcastle());
    CHECK(board.can_brcastle());
    board.disable_brcastle();
    CHECK(board.can_wlcastle());
    CHECK(!board.can_blcastle());
    CHECK(board.can_wrcastle());
    CHECK(!board.can_brcastle());
    board.disable_wlcastle();
    CHECK(!board.can_wlcastle());
    CHECK(!board.can_blcastle());
    CHECK(board.can_wrcastle());
    CHECK(!board.can_brcastle());
    board.disable_wrcastle();
    CHECK(!board.can_wlcastle());
    CHECK(!board.can_blcastle());
    CHECK(!board.can_wrcastle());
    CHECK(!board.can_brcastle());
}

TEST_CASE("prev move sanity check") {
    auto board = Board{};
    board.set_pm_op_f(5);
    board.set_pm_op_r(7);
    board.set_pm_np_f(4);
    board.set_pm_np_r(0);
    CHECK(board.pm_op_f() == FILES[5]);
    CHECK(board.pm_op_r() == RANKS[7]);
    CHECK(board.pm_np_f() == FILES[4]);
    CHECK(board.pm_np_r() == RANKS[0]);
}