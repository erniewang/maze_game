#pragma once

#include <ge211.hxx>

#include <iostream>
#include <vector>

static const int MAZE_SIZE = 31;
static const int NUM_OF_EXTENDERS = 5;

class Model
{
public:
    using Dimensions = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;

    Model(bool is_test=false);

    /// Returns a rectangle containing all the positions of the board.
    /// This can be used to iterate over the positions.
    Dimensions dim() const { return dim_; }
    ge211::Timer timer;

    bool matrix[MAZE_SIZE][MAZE_SIZE] = {{0}}; // default is all false
    Position player_pos;
    Position starting_pos;
    Position ending_pos;
    // this is not Position[] because don't know how to initialize it
    // in the constructor
    int time_extender_pos[NUM_OF_EXTENDERS][2];

    int time_limit() const
    { return time_limit_; }

    int time_left() const
    { return time_left_; }

    bool is_game_over() const
    { return game_over_; }

    int solved() const
    { return solved_count_; }

    void play_move(Dimensions);
    void reload_game();
    void reset_game();
    // controller set time_left
    void set_time_left();

#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif

private:
    Dimensions dim_;

    // This is actually set in reload_game()
    // default limit is 60 seconds, at the beginning of game, we call
    // reset_game(), inside reset_game(), time_limit will be reduced by 5
    // that's why we set it to 65 here
    int time_limit_ = 65;
    int time_extended_ = 0;
    int time_left_;
    bool game_over_ = false;
    int solved_count_ = 0;
    bool is_test_;
};

