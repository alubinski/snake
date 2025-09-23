#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H
#include <string>
#define CHECK_ERRORS

#include <SDL2/SDL.h>
#include <iostream>

namespace Config {
// Game Settings
inline const std::string GAME_NAME{"snake"};
inline constexpr int WINDOW_HEIGHT{400};
inline constexpr int WINDOW_WIDTH{800};

// Colors
inline constexpr SDL_Color BACKGROUND_COLOR{85, 138, 5, 255};
inline constexpr SDL_Color FONT_COLOR{255, 255, 255, 255};

// Assets Paths
inline const std::string APPLE_IMAGE{"apple.png"};
inline const std::string FONT{"Rubik-SemiBold.ttf"};

} // namespace Config

inline void checkSDLError(const std::string &msg) {
#ifdef CHECK_ERRORS
  const char *error = SDL_GetError();
  if (*error != '\0') {
    std::cerr << msg << " Error: " << error << std::endl;
    SDL_ClearError();
  }
#endif
}

#endif
