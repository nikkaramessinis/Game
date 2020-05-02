#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game {
public:
  Game();
  ~Game();

  void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
  
  void handleEvents();
  
  void update();
  
  void render();
  
  //Memory management
  void clean();

  bool running()
  {
    return isRunning;
  }

private:
  int cnt = 0;
  bool isRunning;
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif
