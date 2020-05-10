#pragma once
#include "SDL2/SDL.h"

class Collision
{
public:
  // Axis-Aligned Bound Box
  static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};
