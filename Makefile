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
all: main.cpp Game.cpp Game.hpp TextureManager.cpp TextureManager.h Map.hpp Map.cpp ECS/ECS.hpp ECS/Components.hpp ECS/SpriteComponent.hpp ECS/PositionComponent.hpp
	$(CPP) -std=c++17 -o outpoutsa main.cpp Game.cpp TextureManager.cpp Map.cpp $(LDFLAGS)
clean:
	rm -f $(appname) *.o
.PHONY: all clean

