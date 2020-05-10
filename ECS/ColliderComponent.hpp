#pragma once
#include <string>
#include "SDL2/SDL.h"

class ColliderComponent : public Component
{
public:
  SDL_Rect collider;
  std::string tag;

  TransformComponent* transform;

  ColliderComponent(std::string t)
  {
    tag = t;
  }
  void Init() override
  {
    if (!entity->HasComponent<TransformComponent>())
    {
      entity->AddComponent<TransformComponent>();
    }
    std::cout << "getcomp collider"<<std::endl;
    transform = &entity->GetComponent<TransformComponent>();
    
  }

  void Update() override
  {
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
  }



};
