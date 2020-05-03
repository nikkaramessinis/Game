#include "Game.hpp"
#include "TextureManager.h"
#include "GameObject.hpp"
#include "Map.hpp"

GameObject* player;
GameObject* enemy;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

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
  
//  player = new GameObject("assets/player.png", 0, 0);
//  make all of these smart pointers
  enemy = new GameObject("assets/player2.png", 50 , 50);
  map = new Map();
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
  if (player)
  {
    player->Update();
  }
  enemy->Update();
}

void Game::render()
{
  SDL_RenderClear(renderer);
  // this id where we would add stuff to render
  map->DrawMap();
  if (player)
  {
    player->Render();
  }
  if (enemy)
  {
  enemy->Render();
  }
  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game Cleaned ..." << std::endl;
}
