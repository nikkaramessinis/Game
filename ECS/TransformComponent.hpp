#pragma once

#include "Components.hpp"
#include "../Vector2D.hpp"


class TransformComponent : public Component
{

public:
  Vector2D position;
  Vector2D velocity;


  int height = 32;
  int width = 32;
  int scale = 1;
  int speed = 3;
  TransformComponent() : position()
  {
  }

  TransformComponent(int sc)
  {
    position.x = 400;
    position.y = 320;
    scale = sc;
  }

  TransformComponent(int x, int y)
  {
    position.x = x;
    position.y = y;
  }

  TransformComponent(int x, int y, int h , int w, int sc)
  {
    position.x = x;
    position.y = y;
    height = h;
    width = w;
    scale = sc;
  }
  
  void change() 
  {
//    std::cout << "called this" <<std::endl;
    velocity.x = 1;
  }
  
  void Init() override
  {
    velocity.Zero();
  }
  
  void Update() override
  {
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
  }
};

