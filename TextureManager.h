#pragma once

#include "Game.hpp"

// TODO Probably to do that singleton or RAIIor sth 
class TextureManager
{
public:
  static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};
