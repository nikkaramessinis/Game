#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;


class Game {
public:
  Game();
  ~Game();

  void init(const char* title, int width, int height, bool fullscreen);
  
  void handleEvents();
  
  void update();
  
  void render();
  
  //Memory management
  void clean();

  bool running()
  {
    return isRunning;
  }

  static SDL_Renderer *renderer;
  static SDL_Event event;
  static std::vector<ColliderComponent*> colliders;
private:
  int cnt = 0;
  bool isRunning;
  SDL_Window *window;
};

#endif
