#pragma once

#include "core/scene.hpp"
#include "debug/globaldebug.hpp"
#include "utils/color.hpp"
#include "utils/rect.hpp"

#include <memory>
#include <string>

#define ImTextureID SDL_Texture *

namespace adv
{

class Display
{
public:
  Display(int screen_width, int screen_height, std::string title,
          Color clear_color);

  void render_scene(std::shared_ptr<Scene> scene, const long delta,
                    const Rect camera_pos);
  bool is_initialized() { return initialized; }

  void close();

  SDL_Renderer *get_renderer() { return renderer; }

private:
  Color clear_color;
  bool initialized = false;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  // Debug Nodes
  GlobalDebugWindow debug_window;

  void initialize_imgui();
};

}; // namespace adv
