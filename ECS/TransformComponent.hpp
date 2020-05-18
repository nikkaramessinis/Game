#pragma once

#include "Components.hpp"
#include "../Vector2D.hpp"
#include <cmath>


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
    position.x = 900;
    position.y = 600;
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
    float velx, vely;
    //pes oti douleuei alla dn douleuei h kateuthunsh isws ena * sto telos me kateuthunsh alla to allo einai / kati 
    velx = velocity.x/sqrt(1 + (velocity.y)*(velocity.y));
//    std::cout << "vel.x "<< velx <<std::endl;
    vely = velocity.y/sqrt(1+  + (velocity.x)*(velocity.x));
    //  std::cout << "vel.y "<< vely <<std::endl;
    
    position.x += velx * speed;
    position.y += vely * speed;
  }
};

