#ifndef CELL_H
#define CELL_H

#include "assets.h"
#include "game_config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

enum class CellState { Snake, Apple, Empty };
class Cell {
public:
  Cell(int row, int col, Assets &assets)
      : row_(row), col_(col), assets_(assets) {
    initialize();
  }

  void handleEvent(const SDL_Event &e) {}
  void tick(Uint32 deltaTime) {}
  void render(SDL_Surface *surface) {
    SDL_FillRect(surface, &backgroundRect_,
                 SDL_MapRGB(surface->format, backgroundColor_.r,
                            backgroundColor_.g, backgroundColor_.b));

    if (state_ == CellState::Apple) {
      assets_.apple.render(surface, &backgroundRect_);
    } else if (state_ == CellState::Snake) {
      SDL_FillRect(surface, &backgroundRect_,
                   SDL_MapRGB(surface->format, Config::SNAKE_COLOR.r,
                              Config::SNAKE_COLOR.g, Config::SNAKE_COLOR.b));
    }
  }

private:
  void initialize() {
    state_ = CellState::Empty;
    int middleRow = Config::GRID_ROWS / 2;
    if (row_ == middleRow && col_ == 2) {
      state_ = CellState::Snake;
    } else if (row_ == middleRow && col_ == 3) {
      state_ = CellState::Snake;
    } else if (row_ == middleRow && col_ == 11) {
      state_ = CellState::Apple;
    }
  }

  CellState state_;
  int row_;
  int col_;
  Assets &assets_;
  SDL_Rect backgroundRect_{col_ * Config::CELL_SIZE + Config::PADDING,
                           row_ *Config::CELL_SIZE + Config::PADDING,
                           Config::CELL_SIZE, Config::CELL_SIZE};
  SDL_Color backgroundColor_{(row_ + col_) % 2 == 0 ? Config::CELL_COLOR_A
                                                    : Config::CELL_COLOR_B};
};

#endif // CELL_H
