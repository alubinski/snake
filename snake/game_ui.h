#ifndef GAME_UI_H
#define GAME_UI_H

#include "assets.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>

class GameUI {
public:
  void handleEvent(SDL_Event &e) {}
  void tick(Uint32 deltaTime) {}
  void render(SDL_Surface *surface) {}

private:
  Assets assets_;
};

#endif
