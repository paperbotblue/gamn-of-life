#include "./Main.hpp"
#include "Window.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

Main::Main()
{
  this->window = new Window("Game Of Life", 750, 1100, {0xFF, 0xFF, 0xFF, 0xFF}); 
  this->running = true; 
  this->counter = 0;
  srand(time(0));
}
int Main::run()
{
  SDL_Rect r;

  while(running)
  {   
    if(SDL_PollEvent(&event) > 0)
    {
      if(event.type == SDL_QUIT) 
      {
        running = false;
        continue;
      }
      SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
      event_loop();
    }

    render_life();
    this->window->render_window();
  }
  return 0;
}

void Main::rule_function_auto()
{
    if (counter == 5000)
    {
      rule_function_manual();
      counter = 0;
    } counter++;
}

void Main::rule_function_manual()
{
  std::vector<SDL_Point>* next = new std::vector<SDL_Point>;
  for(int i = 0; i < this->window->window_height; i+=CELL_SIZE)
  {
    for(int j = 0 ; j < this->window->window_width; j+=CELL_SIZE)
    {
      int num_neighbours = get_number_of_neighbouring_alive_cells({j, i});
      if(num_neighbours == 3 && !life_exist({j, i}))
      {
        next->push_back({j, i});
      }
      else if(life_exist({j ,i}))
      {
        if(num_neighbours < 4 && num_neighbours > 1)
        {
          next->push_back({j, i});
        }
      }

    }
  }
  
  life.clear();
  for(int i = 0 ; i < next->size() ; ++i)
  {
    life.push_back(next->at(i));
  }

}

int Main::get_number_of_neighbouring_alive_cells(SDL_Point p)
{
  int num_neighbours = 0;
  if(life_exist({p.x-CELL_SIZE ,p.y-CELL_SIZE})) num_neighbours++;
  if(life_exist({p.x           ,p.y-CELL_SIZE})) num_neighbours++;
  if(life_exist({p.x+CELL_SIZE ,p.y-CELL_SIZE})) num_neighbours++;

  if(life_exist({p.x-CELL_SIZE ,p.y})) num_neighbours++;
  if(life_exist({p.x+CELL_SIZE ,p.y})) num_neighbours++;
  
  if(life_exist({p.x-CELL_SIZE ,p.y+CELL_SIZE})) num_neighbours++;
  if(life_exist({p.x           ,p.y+CELL_SIZE})) num_neighbours++;
  if(life_exist({p.x+CELL_SIZE ,p.y+CELL_SIZE})) num_neighbours++;
  
  return num_neighbours;
}

void Main::event_loop()
{
  if(event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym) 
    {
      case 's':
        spawn_life(mouse_position);
        break;
      case 'a':
        rule_function_manual();
        break;
      case 'r':
        spawn_life();
        break;
    }

      
  }
  else if(event.type == SDL_KEYUP)
  {
    switch(event.key.keysym.sym)
    {

    }
  }
}

void Main::spawn_life()
{
  for (int i = 0 ; i < window->window_height ; i+=CELL_SIZE)
  {
    for (int j = 0 ; j < window->window_width ; j+=CELL_SIZE)
    {
      if (rand() % 100 < SPAWN_RATE && !life_exist({j,i}))
      {
        printf("spanned life\n");
        life.push_back({j,i});
      }
    }
  }
}

void Main::spawn_life(SDL_Point p)
{
  p.x = (p.x / CELL_SIZE) * CELL_SIZE;
  p.y = (p.y / CELL_SIZE) * CELL_SIZE;
  life.push_back(p);
}

void Main::kill_life(SDL_Point p)
{
  for(int k = 0 ; k < life.size() ; ++k)
  {
    if(life.at(k).x == p.x && life.at(k).y == p.y)
    {
      life.erase(life.begin() + k);
    }
  }
}

bool Main::life_exist(SDL_Point p)
{
  for (int i = 0 ; i < life.size() ; ++i)
  {
    if(life.at(i).x == p.x && life.at(i).y == p.y) return true;
  }
  return false;
}

void Main::render_life()
{
  SDL_Rect r;
  SDL_SetRenderDrawColor(this->window->renderer, 0x00, 0x00, 0x00, 0xFF);
  for(int i = 0 ; i < life.size() ; ++i)
  {
    r = {life.at(i).x, life.at(i).y, CELL_SIZE - 2, CELL_SIZE - 2};
    SDL_RenderFillRect(this->window->renderer, &r);
  }
}

Main::~Main()
{

}
