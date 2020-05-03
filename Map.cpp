#include "Map.hpp"
#include "TextureManager.h"
#include <iostream>

//put this in a config file or json or sth
int lvl1[20][25] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map()
{
  dirt = TextureManager::LoadTexture("assets/dirt.png");
  if(!dirt)
  {
    std::cout << "Couldn't load texture" << std::endl;
  }
  grass = TextureManager::LoadTexture("assets/grass.png");
  water = TextureManager::LoadTexture("assets/water.png");
  
  src.x = 0;
  src.y = 0;
  
  src.w = 32;
  src.h = 32;
  dest.x = 0;
  dest.y = 0;
  dest.w = 32;
  dest.h = 32;
  LoadMap(lvl1);
}

void Map::LoadMap(int arr[20][25])
{
  for(int row = 0; row < 20; row++)
  {
    for(int column = 0; column < 25; column++)
    {
      map[row][column] = arr[row][column];
    }
  }
}

void Map::DrawMap()
{
  int type=0;
  for(int row = 0; row < 20; row++)
  {
    for(int column = 0; column < 25; column++)
    {
      type = map[row][column];
      dest.x = column * 32;
      dest.y = row * 32;
      
      switch (type)
      {
      case 0:
        TextureManager::Draw(water, src, dest);
        break;
      case 1:
        TextureManager::Draw(grass, src, dest);
        break;
      case 2:
        TextureManager::Draw(dirt, src, dest);
        break;
      }
    }
  }
}
