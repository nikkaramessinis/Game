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

std::vector<ColliderComponent*> Game::colliders;
bool Game::isRunning = false;

auto &player(manager.AddEntity());
auto &wall(manager.AddEntity());

const char* mapFile = "assets/terrain_ss.png";
enum groupLabels : std::size_t
{
  groupMap,
  groupPlayers,
  groupEnemies,
  groupColliders
};


auto& tiles(manager.GetGroup(groupMap));
auto& players(manager.GetGroup(groupPlayers));
auto& enemies(manager.GetGroup(groupEnemies));

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
  
  map = new Map();
  //ecs implementation

  Map::LoadMap("assets/map.map", 25, 20);
  
  player.AddComponent<TransformComponent>(2);
  player.AddComponent<SpriteComponent>("assets/player.png", true);
  player.AddComponent<KeyboardController>();
  player.AddComponent<ColliderComponent>("player");
  player.AddGroup(groupPlayers);
 
}

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
  manager.Refresh();
  manager.Update();
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
  for (auto& p : players)
  {
    p->Draw();
  }
  for (auto& e : enemies)
  {
    e->Draw();
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
void Game::AddTile(int srcX,int srcY, int xpos, int ypos)
{
  auto& tile(manager.AddEntity());
  tile.AddComponent<TileComponent>(srcX, srcY, xpos, ypos, mapFile);
  tile.AddGroup(groupMap);
}
