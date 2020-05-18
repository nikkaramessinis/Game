#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"
#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0,0,1600, 1280};

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto &player(manager.AddEntity());
auto &label(manager.AddEntity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(const char* title, int width, int height, bool fullscreen)
{
  int flags = 0;
  
  if (fullscreen)
  {
    flags = SDL_WINDOW_FULLSCREEN;
  }
  
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer)
    {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      // std::cout << "Renderer created ..." << std::endl;
    }
    isRunning = true;
  }
  else
  {
    isRunning = false;
  }

  if (TTF_Init() == -1)
  {
    std::cout << "Error : SDL_TTF " << std::endl;
  }
  
  assets->AddTexture("terrain", "assets/terrain_ss.png");
  assets->AddTexture("player", "assets/player.png");
  assets->AddTexture("projectile", "assets/proj.png");
  
  assets->AddFont("Georgia", "assets/georgia.ttf", 16);
  
  map = new Map("terrain", 3, 32);
  //ecs implementation

  map->LoadMap("assets/map.map", 25, 20);
  
  player.AddComponent<TransformComponent>(2);
  player.AddComponent<SpriteComponent>("player", true);
  player.AddComponent<KeyboardController>();
  player.AddComponent<ColliderComponent>("player");
  player.AddGroup(Game::groupPlayers);

  SDL_Color white = {255, 255, 255, 255};
  label.AddComponent<UILabel>(10, 10, "Test String", "Georgia", white);
  
  //assets->CreateProjectile(Vector2D(600, 640),Vector2D(2, 0), 200, 1, "projectile");
  //assets->CreateProjectile(Vector2D(600, 600),Vector2D(2, 0), 200, 1, "projectile");
  //assets->CreateProjectile(Vector2D(620, 610),Vector2D(2, 1), 200, 1, "projectile");
  //assets->CreateProjectile(Vector2D(680, 620),Vector2D(2, -1), 200, 1, "projectile");
  //assets->CreateProjectile(Vector2D(670, 600),Vector2D(2, 0), 200, 1, "projectile");
 
}

auto& tiles(manager.GetGroup(Game::groupMap));
auto& players(manager.GetGroup(Game::groupPlayers));
auto& colliders(manager.GetGroup(Game::groupColliders));
auto& projectiles(manager.GetGroup(Game::groupProjectiles));

void Game::HandleEvents()
{
  SDL_PollEvent(&event);
  switch (event.type)
  {
  case SDL_QUIT:
    isRunning = false;
      break;      
  default:
    break;
  }
  
}

void Game::Update()
{
  SDL_Rect playerCol = player.GetComponent<ColliderComponent>().collider;
  Vector2D playerPos = player.GetComponent<TransformComponent>().position;

  std::stringstream ss;
  ss << "Player position : " << playerPos << std::endl;
  label.GetComponent<UILabel>().SetLabelText(ss.str(), "Georgia");
  
  manager.Refresh();
  manager.Update();

  for(auto& c : colliders)
  {
    SDL_Rect cCol = c->GetComponent<ColliderComponent>().collider;
    if (Collision::AABB(cCol, playerCol))
    {
      player.GetComponent<TransformComponent>().position = playerPos;
    }
  }

  for (auto& p : projectiles)
  {
    if (Collision ::AABB(player.GetComponent<ColliderComponent>().collider,p->GetComponent<ColliderComponent>().collider))
    {
      std::cout << "Hit player "<<std::endl;
      p->Destroy();
    }
  }
  
  //  std::cout << "before collision "<<std::endl;
  camera.x = player.GetComponent<TransformComponent>().position.x - 400;
  camera.y = player.GetComponent<TransformComponent>().position.y - 320;
  
  if (camera.x < 0)
  {
    //std::cout << "Camera.x" << camera.x;
    camera.x = 0;
  }
  
  if (camera.y < 0)
  {
    //std::cout << "Camera.y < 0";
    camera.y = 0;
  }
  if (camera.x > camera.w)
  {
    //std::cout << "Camera.x "<< camera.x  <<" w "<< camera.w;
    camera.x = camera.w;
  }
  if (camera.y > camera.h)
  {
    //std::cout << "Camera.y "<<camera.y  <<" h "<< camera.h;
    camera.y = camera.h; 
  }

}

void Game::Render()
{
  SDL_RenderClear(renderer);
  // this id where we would add stuff to render
  for (auto& t : tiles)
  {
    t->Draw();
  }

  for (auto& c : colliders)
  {
    c->Draw();
  }
  
  for (auto& p : players)
  {
    p->Draw();
  }

  for (auto& p: projectiles)
  {
    p->Draw();
  }

  label.Draw();
  SDL_RenderPresent(renderer);
}

void Game::Clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
//  std::cout << "Game Cleaned ..." << std::endl;
}
