CPP=g++
CFLAGS = -O3
appname = test

SDL_CFLAGS := $(shell sdl2-config --cflags)
sdl_LDFLAGS := $(shell sdl2-config --libs)

CXXFLAGS := $(SDL_CFLAGS) -O3
LDFLAGS := $(SDL_LDFLAGS) -Lsdl2main -lSDL2 -lSDL2_image
sdl_cflags := $(shell pkg-config --cflags sdl2)
sdl_libs := $(shell pkg-config --libs sdl2)
override CXXFLAGS += $(sdl_cflags)
override LIBS += $(sdl_libs)
all: main.cpp Game.cpp Game.hpp TextureManager.cpp TextureManager.h Map.hpp Map.cpp GameObject.hpp GameObject.cpp ECS/ECS.hpp ECS/Components.hpp ECS/SpriteComponent.hpp ECS/TransformComponent.hpp Vector2D.hpp Vector2D.cpp ECS/KeyboardController.hpp Collision.h Collision.cpp ECS/ColliderComponent.hpp 
	$(CPP) -std=c++17 -g -o outpoutsa main.cpp Game.cpp TextureManager.cpp Map.cpp Vector2D.cpp GameObject.cpp Collision.cpp $(LDFLAGS)
clean:
	rm -f $(appname) *.o
.PHONY: all clean

