#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>


class AssetManager;
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

  static SDL_Renderer *renderer;
  static SDL_Event event;
  static bool isRunning;
  static SDL_Rect camera;
  static AssetManager*  assets;
  
  enum groupLabels : std::size_t
  {
    groupMap,
    groupPlayers,
    groupColliders,
    groupProjectiles
  };

  
private:
  int cnt = 0;
  SDL_Window *window;
};

#endif
