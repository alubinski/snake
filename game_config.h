#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H
#include <string>
#define CHECK_ERRORS

#include <SDL2/SDL.h>
#include <iostream>

namespace UserEvents {
inline Uint32 ADVANCE{SDL_RegisterEvents(1)};
inline Uint32 APPLE_EATEN{SDL_RegisterEvents(1)};
inline Uint32 RESTART_GAME{SDL_RegisterEvents(1)};
} // namespace UserEvents

namespace Config {
// Game Settings
inline const std::string GAME_NAME{"snake"};
inline constexpr int ADVANCE_INTERVAL{200};
inline constexpr int GRID_COLUMS{16};
static_assert(GRID_COLUMS >= 12, "GRID_COLUMS must be at least 12");

inline constexpr int GRID_ROWS{5};
static_assert(GRID_ROWS >= 5, "GRID_ROWS must be at least 5");

// Size and Positioning
inline constexpr int CELL_SIZE{36};
inline constexpr int GRID_HEIGHT{GRID_ROWS * CELL_SIZE};
inline constexpr int GRID_WIDTH{GRID_COLUMS * CELL_SIZE};

inline constexpr int PADDING{5};
inline constexpr int FOOTER_HEIGHT{60};
inline constexpr int WINDOW_HEIGHT{GRID_HEIGHT + FOOTER_HEIGHT + 2 * PADDING};
inline constexpr int WINDOW_WIDTH{GRID_WIDTH + 2 * PADDING};

// Colors
inline constexpr SDL_Color BACKGROUND_COLOR{85, 138, 5, 255};
inline constexpr SDL_Color FONT_COLOR{255, 255, 255, 255};
inline constexpr SDL_Color CELL_COLOR_A{171, 214, 82, 255};
inline constexpr SDL_Color CELL_COLOR_B{161, 208, 74, 255};
inline constexpr SDL_Color SNAKE_COLOR{67, 117, 234, 255};
inline constexpr SDL_Color BUTTON_COLOR{73, 117, 46, 255};

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
