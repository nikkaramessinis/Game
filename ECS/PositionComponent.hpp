#pragma once

#include "Components.hpp"

class PositionComponent : public Component
{
private:
  int xpos = 0;
  int ypos = 0;
public:
  PositionComponent() : xpos(0), ypos(0)
  {
  }
  PositionComponent(int x, int y):xpos(x), ypos(y)
  {
  }
  int X()
  {
    return xpos;
  }
  
  int Y()
  {
    return ypos;
  }

  void Update() override
  {
    xpos++;
    ypos++;
  }

  void SetPos(int x, int y)
  {
    xpos = x;
    ypos = y;
  }
};

