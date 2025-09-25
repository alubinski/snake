#ifndef SCORE_COUNTER_H
#define SCORE_COUNTER_H

#include "assets.h"
#include "engine/text.h"
#include "game_config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>

class ScoreCounter {
public:
  ScoreCounter(Assets &assets) : assets_(assets) {}

  void handleEvent(const SDL_Event &e) {
    if (e.type == UserEvents::APPLE_EATEN) {
      currentScore_++;
      text_.setText(getScoreString());
    } else if (e.type == UserEvents::RESTART_GAME) {
      currentScore_ = 0;
      text_.setText(getScoreString());
    }
  }

  void render(SDL_Surface *surface) {
    using namespace Config;
    SDL_FillRect(surface, &backgroundRect_,
                 SDL_MapRGB(surface->format, SCORE_BACKGROUND_COLOR.r,
                            SCORE_BACKGROUND_COLOR.g,
                            SCORE_BACKGROUND_COLOR.b));
    assets_.apple.render(surface, &appleRect_);
    text_.render(surface, &textRect_);
  }

private:
  std::string getScoreString() {
    return std::to_string(currentScore_) + "/" + std::to_string(maxScore_);
  }

  Assets &assets_;
  int maxScore_{Config::MAX_LENGTH - 2};
  int currentScore_{0};
  Engine::Text scoreText_{getScoreString(), 40};
  Engine::Text text_{getScoreString(), 40};

  SDL_Rect backgroundRect_{
      Config::PADDING, Config::GRID_HEIGHT + 2 * Config::PADDING,
      maxScore_ > 99 ? 250 : 190, Config::FOOTER_HEIGHT - Config::PADDING};
  SDL_Rect appleRect_{backgroundRect_.x + Config::PADDING,
                      backgroundRect_.y + Config::PADDING,
                      backgroundRect_.h - Config::PADDING * 2,
                      backgroundRect_.h - Config::PADDING * 2};
  SDL_Rect textRect_{appleRect_.x + appleRect_.w + Config::PADDING,
                     appleRect_.y, 0, 0};
};
#endif // SCORE_COUNTER_H
