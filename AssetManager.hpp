#pragma once

#include <map>
#include <string>
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include "ECS/ECS.hpp"
#include <SDL2/SDL_ttf.h>

class AssetManager
{
public:
  AssetManager(Manager* manager);
  ~AssetManager();
//gameobjects
  void CreateProjectile(Vector2D pos,Vector2D vel, int range,int speed, std::string id);
  

  //texture management
  void AddTexture(std::string id, const char * path);
  SDL_Texture* GetTexture(const std::string& id);

  void AddFont(const std::string& id, const std::string& path, int fontSize);
  TTF_Font* GetFont(const std::string& id);
private:

  Manager* manager;
  std::map<std::string, SDL_Texture*> textures;
  std::map<std::string, TTF_Font*> fonts;
  
};
