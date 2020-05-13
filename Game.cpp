#include "Game.hpp"
#include "TextureManager.h"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0,0,800, 640};

bool Game::isRunning = false;

auto &player(manager.AddEntity());

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
  
  map = new Map("assets/terrain_ss.png", 3, 32);
  //ecs implementation

  map->LoadMap("assets/map.map", 25, 20);
  
  player.AddComponent<TransformComponent>(2);
  player.AddComponent<SpriteComponent>("assets/player.png", true);
  player.AddComponent<KeyboardController>();
  player.AddComponent<ColliderComponent>("player");
  player.AddGroup(Game::groupPlayers);
 
}

auto& tiles(manager.GetGroup(Game::groupMap));
auto& players(manager.GetGroup(Game::groupPlayers));
auto& colliders(manager.GetGroup(Game::groupColliders));

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
//  std::cout << "before collision "<<std::endl;
  camera.x = player.GetComponent<TransformComponent>().position.x - 400;
  camera.y = player.GetComponent<TransformComponent>().position.y - 320;

  if (camera.x < 0)
  {
    camera.x = 0;
  }
  if (camera.y < 0)
  {
    camera.y =0;
  }
  if (camera.x > camera.w)
  {
    camera.x = camera.w;
  }
  if (camera.y > camera.h)
  {
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
  
  SDL_RenderPresent(renderer);
}

void Game::Clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
//  std::cout << "Game Cleaned ..." << std::endl;
}
