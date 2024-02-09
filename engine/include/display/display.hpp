#pragma once

#include "SDL.h"

#include "nodes/node.hpp"
#include "core/scene.hpp"
#include "world/position_rect.hpp"
#include "utils/logger.hpp"

#include <string>
#include <memory>

namespace adv
{

class Display
{
  public:
    Display(int screen_width, int screen_height, std::string title);
    ~Display();

    void render_scene(std::shared_ptr<Scene> scene, const long delta, const PositionRect camera_pos);
    bool is_initialized() { return initialized; }

  private:
    bool initialized = false;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

};