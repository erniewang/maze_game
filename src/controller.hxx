#pragma once

#include "model.hxx"
#include "view.hxx"

// The main game class for Reversi.
class Controller : public ge211::Abstract_game
{
public:

    explicit Controller();

// `protected` means that GE211 (via base class `ge211::Abstract_game`)
// can access these members, but arbitrary other code cannot:
protected:
    //
    // Controller operations called by GE211
    //

    void on_key(ge211::Key) override;
    /* this game does not use mouse */
    // void on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) override;
    // void on_mouse_move(ge211::Posn<int>) override;

    //void on_frame(double dt) override;

    // These three delegate to the view:
    void draw(ge211::Sprite_set&) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View  view_;
    //  - the position of a keyboard-controller cursor.
    ge211::Posn<int> cursor_position_;
};
