#ifndef IMAGE_H
#define IMAGE_H

#include "game_config.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <string>

namespace Engine {
class Image {
public:
  Image(const std::string &path) {
    imageSurface_ = IMG_Load(path.c_str());
    checkSDLError("Loading image");
  }

  ~Image() {
    if (imageSurface_) {
      SDL_FreeSurface(imageSurface_);
    }
  }

  void render(SDL_Surface *surface, SDL_Rect *rect) {
    SDL_BlitScaled(imageSurface_, nullptr, surface, rect);
  }

  Image(const Image &) = delete;
  Image &operator=(const Image &) = delete;

private:
  SDL_Surface *imageSurface_;
};
} // namespace Engine

#endif
