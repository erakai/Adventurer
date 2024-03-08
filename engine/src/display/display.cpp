#include "display/display.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "utils/logger.hpp"

using namespace adv;

Display::Display(int screen_width, int screen_height, std::string title,
                 Color clear_color)
    : clear_color(clear_color)
{
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
  {
    logger::log_sdl("Error initializing SDL!");
    return;
  }

  if (IMG_Init(IMG_INIT_PNG) < 0)
  {
    logger::log_sdl("Error initializing SDL_image!");
    return;
  }

  SDL_CreateWindowAndRenderer(screen_width, screen_height, SDL_WINDOW_SHOWN,
                              &window, &renderer);

  if (window == nullptr || renderer == nullptr)
  {
    logger::log_sdl("Error creating window and renderer!");
    return;
  }

  SDL_SetWindowTitle(window, title.c_str());

  initialized = true;
  logger::log("Display initialized");
}

Display::~Display()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
  window = nullptr;

  SDL_Quit();
}

void Display::render_scene(std::shared_ptr<Scene> scene, const long delta,
                           const Rect camera_pos)
{
  SDL_SetRenderDrawColor(renderer, clear_color.r, clear_color.g, clear_color.b,
                         clear_color.opacity);
  SDL_RenderClear(renderer);

  scene->render(renderer, delta, camera_pos);

  SDL_RenderPresent(renderer);
}
