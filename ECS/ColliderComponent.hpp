#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "Components.hpp"

class ColliderComponent : public Component
{
public:
  SDL_Rect collider;
  std::string tag;

  TransformComponent* transform;

  SDL_Texture* tex;
  SDL_Rect srcR, destR;
  
  ColliderComponent(std::string t)
  {
    tag = t;
  }

  ColliderComponent(std::string t, int  xpos, int ypos, int size)
  {
    tag = t;
    collider.x = xpos;
    collider.y = ypos;
    collider.h = collider.w = size;
  }
  void Init() override
  {
    if (!entity->HasComponent<TransformComponent>())
    {
      entity->AddComponent<TransformComponent>();
    }
    std::cout << "getcomp collider"<<std::endl;
    transform = &entity->GetComponent<TransformComponent>();

    tex = TextureManager::LoadTexture("assets/ColTex.png");
    srcR = {0, 0, 32, 32};
    destR = {collider.x, collider.y , collider.w, collider.h};

    
  }

  void Update() override
  {
    if (tag != "terrain")
    {
      collider.x = static_cast<int>(transform->position.x);
      collider.y = static_cast<int>(transform->position.y);
      collider.w = transform->width * transform->scale;
      collider.h = transform->height * transform->scale;
    }
    
    destR.x = collider.x - Game::camera.x; 
    destR.y = collider.y - Game::camera.y; 
  }


  void Draw() override
  {
    TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);

  }

};
