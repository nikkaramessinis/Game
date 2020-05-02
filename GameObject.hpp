#pragma once
#include "Game.hpp"

class GameObject
{
public:
  GameObject(SDL_Renderer* ren, const char* texturesheet, int x, int y);
  ~GameObject();

  void Update();
  
  void Render();

private:
  int xpos;
  int ypos;

  SDL_Renderer* renderer;
  SDL_Texture* objTexture;
  SDL_Rect srcRect, destRect;
};
