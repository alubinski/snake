#ifndef WINDOW_H
#define WINDOW_H

#include "game_config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_video.h>

class Window {
public:
  Window() {
    SDLWindow_ =
        SDL_CreateWindow(Config::GAME_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, Config::WINDOW_WIDTH,
                         Config::WINDOW_HEIGHT, 0);

    checkSDLError("CreateWindow");
  }

  ~Window() {
    if (SDLWindow_ && SDL_WasInit(SDL_INIT_VIDEO)) {
      SDL_DestroyWindow(SDLWindow_);
    }
  }

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  void render() {
    SDL_FillRect(getSurface(), nullptr,
                 SDL_MapRGB(getSurface()->format, Config::BACKGROUND_COLOR.r,
                            Config::BACKGROUND_COLOR.g,
                            Config::BACKGROUND_COLOR.b));
  }

  void update() { SDL_UpdateWindowSurface(SDLWindow_); }

  SDL_Surface *getSurface() { return SDL_GetWindowSurface(SDLWindow_); }

private:
  SDL_Window *SDLWindow_;
};

#endif
