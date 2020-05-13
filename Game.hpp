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

  void Init(const char* title, int width, int height, bool fullscreen);
  
  void HandleEvents();
  
  void Update();
  
  void Render();
  
  //Memory management
  void Clean();

  bool Running()
  {
    return isRunning;
  }

  static void AddTile(int srcX, int srcY, int xpos, int ypos);
  static SDL_Renderer *renderer;
  static SDL_Event event;
  static std::vector<ColliderComponent*> colliders;
  static bool isRunning;
  static SDL_Rect camera;
private:
  int cnt = 0;
  SDL_Window *window;
};

#endif
