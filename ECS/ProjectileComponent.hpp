#pragma once

#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"

class ProjectileComponent : public Component
{
public:
  ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel)
  {
  }
  ~ProjectileComponent(){}
  
  void Init() override
  {
    transform = &entity->GetComponent<TransformComponent>();
    transform->velocity.x = speed;
  }

  void Update() override
  {
    distance += speed;
    
    if (transform->position.x > Game::camera.x + Game::camera.w)
    {
      std::cout << "Out of bounds "<< std::endl;
      std::cout << "transpos" << transform->position.x << std::endl;
        std::cout << "camera x: "<< Game::camera.x << "+" <<  Game::camera.w << std::endl;
      entity->Destroy();
    }
    else  if(distance > range)
    {
      std::cout << "Out of range" << std::endl;
      entity->Destroy();
    }
  }
private :
  TransformComponent* transform;

  int range = 0;
  int speed = 0;
  int distance = 0;
  Vector2D velocity;

};
