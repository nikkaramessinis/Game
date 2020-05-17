#pragma once

#include "../Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"


class KeyboardController : public Component
{
public:
  TransformComponent* transform;
  SpriteComponent* sprite;
  
  void Init() override
  {
    transform = &entity->GetComponent<TransformComponent>();
    sprite = &entity->GetComponent<SpriteComponent>();
  }

  void Update() override
  {
    if (Game::event.type == SDL_KEYDOWN)
    {
      switch (Game::event.key.keysym.sym)
      {
      case SDLK_w:
//        std::cout << "Key down "<<std::endl;
        transform->velocity.y = -1;
        sprite->Play("WalkBackwards");
        break;
      case SDLK_s:
        transform->velocity.y = 1;
        sprite->Play("WalkDownwards");
        break;
      case SDLK_d:
        transform->velocity.x = 1;
        sprite->Play("WalkRight");
        break;
      case SDLK_a:
        transform->velocity.x = -1;
        sprite->Play("WalkRight");
        sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
        break;
      default:
        break;
      }
    }
    if (Game::event.type == SDL_KEYUP)
    {
      switch (Game::event.key.keysym.sym)
      {
      case SDLK_w:
        transform->velocity.y = 0;
        sprite->Play("Idle");
        break;
      case SDLK_s:
        transform->velocity.y = 0;
        sprite->Play("Idle");
        break;
      case SDLK_d:
        transform->velocity.x = 0;
        sprite->Play("Idle");
        break;
      case SDLK_a:
        transform->velocity.x = 0;
        sprite->spriteFlip = SDL_FLIP_NONE;
        sprite->Play("Idle");
        break;
      case SDLK_ESCAPE:
        Game::isRunning = false;
      default:
        break;
      }
    }

  }

};


