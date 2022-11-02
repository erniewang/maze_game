#include <fstream>
#include <cstdlib>
#include <ctime>
#include "model.hxx"

using namespace ge211;

Model::Model(bool is_test)
        : timer(Timer()),
          player_pos(Position{0, 0}),
          starting_pos(Position{0, 0}),
          ending_pos(Position{0, 0}),
          is_test_(is_test)
{
    // in the future, we have different sizes of mazes
    // we can set dim_ in reload_game()
    // but here dim_ is fixed to MAZE_SIZE
    dim_ = {MAZE_SIZE, MAZE_SIZE};
    std::srand(std::time(0));
    // reset maze
    reload_game();
    // reset starting, ending positions, time extenders
    reset_game();
}

void
Model::reload_game()
{
    std::string filename = "maze";
    if(is_test_){
        filename += "test.txt";
    }else{
        int maze_num = std::rand() % 10;
        filename += "0" + std::to_string(maze_num) + ".txt";
    }
    std::ifstream f = ge211::open_resource_file(filename);
    std::string line;
    int i = 0;
    while(std::getline(f, line)){
        for(int j = 0; j < line.length(); j++){
            if(line[j] == '#'){
                // true means it's wall
                matrix[i][j] = true;
            } else {
                matrix[i][j] = false;
            }
        }
        i++;
    }
    f.close();
    time_limit_ = 65;
    time_extended_ = 0;
    solved_count_ = 0;
}

void
Model::reset_game()
{
    game_over_ = false;
    // Shorten time_limit by 5
    if(time_limit_ >= 10){
        time_limit_ -= 5;
    }
    time_extended_ = 0;
    timer.reset();

    // in test, all blocks are walls except one straight route at
    //  (1, 1) - (1, 29)
    if(is_test_){
        starting_pos = {1,1};
        player_pos = {1,1};
        ending_pos = {MAZE_SIZE-2, 1};
        for (int i = 0; i < NUM_OF_EXTENDERS; i++){
            time_extender_pos[i][0] = 5 * (i + 1); // 5, 10, 15, 20, 25
            time_extender_pos[i][1] = 1;
        }
        return;
    }

    int range = MAZE_SIZE - 2;
    //reset starting
    while(true){
        int x = std::rand() % range + 1;
        int y = std::rand() % range + 1;
        if(matrix[y][x] == false){
            starting_pos = {x, y};
            player_pos = {x, y};
            break;
        }
    }

    //reset ending
    while(true){
        int x = std::rand() % range + 1;
        int y = std::rand() % range + 1;
        if(matrix[y][x] == false){
            ending_pos = {x, y};
            break;
        }
    }

    //reset time extenders
    for (int i = 0; i < NUM_OF_EXTENDERS; i++){
        while(true){
            int x = std::rand() % range + 1;
            int y = std::rand() % range + 1;
            if(matrix[y][x] == false){
                time_extender_pos[i][0] = x;
                time_extender_pos[i][1] = y;
                break;
            }
        }
    }
}

void
Model::play_move(Dimensions dim)
{
    if(game_over_){
        return;
    }

    Position move_to = player_pos + dim;
    if(matrix[move_to.y][move_to.x]){
        // will move to wall, so just return
        return;
    }
    player_pos = move_to;
    if (player_pos == ending_pos){
        game_over_ = true;
        solved_count_ += 1;
        reset_game();
        return;
    }

    // Check if player hit one of time extender circles
    // the player can keep going back to time extender to extend time
    // this is not a bug, according to spec, it's correct behavior
    for (int i = 0; i < NUM_OF_EXTENDERS; i++){
        Position pos = {time_extender_pos[i][0], time_extender_pos[i][1]};
        if (player_pos == pos ){
            int diff = time_limit_ - time_left_;
            if (diff < 5){
                time_extended_ += diff;
            }else{
                time_extended_ += 5;
            }
            break;
        }
    }
}

void
Model::set_time_left()
{
    if (game_over_){
        time_left_ = 0;
        return;
    }

    time_left_ = time_limit_ + time_extended_ - (int)timer.elapsed_time().seconds();
    if(time_left_ > time_limit_){
        time_left_ = time_limit_;
    }
    if(time_left_ < 0){
        game_over_ = true;
        time_left_ = 0;
    }
}