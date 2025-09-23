#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include "snake/assets.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <vector>

class Grid {
public:
  Grid(Assets &assets) {
    using namespace Config;
    cells_.reserve(GRID_ROWS * GRID_COLUMS);
    for (int r{}; r < GRID_ROWS; ++r) {
      for (int c{}; c < GRID_COLUMS; ++c) {
        cells_.emplace_back(r, c, assets);
      }
    }
  }

  void handleEvent(const SDL_Event &e) {
    for (auto &cell : cells_) {
      cell.handleEvent(e);
    }
  }

  void tick(Uint32 deltaTime) {
    for (auto &cell : cells_) {
      cell.tick(deltaTime);
    }
  }

  void render(SDL_Surface *surface) {
    for (auto &cell : cells_) {
      cell.render(surface);
    }
  }

private:
  std::vector<Cell> cells_;
};

#endif
