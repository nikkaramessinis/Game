#include "Map.hpp"
#include "TextureManager.h"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"
#include <fstream>


extern Manager manager;

Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts)
{
  scaledSize = ms * ts;
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
  char c;
  std::fstream mapFile;
  mapFile.open(path);

  int srcX, srcY;
  
  for (int y=0; y < sizeY; y++)
  {
    for (int x =0; x<sizeX; x++)
    {
      mapFile.get(c);
      srcY = atoi(&c) * tileSize;
      mapFile.get(c);
      srcX = atoi(&c) * tileSize;
      //64 means doubling the size of the tile
      AddTile(srcX, srcY, x*scaledSize, y*scaledSize);
      mapFile.ignore();
      
    }
  }
  mapFile.ignore();
  
  for (int y = 0; y < sizeY; y++)
  {
    for (int x = 0; x < sizeX; x++)
    {
      mapFile.get(c);
      if (c == '1')
      {
        auto &tcol(manager.AddEntity());
        tcol.AddComponent<ColliderComponent>("terrain", x * scaledSize,
                                             y * scaledSize, scaledSize);
        tcol.AddGroup(Game::groupColliders);
      }
      mapFile.ignore();
    }
  }  
  mapFile.close();
}


void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
  auto& tile(manager.AddEntity());
  tile.AddComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
  tile.AddGroup(Game::groupMap);
}
