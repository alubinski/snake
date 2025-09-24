#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include "engine/random.h"
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
    if (e.type == UserEvents::APPLE_EATEN) {
      placeRandomApple();
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
  void placeRandomApple() {
    while (true) {
      size_t randomIndex{Engine::Random::Int(0, cells_.size() - 1)};
      if (cells_[randomIndex].placeApple()) {
        break;
      }
    }
  }

  std::vector<Cell> cells_;
};

#endif
