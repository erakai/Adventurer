#pragma once

#include "SDL.h"

#include "nodes/node.hpp"
#include "core/scene.hpp"
#include "utils/logger.hpp"

#include <string>

namespace adv
{

class Display
{
  public:
    Display(int screen_width, int screen_height, std::string title);
    ~Display();

    void render_scene(std::shared_ptr<Scene> scene, long delta);
    bool is_initialized() { return initialized; }

  private:
    bool initialized = false;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* screen_surface = nullptr;
    
};

};