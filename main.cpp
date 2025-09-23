#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "engine/window.h"
#include "snake/game_ui.h"

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_VIDEO);
  checkSDLError("Initializing SDL");

  IMG_Init(IMG_INIT_PNG);
  checkSDLError("Initializing SDL_image");

  TTF_Init();
  checkSDLError("Initializing SDL_ttf");

  Window gameWindow{};
  GameUI gameUI{};

  Uint32 previousTick{SDL_GetTicks()};
  Uint32 currentTick;
  Uint32 deltaTime;

  SDL_Event event;
  while (true) {
    currentTick = SDL_GetTicks();
    deltaTime = currentTick - previousTick;

    while (SDL_PollEvent(&event)) {
      gameUI.handleEvent(event);
      if (event.type == SDL_QUIT) {
        SDL_Quit();
        IMG_Quit();
        return 0;
      }
    }

    gameUI.tick(deltaTime);

    gameWindow.render();
    gameUI.render(gameWindow.getSurface());

    gameWindow.update();

    previousTick = currentTick;
  }
}
