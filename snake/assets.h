#ifndef ASSETS_H
#define ASSETS_H

#include "engine/image.h"
#include "game_config.h"

struct Assets {
  Engine::Image apple{Config::APPLE_IMAGE};
};

#endif
