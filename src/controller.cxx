#include "controller.hxx"

using Color = ge211::Color;

static Color const white_color {255, 255, 255};

Controller::Controller()
        : model_(),
          view_(model_),
          cursor_position_(ge211::Posn<int>(0,0))
{ }

void
Controller::draw(ge211::Sprite_set& sprites)
{
    // background and space are always white
    background_color = white_color;
    model_.set_time_left();
    view_.draw(sprites, cursor_position_);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }

    // press 'n' will start NEW game -> reload maze, reset the game
    if (key == ge211::Key::code('n')) {
        model_.reload_game();
        model_.reset_game();
    }

    if (key == ge211::Key::up()) {
        model_.play_move({0, -1});
    }

    if (key == ge211::Key::down()) {
        model_.play_move({0, 1});
    }

    if (key == ge211::Key::left()) {
        model_.play_move({-1, 0});
    }

    if (key == ge211::Key::right()) {
        model_.play_move({1, 0});
    }
}