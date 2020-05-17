#include "AssetManager.hpp"
#include "ECS/Components.hpp"

AssetManager::AssetManager(Manager* _manager) : manager(_manager)
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range,int speed, std::string id)
{
  auto& projectile(manager->AddEntity());
  projectile.AddComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
  projectile.AddComponent<SpriteComponent>(id, false);
  projectile.AddComponent<ProjectileComponent>(range,speed, vel);
  projectile.AddComponent<ColliderComponent>("projectile");
  projectile.AddGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char * path)
{
  textures.emplace(id, TextureManager::LoadTexture(path)); 
}
void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
  std::cout << __LINE__ << std::endl;
  fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
  return fonts[id];
}


SDL_Texture* AssetManager::GetTexture(std::string id)
{
//  auto it = textures.find(id); 
//  if(it != textures.end())
  // {
  //   return it->second;
  // }
  return textures[id];
  //return nullptr;
}

