#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "./Util.hpp"

class Window
{
  public:
    int window_width;
    int window_height;
    char* window_title;

    SDL_Color window_bg_color;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Window(char* window_title, unsigned int window_height, unsigned int window_width, SDL_Color window_bg_color);
    void render_window();    

};


#endif // !WINDOW_HPP
