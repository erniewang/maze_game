#pragma once

#include "model.hxx"
#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const&);

    // TODO: your code here
    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, Position cursor_position);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    // Converts an abstract board position to a concrete screen
    // position.
    Position
    board_to_screen(Model::Position board_pos) const;

    // Converts a concrete screen (pixel) position to an abstract board
    // position.
    Model::Position
    screen_to_board(Position screen_pos) const;

private:
    Model const& model_;

    ge211::Rectangle_sprite const wall_sprite;
    ge211::Rectangle_sprite const starting_sprite;
    ge211::Rectangle_sprite const ending_sprite;
    ge211::Circle_sprite const time_extender_sprite;
    ge211::Circle_sprite const player_sprite;
    ge211::Text_sprite txt_sprite;
    ge211::Text_sprite cnt_sprite;
    ge211::Font txt_font;
};
