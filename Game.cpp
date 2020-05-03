#include "Game.hpp"
#include "TextureManager.h"
#include "Map.hpp"
#include "ECS/Components.hpp"

Map* map = nullptr;
SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto &player(manager.AddEntity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  int flags = 0;
  
  if (fullscreen)
  {
    flags = SDL_WINDOW_FULLSCREEN;
  }
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    std::cout << "Subsystems initialized ..." << std::endl;
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window)
    {
      std::cout << "Window created" << std::endl;
    }

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
  player.AddComponent<PositionComponent>(500, 500);
  player.AddComponent<SpriteComponent>("assets/player.png");
}

void Game::handleEvents()
{
  SDL_Event event;
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

  if (player.GetComponent<PositionComponent>().X() > 100)
  {
    player.GetComponent<SpriteComponent>().SetTex("assets/player2.png");
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
