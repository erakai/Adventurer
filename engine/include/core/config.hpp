#pragma once

#include "utils/color.hpp"

#include <string>

namespace adv
{

class Config
{
public:
  std::string title = "Game";

  int screen_width = 1280;
  int screen_height = 720;

  Color bg_color = {33, 37, 54};
  // Color bg_color = {0, 0, 0};
};

}; // namespace adv
