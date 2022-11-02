#include "model.hxx"
#include <catch.hxx>

using namespace ge211;

TEST_CASE("verify maze")
{
    Model m(true);
    CHECK(m.player_pos == Posn<int>{1, 1});
    CHECK(m.ending_pos == Posn<int>{MAZE_SIZE-2, 1});
    /*
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    CHECK(m[{0, 0}] == Player::neither);
    CHECK(m.find_move({0, 0}) == nullptr);
    CHECK_THROWS_AS(m.play_move({0, 0}), Client_logic_error);
     */
}

struct Test_access
{
    Model& model;

    // Constructs a `Test_access` with a reference to the Model under test.
    explicit Test_access(Model&);
    // Sets the player at `posn` to `player`.
    void set_player(Model::Position posn);
    // Gives direct access to `model.next_moves_` so our tests can modify it:
    //Move_map& next_moves();
};

/*
// Example of using Test_access to modify the model state to set up our test.
TEST_CASE("Small Game")
{
    Model model(true);
    Test_access access(model);

    // Use Test_access to place pieces on the board without going through
    // Model::play_move():
    access.set_player({1, 1}, Player::dark);
    access.set_player({2, 1}, Player::dark);
    access.set_player({1, 2}, Player::dark);
    access.set_player({2, 2}, Player::dark);

    // Use Test_access to set `model.next_moves_` to allow the particular
    // (illegal) move that we'd like to try:
    access.next_moves()[{0, 0}] = Position_set {{0, 0}};

    // Now we can play the move, because model.next_moves_ says so:
    model.play_move({0, 0});

    // Check that the game is over and Dark won:
    CHECK(model.turn() == Player::neither);
    CHECK(model.winner() == Player::dark);

    // Construct the set of board positions that should contain Player::dark:
    Position_set darks {{0, 0}, {1, 1}, {2, 1}, {1, 2}, {2, 2}};

    // Go through each position on the board, confirming that the positions in
    // the `darks` set contain Player::dark and all other positions contain
    // Player::neither.
    for (auto posn : model.board()) {
        Player expected = darks[posn] ? Player::dark : Player::neither;
        CHECK(model[posn] == expected);
    }
}
*/

///
/// Member function definitions for Test_access
///

Test_access::Test_access(Model& model)
        : model(model)
{ }

void
Test_access::set_player(Model::Position posn)
{
    model.player_pos = posn;
}

/*
Move_map&
Test_access::next_moves()
{
    return model.next_moves_;
}
*/

// Example of using Test_access to modify the model state to set up our test.
/*
TEST_CASE("8x8 Game")
{
    ///
    /// SETUP
    ///

    Model model(8, 8);
    Test_access access(model);
    const Move* move;
    Move_map next_moves;

    CHECK(model.turn() == Player::dark);
    model.play_move({3,3});
    CHECK(model.turn() == Player::light);
    move = model.find_move({3,3});
    CHECK(move == nullptr);
    move = model.find_move({3,4});
    CHECK(move->second == Position_set{{3,4}});
    model.play_move({3,4});
    model.play_move({4,3});
    // still at openning phase, outside of center positions not allowed
    move = model.find_move({4,5});
    CHECK(move == nullptr);
    // There should now be only 1 move {4,4}
    next_moves = access.next_moves();
    CHECK(next_moves.size() == 1);
    model.play_move({4,4});
    //    d
    //  DLd
    //  DLd
    //    d
    //  dark's turn, there're 4 moves
    next_moves = access.next_moves();
    CHECK(next_moves.size() == 4);
    model.play_move({4,5}); //dark played
    //
    // lDL
    //  DDD
    // l l l
    next_moves = access.next_moves();
    CHECK(model.turn() == Player::light);
    CHECK(next_moves.size() == 4);
    model.play_move({3,2});
    // ddddd
    //  LLL
    //   DDD
    //
    CHECK(model[{3,3}] == Player::light);
    CHECK(model[{4,5}] == Player::dark);
    next_moves = access.next_moves();
    CHECK(next_moves.size() == 5);


}
*/
