#pragma once

#include <string>

namespace adv
{

class Config
{
  public:
    std::string title = "Game";

    int screen_width = 1280;
    int screen_height = 720;

    int frames_per_second = 120;
};

};