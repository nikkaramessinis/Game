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

void AssetManager::AddFont(const std::string& id,const std::string& path, int fontSize)
{
  std::cout << __FUNCTION__ << __LINE__ << std::endl;
  fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(const std::string& id)
{
  auto it = fonts.find(id); 
  if(it != fonts.end())
  {
    return it->second;
  }
}


SDL_Texture* AssetManager::GetTexture(const std::string& id)
{
  auto it = textures.find(id); 
  if(it != textures.end())
  {
    return it->second;
  }
  std::cout<< __FUNCTION__ << " couldn't find texture "<< id 
  << " call AddTexture first "<<std::endl;
  exit(1);

}

