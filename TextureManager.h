#pragma once

#include "Game.hpp"

// TODO Probably to do that singleton or RAIIor sth 
class TextureManager
{
public:
  static SDL_Texture* LoadTexture(const char* fileName);
  static void Draw(SDL_Texture* text, SDL_Rect src, SDL_Rect dest);
};
