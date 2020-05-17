#pragma once
#include <string>

class Map
{
public:
  Map(std::string tid, int ms, int ts);
  ~Map();

  void LoadMap(std::string path, int sizeX, int sizeY);

  void AddTile(int srcX, int srcY, int xpos, int ypos);
  
private:
  std::string textID;
  int mapScale;
  int tileSize;
  int scaledSize;
};
