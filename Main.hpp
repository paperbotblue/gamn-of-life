#ifndef MAIN_HPP
#define MAIN_HPP

#include "./Window.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <vector>

#define CELL_SIZE 50
#define SPAWN_RATE 10

class Main
{
  private:
    bool running;
    int counter;
    SDL_Event event;
    SDL_Point mouse_position;
    std::vector<SDL_Point> life;
    std::vector<SDL_Point> dead_cells;
    Window* window;
  
  public:
    Main();
    int run();
    void event_loop();

    void spawn_life();
    void spawn_life(SDL_Point);
    void kill_life(SDL_Point);

    bool life_exist(SDL_Point);
    void rule_function_auto();
    void rule_function_manual();
    void set_neighbouring_dead_cells(SDL_Point);
    int get_number_of_neighbouring_alive_cells(SDL_Point);
    void neighbour_check();
    void render_life();
    ~Main();
};

#endif // !Main

