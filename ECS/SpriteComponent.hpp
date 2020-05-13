#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include <iostream>
#include "../TextureManager.h"
#include "Animation.hpp"
#include <map>

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
  SpriteComponent(const char* path)
  {
    SetTex(path);
  }

  SpriteComponent(const char* path, bool isAnimated)
  {
    animated = isAnimated;
    Animation idle = Animation(0, 4, 100);
    Animation walk = Animation(2, 4, 100);

    
    animations.emplace("Idle", idle);
    animations.emplace("Walk", walk);

    Play("Idle");
    SetTex(path);
  }
  
  void SetTex(const char* path)
  {
    texture = TextureManager::LoadTexture(path);
    if (texture)
    {
      std::cout << "Failed to load texture"<<std::endl;
      exit;
    }
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
    if (animated)
    {
      srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
    }
    srcRect.y = animIndex * transform->height;
    
    destRect.x = static_cast<int>(transform->position.x);
    destRect.y = static_cast<int>(transform->position.y);
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
    SDL_DestroyTexture(texture);
  }

};
