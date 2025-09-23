#ifndef TEXT_H
#define TEXT_H

#include "game_config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace Engine {
class Text {
public:
  Text(const std::string &initialText, int fontSize)
      : contesnt_(initialText), font_(nullptr), textSurface_(nullptr) {
    font_ = TTF_OpenFont(Config::FONT.c_str(), fontSize);
    checkSDLError("Opening font");

    setText(initialText);
  }

  void setText(const std::string &newText) {
    contesnt_ = newText;

    if (textSurface_) {
      SDL_FreeSurface(textSurface_);
    }
    textSurface_ =
        TTF_RenderText_Blended(font_, contesnt_.c_str(), Config::FONT_COLOR);
    checkSDLError("Creating text surface");
  }

  void render(SDL_Surface *surface, SDL_Rect *rect) {
    if (textSurface_) {
      SDL_BlitSurface(textSurface_, nullptr, surface, rect);
    }
  }

private:
  std::string contesnt_;
  TTF_Font *font_;
  SDL_Surface *textSurface_;
};

} // namespace Engine

#endif
