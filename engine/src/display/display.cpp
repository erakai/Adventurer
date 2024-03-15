#include "display/display.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_video.h"
#include "utils/logger.hpp"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

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

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetWindowTitle(window, title.c_str());

  initialize_imgui();

  initialized = true;
  logger::log("Display initialized");
}

void Display::initialize_imgui()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;            // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // IF using Docking Branch

  ImGui::StyleColorsDark();

  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);
}

void Display::close()
{
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

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

  ImGui::Render();
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

  SDL_RenderPresent(renderer);
}
