#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "game_config.h"
#include "snake/snake_data.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

class GameState {
public:
  void handleEvent(const SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
      handleKeyEvent(e.key);
    } else if (e.type == UserEvents::APPLE_EATEN) {
      ++snake.length;
      if (snake.length == Config::MAX_LENGTH) {
        SDL_Event event{UserEvents::GAME_WON};
        SDL_PushEvent(&event);
      }
    } else if (e.type == UserEvents::RESTART_GAME) {
      restartGame();
    } else if (e.type == UserEvents::GAME_LOST ||
               e.type == UserEvents::GAME_WON) {
      isGameOver = true;
    }
  }

  void tick(Uint32 deltaTime) {
    if (isPaused || isGameOver) {
      return;
    }

    elapsedTime += deltaTime;
    if (elapsedTime >= Config::ADVANCE_INTERVAL) {
      elapsedTime = 0;
      updateSnake();
    }
  }

private:
  void updateSnake() {
    snake.direction = nextDirection;
    switch (snake.direction) {
    case UP:
      snake.headRow--;
      break;
    case DOWN:
      snake.headRow++;
      break;
    case LEFT:
      snake.headCol--;
      break;
    case RIGHT:
      snake.headCol++;
      break;
    }

    if (snake.headRow < 0 || snake.headRow >= Config::GRID_ROWS ||
        snake.headCol < 0 || snake.headCol >= Config::GRID_COLUMS) {
      SDL_Event event{UserEvents::GAME_LOST};
      SDL_PushEvent(&event);
      return;
    }

    SDL_Event event{UserEvents::ADVANCE};
    event.user.data1 = &snake;
    SDL_PushEvent(&event);
  }

  void restartGame() {
    isGameOver = false;
    isPaused = true;
    snake = {.headRow = Config::GRID_ROWS / 2,
             .headCol = 3,
             .length = 2,
             .direction = RIGHT};
    nextDirection = RIGHT;
    elapsedTime = 0;
  }

  void handleKeyEvent(const SDL_KeyboardEvent &e) {
    if (isGameOver) {
      return;
    }
    switch (e.keysym.sym) {
    case SDLK_UP:
    case SDLK_w:
      if (snake.direction != DOWN) {
        nextDirection = UP;
      }
      break;
    case SDLK_DOWN:
    case SDLK_s:
      if (snake.direction != UP) {
        nextDirection = DOWN;
      }
      break;
    case SDLK_LEFT:
    case SDLK_a:
      if (snake.direction != RIGHT) {
        nextDirection = LEFT;
      }
      break;
    case SDLK_RIGHT:
    case SDLK_d:
      if (isPaused) {
        isPaused = false;
        nextDirection = RIGHT;
        updateSnake();
      } else if (snake.direction != LEFT) {
        nextDirection = RIGHT;
      }
      break;
    }
  }

  SnakeData snake{.headRow = Config::GRID_ROWS / 2,
                  .headCol = 3,
                  .length = 2,
                  .direction = RIGHT};
  Uint32 elapsedTime{0};
  MoveDirection nextDirection{RIGHT};
  bool isPaused{true};
  bool isGameOver{false};
};

#endif // GAME_STATE_H
