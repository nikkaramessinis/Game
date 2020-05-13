#pragma once
#include "ECS.hpp"
#include "SDL2/SDL.h"

class TileComponent : public Component
{
public:
  const char * path;
  SDL_Texture* texture;
  SDL_Rect srcRect, destRect;
  Vector2D position; 
  
  TileComponent() = default;

  ~TileComponent()
  {
    SDL_DestroyTexture(texture);
  }
  
  TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char* path)
  {
    texture = TextureManager::LoadTexture(path);
    position.x = xpos;
    position.y = ypos;
    srcRect.x = srcX;
    srcRect.y = srcY;
    srcRect.w = srcRect.h = tsize;
    destRect.x= xpos;
    destRect.y= ypos;
    destRect.w = destRect.h = tsize*tscale;
    
  }

  void Update() override
  {
    destRect.x = position.x - Game::camera.x ;
    destRect.y = position.y - Game::camera.y;
  }
  
  
  void Draw() override
  {
    TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
  }
  
};
