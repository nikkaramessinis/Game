#pragma once
#include "ECS.hpp"

class PositionComponent : public Component
{
private:
  int xpos = 0;
  int ypos = 0;
public:
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
