#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 15;
static Color const wall_color {0, 0, 0}; // black wall
static Color const red_color {255, 100, 100};
static Color const green_color {100, 255, 100};
static Color const light_blue_color {128, 128, 255};
static Color const blue_color {0, 0, 255};
static int const player_radius = grid_size / 2 - 1;
static Color const txt_color = {50, 50, 50};


View::View(Model const& model)
        : model_(model),
          wall_sprite({grid_size, grid_size}, wall_color),
          starting_sprite({grid_size, grid_size}, red_color),
          ending_sprite({grid_size, grid_size}, green_color),
          time_extender_sprite(player_radius, light_blue_color),
          player_sprite(player_radius, blue_color),
          txt_sprite(),
          cnt_sprite(),
          txt_font(ge211::Font{"OpenSans-Bold.ttf", 24})
{}

void View::draw(Sprite_set& set, Position cursor_position)
{
    Dimensions dim = model_.dim();
    for(int i=0; i<dim.height; i++){
        for(int j=0; j < dim.width; j++){
            if(model_.matrix[i][j]){
                set.add_sprite(wall_sprite, board_to_screen({j,i}), 0);
            }
        }
    }

    for(int i=0; i < NUM_OF_EXTENDERS; i++){
        Position pos = {model_.time_extender_pos[i][0], model_.time_extender_pos[i][1]};
       set.add_sprite(time_extender_sprite, board_to_screen(pos), 1);
    }

    set.add_sprite(starting_sprite, board_to_screen(model_.starting_pos), 1);
    set.add_sprite(ending_sprite, board_to_screen(model_.ending_pos), 1);
    set.add_sprite(player_sprite, board_to_screen(model_.player_pos), 2);

    ge211::Text_sprite::Builder txt_builder(txt_font);

    // counter
    std::string counter_txt = "Solved: " + std::to_string(model_.solved());
    txt_builder.color(txt_color) << counter_txt;
    cnt_sprite.reconfigure(txt_builder);
    set.add_sprite(cnt_sprite, board_to_screen({12, model_.dim().height + 4}), 2);


    ge211::Text_sprite::Builder txt_builder2(txt_font);
    // timer
    if(model_.is_game_over()){
        txt_builder2.color(txt_color) << "Game Over";

        txt_sprite.reconfigure(txt_builder2);
        Position pos{10, model_.dim().height + 1};
        set.add_sprite(txt_sprite, board_to_screen(pos), 2);
    }else{
        int time_left = model_.time_left();
        std::string time_left_txt = std::to_string(time_left);
        txt_builder2.color(txt_color) << time_left_txt;

        txt_sprite.reconfigure(txt_builder2);
        Position pos{15, model_.dim().height + 1};
        set.add_sprite(txt_sprite, board_to_screen(pos), 2);
    }

    /*
    if(model_.is_game_over()){
        // it's possible no winner so both players will be grayed-out
        if(model_.winner() != Player::dark) {
            for (auto pos: model_.board()) {
                if (model_[pos] == Player::dark) {
                    set.add_sprite(loser_sprite, board_to_screen(pos), 3);
                }
            }
        }
        if(model_.winner() != Player::light) {
            for (auto pos: model_.board()) {
                if (model_[pos] == Player::light) {
                    set.add_sprite(loser_sprite, board_to_screen(pos), 3);
                }
            }
        }
    }

    // mouse sprite
    Position real_cursor_position = {cursor_position.x - cursor_radius,
                                     cursor_position.y - cursor_radius};
    if(model_.turn() == Player::dark){
        set.add_sprite(dark_player_mouse_sprite, real_cursor_position, 4);
    }else if(model_.turn() == Player::light){
        set.add_sprite(light_player_mouse_sprite, real_cursor_position, 4);
    }
     */

}

View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    int width = model_.dim().width;
    int height = model_.dim().height + 10;
    return grid_size * Dimensions{width, height};
}

std::string
View::initial_window_title() const
{
    return "Ernie's Maze";
}

View::Position
View::board_to_screen(Model::Position pos) const
{
    return {grid_size * pos.x, grid_size * pos.y};
}

Model::Position
View::screen_to_board(View::Position pos) const
{
    return {pos.x / grid_size, pos.y / grid_size};
}
