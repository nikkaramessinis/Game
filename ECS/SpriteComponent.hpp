#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include <iostream>
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include <map>
#include "../AssetManager.hpp"

class SpriteComponent : public Component
{
private:
  TransformComponent *transform;
  SDL_Texture *texture;
  SDL_Rect srcRect, destRect;

  bool animated = false;
  int frames = 0;
  int speed = 100;
  
public:
  int animIndex = 0;
  std::map <const char*, Animation> animations;
  
  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
  
  SpriteComponent() = default;
  SpriteComponent(std::string id)
  {
    SetTex(id);
  }

  SpriteComponent(std::string id, bool isAnimated)
  {
    animated = isAnimated;
    Animation idle = Animation(0, 1, 100);
    Animation walkright = Animation(2, 4, 100);
    Animation walkdownwards = Animation(0, 4, 100);
    std::cout << __FUNCTION__ << __LINE__ << std::endl;
    Animation walkbackwards = Animation(3, 4, 100);
    std::cout << __FUNCTION__ << __LINE__ << std::endl;

    
    animations.emplace("Idle", idle);
    animations.emplace("WalkRight", walkright);
    animations.emplace("WalkBackwards", walkbackwards);
    animations.emplace("WalkDownwards", walkdownwards);
    std::cout << __FUNCTION__ << __LINE__ << std::endl;

    Play("Idle");
    SetTex(id);
  }
  
  void SetTex(std::string id)
  {
    texture = Game::assets->GetTexture(id);
  }
  
  void Init() override
  {

    transform = &entity->GetComponent<TransformComponent>();
    
    srcRect.x =  srcRect.y = 0;
    srcRect.w = transform->width;
    srcRect.h =  transform->height;
  }


  void Update() override
  {
    if (animated && speed > 0)
    {
      srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
    }
    srcRect.y = animIndex * transform->height;
    
    destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
    destRect.y = static_cast<int>(transform->position.y)  - Game::camera.y;
    destRect.w = transform->width * transform->scale;
    destRect.h = transform->height * transform->scale;
    
  }

  void Draw()
  {
    TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
  }

  void Play(const char * animName)
  {
    frames = animations[animName].frames;
    animIndex = animations[animName].index;
    speed = animations[animName].speed;
  }
  ~SpriteComponent()
  {
  }

};
