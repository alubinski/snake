#ifndef RESTART_BUTTON_H
#define RESTART_BUTTON_H

#include "engine/text.h"
#include "game_config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>

class RestartButton {
public:
  void render(SDL_Surface *surface) {
    SDL_FillRect(surface, &button_rect_,
                 SDL_MapRGB(surface->format, current_color_.r, current_color_.g,
                            current_color_.b));
    text_.render(surface, &text_rect_);
  }

  void handleEvent(SDL_Event &e) {
    using namespace UserEvents;
    if (e.type == SDL_MOUSEBUTTONDOWN) {
      handleLeftClick(e.button);
    } else if (e.type == UserEvents::GAME_WON ||
               e.type == UserEvents::GAME_LOST) {
      current_color_ = Config::BUTTON_HIGHLIGHT_COLOR;
    } else if (e.type == UserEvents::RESTART_GAME) {
      current_color_ = Config::BUTTON_COLOR;
    }
  }

private:
  void handleLeftClick(SDL_MouseButtonEvent &e) {
    using namespace UserEvents;
    if (e.x >= button_rect_.x && e.x <= button_rect_.x + button_rect_.w &&
        e.y >= button_rect_.y && e.y <= button_rect_.y + button_rect_.h) {
      SDL_Event event{RESTART_GAME};
      SDL_PushEvent(&event);
    }
  }

  SDL_Rect button_rect_{
      Config::WINDOW_WIDTH - 150, Config::GRID_HEIGHT + Config::PADDING * 2,
      150 - Config::PADDING, Config::FOOTER_HEIGHT - Config::PADDING};
  SDL_Color current_color_{Config::BUTTON_COLOR};
  Engine::Text text_{"Restart", 20};
  SDL_Rect text_rect_{button_rect_.x + Config::PADDING * 5,
                      button_rect_.y + Config::PADDING * 3, 0, 0};
};

#endif // RESTART_BUTTON_H
