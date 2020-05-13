#include "Game.hpp"
#include <memory>

std::unique_ptr<Game> game; 

int main(int argc, const char* argv[]) {

  const int FPS = 60;
  const int frameDelay = 1000/FPS;

  Uint32 frameStart;
  int frameTime;

  game = std::make_unique<Game>();
  game->Init("KaramEngine" , 800, 600, false);
  while (game->Running())
  {
    frameStart = SDL_GetTicks();
    
    game->HandleEvents();  
    game->Update();  
    game->Render();

    // How long the frame has taken
    frameTime = SDL_GetTicks() - frameStart;
    
    if (frameDelay > frameTime)
    {
      SDL_Delay(frameDelay - frameTime);
    }
    
  }
  game->Clean();
  return 0;
}
