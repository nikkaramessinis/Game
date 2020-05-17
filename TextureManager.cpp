#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
  SDL_Surface* tempSurface = IMG_Load(texture);
  SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  if(!tex)
  {
    std::cout << "Couldn't load texture" << texture << std::endl;
  }
  SDL_FreeSurface(tempSurface);
  return tex;
}


void TextureManager::Draw(SDL_Texture* tex,const SDL_Rect& src,const SDL_Rect& dest, SDL_RendererFlip flip)
{
  SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0, nullptr, flip);
}
