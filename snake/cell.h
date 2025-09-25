#ifndef CELL_H
#define CELL_H

#include "assets.h"
#include "game_config.h"
#include "snake/snake_data.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>

enum class CellState { Snake, Apple, Empty };
class Cell {
public:
  Cell(int row, int col, Assets &assets)
      : row_(row), col_(col), assets_(assets) {
    initialize();
  }

  void handleEvent(const SDL_Event &e) {
    using namespace UserEvents;
    if (e.type == ADVANCE) {
      advance(e.user);
    } else if (e.type == APPLE_EATEN) {
      if (state_ == CellState::Snake) {
        snakeDuration_++;
      }
    } else if (e.type == GAME_WON) {
      snakeColor_ = Config::SNAKE_VICTORY_COLOR;
    } else if (e.type == GAME_LOST) {
      snakeColor_ = Config::SNAKE_LOST_COLOR;
    } else if (e.type == RESTART_GAME) {
      initialize();
    }
  }

  void tick(Uint32 deltaTime) {
    if (state_ == CellState::Snake && fillPercent_ < 1.0f) {
      growHead(deltaTime);
    } else if (state_ != CellState::Snake && fillPercent_ > 0.0f) {
      shrinkTail(deltaTime);
    }
  }

  void render(SDL_Surface *surface) {
    SDL_FillRect(surface, &backgroundRect_,
                 SDL_MapRGB(surface->format, backgroundColor_.r,
                            backgroundColor_.g, backgroundColor_.b));

    if (state_ == CellState::Apple) {
      assets_.apple.render(surface, &backgroundRect_);
    } else if (fillPercent_ > 0.0f) {
      SDL_FillRect(surface, &snakeRect_,
                   SDL_MapRGB(surface->format, snakeColor_.r, snakeColor_.g,
                              snakeColor_.b));
    }
  }

  bool placeApple() {
    if (state_ != CellState::Empty) {
      return false;
    }

    state_ = CellState::Apple;
    return true;
  }

private:
  void initialize() {
    fillDirection_ = MoveDirection::RIGHT;
    snakeRect_ = backgroundRect_;
    state_ = CellState::Empty;
    snakeDuration_ = 0;
    snakeColor_ = Config::SNAKE_COLOR;
    fillPercent_ = 0.0f;

    int middleRow = Config::GRID_ROWS / 2;
    if (row_ == middleRow && col_ == 2) {
      state_ = CellState::Snake;
      snakeDuration_ = 1;
      fillPercent_ = 1.0f;
    } else if (row_ == middleRow && col_ == 3) {
      state_ = CellState::Snake;
      snakeDuration_ = 2;
      fillPercent_ = 1.0f;
    } else if (row_ == middleRow && col_ == 11) {
      state_ = CellState::Apple;
    }
  }

  void advance(const SDL_UserEvent &e) {
    SnakeData *data{static_cast<SnakeData *>(e.data1)};

    bool isThisCell{data->headRow == row_ && data->headCol == col_};
    if (isThisCell) {
      if (state_ == CellState::Snake) {
        // Snake ran into itself
        SDL_Event event{UserEvents::GAME_LOST};
        SDL_PushEvent(&event);
        return;
      }
      if (state_ == CellState::Apple) {
        SDL_Event event{UserEvents::APPLE_EATEN};
        SDL_PushEvent(&event);
      }
      state_ = CellState::Snake;
      snakeDuration_ = data->length;
      fillDirection_ = data->direction;
      fillPercent_ = 0.0f;
    } else if (state_ == CellState::Snake) {
      if (snakeDuration_ == data->length) {
        fillDirection_ = data->direction;
      }
      --snakeDuration_;
      if (snakeDuration_ == 0) {
        state_ = CellState::Empty;
      }
    }
  }

  void growHead(float deltaTime) {
    using namespace Config;
    fillPercent_ += deltaTime / ADVANCE_INTERVAL;
    if (fillPercent_ > 1.0f) {
      fillPercent_ = 1.0f;
    }

    snakeRect_ = backgroundRect_;
    if (fillDirection_ == MoveDirection::RIGHT) {
      snakeRect_.w = CELL_SIZE * fillPercent_;
    } else if (fillDirection_ == MoveDirection::LEFT) {
      snakeRect_.x = backgroundRect_.x + CELL_SIZE * (1.0f - fillPercent_);
    } else if (fillDirection_ == MoveDirection::DOWN) {
      snakeRect_.h = CELL_SIZE * fillPercent_;
    } else if (fillDirection_ == MoveDirection::UP) {
      snakeRect_.y = backgroundRect_.y + CELL_SIZE * (1.0f - fillPercent_);
    }
  }

  void shrinkTail(float deltaTime) {
    using namespace Config;
    fillPercent_ -= deltaTime / ADVANCE_INTERVAL;
    if (fillPercent_ < 0.0f) {
      fillPercent_ = 0.0f;
    }

    snakeRect_ = backgroundRect_;
    if (fillDirection_ == MoveDirection::RIGHT) {
      snakeRect_.x = backgroundRect_.x + CELL_SIZE * (1 - fillPercent_);
    } else if (fillDirection_ == MoveDirection::LEFT) {
      snakeRect_.w = CELL_SIZE * fillPercent_;
    } else if (fillDirection_ == MoveDirection::DOWN) {
      snakeRect_.y = backgroundRect_.y + CELL_SIZE * (1.0f - fillPercent_);
    } else if (fillDirection_ == MoveDirection::UP) {
      snakeRect_.h = CELL_SIZE * fillPercent_;
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
  int snakeDuration_{0};
  SDL_Color snakeColor_{Config::SNAKE_COLOR};
  SDL_Rect snakeRect_;
  float fillPercent_{0};
  MoveDirection fillDirection_{MoveDirection::RIGHT};
};

#endif // CELL_H
