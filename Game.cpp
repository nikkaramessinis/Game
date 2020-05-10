#include "Game.hpp"
#include "TextureManager.h"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include <iostream>
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto &player(manager.AddEntity());
auto &wall(manager.AddEntity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen)
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
      std::cout << "Renderer created ..." << std::endl;
    }
    isRunning = true;
  }
  else
  {
    isRunning = false;
  }
  
  map = new Map();
  //ecs implementation
  

  player.AddComponent<TransformComponent>(0, 0);
  player.AddComponent<SpriteComponent>("assets/player2.png");
  player.AddComponent<KeyboardController>();
  player.AddComponent<ColliderComponent>("player");
  wall.AddComponent<TransformComponent>(300.0f,300.0f);
  wall.AddComponent<SpriteComponent>("assets/dirt_0.png");
  wall.AddComponent<ColliderComponent>("wall");
}

void Game::handleEvents()
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
void Game::update()
{
  manager.Refresh();
  manager.Update();
  std::cout << "before collision "<<std::endl;
  if (Collision::AABB(player.GetComponent<ColliderComponent>().collider,
  wall.GetComponent<ColliderComponent>().collider))
  {
    std::cout << "Collided " << std::endl;
  }
}

void Game::render()
{
  SDL_RenderClear(renderer);
  // this id where we would add stuff to render
  map->DrawMap();
  manager.Draw();
  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game Cleaned ..." << std::endl;
}
