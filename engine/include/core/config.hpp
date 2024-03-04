#pragma once

#include "utils/color.hpp"
#include "utils/globals.hpp"

#include <string>

namespace adv
{

class Config
{
public:
  std::string title = "Game";

  int screen_width = 1280;
  int screen_height = 720;

  int starting_scene_world_width = 1280 * globals::WORLD_DIST_PER_DISPLAY_PIXEL;
  int starting_scene_world_height = 720 * globals::WORLD_DIST_PER_DISPLAY_PIXEL;

  int frames_per_second = 144;

  Color bg_color = {33, 37, 54};
  // Color bg_color = {0, 0, 0};
};

}; // namespace adv
