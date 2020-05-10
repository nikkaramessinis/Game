#pragma once

#include "Game.hpp"

// TODO Probably to do that singleton or RAIIor sth 
class TextureManager
{
public:
  static SDL_Texture* LoadTexture(const char* fileName);
  static void Draw(SDL_Texture* text,const SDL_Rect& src, const SDL_Rect& dest);
};
