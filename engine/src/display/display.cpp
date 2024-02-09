#include "display/display.hpp"

using namespace adv;

Display::Display(int screen_width, int screen_height, std::string title)
{
  if (SDL_Init(SDL_INIT_TIMER |
               SDL_INIT_VIDEO |
               SDL_INIT_AUDIO) < 0)
  {
    logger::log_sdl("Error initializing SDL!");
    return;
  }

  SDL_CreateWindowAndRenderer(screen_width, screen_height, 
                              SDL_WINDOW_SHOWN, &window, &renderer);

  if (window == nullptr || renderer == nullptr)
  {
    logger::log_sdl("Error creating window and renderer!");
    return;
  }

  SDL_SetWindowTitle(window, title.c_str());
  screen_surface = SDL_GetWindowSurface(window);

  initialized = true;
}

Display::~Display()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
  window = nullptr;

  SDL_Quit();
}

void Display::render_scene(std::shared_ptr<Scene> scene, const long delta, const PositionRect camera_pos)
{
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);

  scene->render(renderer, delta, camera_pos);

  SDL_RenderPresent(renderer);
  SDL_UpdateWindowSurface(window);
}