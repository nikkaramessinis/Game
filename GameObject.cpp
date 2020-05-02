#include "GameObject.hpp"
#include "TextureManager.h"

GameObject::GameObject( SDL_Renderer* ren, const char* textureSheet, int x, int y) :
  renderer(ren),
  objTexture(TextureManager::LoadTexture(textureSheet, ren)),
  xpos(x),
  ypos(y)
{
}

void GameObject::Update()
{
  xpos++;
  ypos++;

  srcRect.h = 64;
  srcRect.w = 64;
  srcRect.x = 0;
  srcRect.y = 0;
  
  destRect.x = xpos;
  destRect.y = ypos;
  destRect.w = srcRect.w*2;
  destRect.h = srcRect.h*2;
}

void GameObject::Render()
{
  SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

