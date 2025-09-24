#ifndef GAME_UI_H
#define GAME_UI_H

#include "assets.h"
#include "snake/grid.h"
#include "snake/restart_button.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>

class GameUI {
public:
  GameUI() : grid_(assets_) {}

  void handleEvent(SDL_Event &e) {
    grid_.handleEvent(e);
    restart_button_.handleEvent(e);
  }
  void tick(Uint32 deltaTime) { grid_.tick(deltaTime); }
  void render(SDL_Surface *surface) {
    grid_.render(surface);
    restart_button_.render(surface);
  }

private:
  Grid grid_;
  Assets assets_;
  RestartButton restart_button_;
};

#endif
