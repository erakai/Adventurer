#include "core/input.hpp"
#include "SDL_events.h"
#include "display/camera.hpp"
#include "utils/globals.hpp"

#include "utils/logger.hpp"

#include "imgui_impl_sdl2.h"

using namespace adv::input;

std::vector<std::function<void(void)>> adv::input::before_input_callbacks;
std::unordered_map<KeyEventType, std::vector<std::function<void()>>>
    adv::input::key_callbacks;
std::vector<std::function<void(KeyEventType k)>>
    adv::input::general_key_callbacks;
std::unordered_map<MouseEventType,
                   std::vector<std::function<void(int mouse_x, int mouse_y)>>>
    adv::input::mouse_callbacks;
std::vector<std::function<void(MouseEventType m, int mouse_x, int mouse_y)>>
    adv::input::general_mouse_callbacks;
std::unordered_map<MouseButton, bool> adv::input::mouse_button_states;
std::shared_ptr<adv::Camera> adv::input::camera;

int adv::input::mouse_x, adv::input::mouse_y;

void adv::input::add_camera(std::shared_ptr<adv::Camera> cam)
{
  camera = cam;
}

void adv::input::key_hook(KeyEventType e, std::function<void()> func)
{
  key_callbacks[e].push_back(func);
}

void adv::input::key_hook(std::function<void(KeyEventType k)> func)
{
  general_key_callbacks.push_back(func);
}

void adv::input::mouse_hook(
    std::function<void(MouseEventType m, int mouse_x, int mouse_y)> func)
{
  general_mouse_callbacks.push_back(func);
}

void adv::input::mouse_hook(MouseEventType e,
                            std::function<void(int mouse_x, int mouse_y)> func)
{
  mouse_callbacks[e].push_back(func);
}

void adv::input::before_input_hook(std::function<void()> func)
{
  before_input_callbacks.push_back(func);
}

void adv::input::run_key_hooks(KeyEventType e)
{
  for (auto &f : key_callbacks[e])
    f();
  for (auto &f : general_key_callbacks)
    f(e);
}

void adv::input::run_mouse_hooks(MouseEventType e, int mouse_x, int mouse_y)
{
  if (camera != nullptr)
  {
    Rect viewport = camera->get_viewport();
    mouse_x = mouse_x + (viewport.x1() / adv::globals::SUBPIXELS);
    mouse_y = mouse_y + (viewport.y1() / adv::globals::SUBPIXELS);
  }

  for (auto &f : mouse_callbacks[e])
    f(mouse_x, mouse_y);
  for (auto &f : general_mouse_callbacks)
    f(e, mouse_x, mouse_y);
}

void adv::input::run_before_input_hooks()
{
  for (auto &f : before_input_callbacks)
    f();
}

// TODO: Break this up into multiple functions
bool adv::input::poll_event_loop()
{
  ImGuiIO &io = ImGui::GetIO();
  run_before_input_hooks();

  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    // First forward event to ImGui
    ImGui_ImplSDL2_ProcessEvent(&e);

    if (e.type == SDL_QUIT)
    {
      return false;
    }

    if (!io.WantCaptureMouse)
    {

      if (e.type == SDL_MOUSEBUTTONDOWN)
      {
        switch (e.button.button)
        {
        case (SDL_BUTTON_LEFT):
          mouse_button_states[LEFT_MOUSE_BUTTON] = true;
          run_mouse_hooks(LEFT_MOUSE_BUTTON_PRESS, e.motion.x, e.motion.y);
          break;
        case (SDL_BUTTON_RIGHT):
          mouse_button_states[RIGHT_MOUSE_BUTTON] = true;
          run_mouse_hooks(RIGHT_MOUSE_BUTTON_PRESS, e.motion.x, e.motion.y);
          break;
        }
      }
      else if (e.type == SDL_MOUSEBUTTONUP)
      {
        switch (e.button.button)
        {
        case (SDL_BUTTON_LEFT):
          mouse_button_states[LEFT_MOUSE_BUTTON] = false;
          run_mouse_hooks(LEFT_MOUSE_BUTTON_RELEASE, e.motion.x, e.motion.y);
          break;
        case (SDL_BUTTON_RIGHT):
          mouse_button_states[RIGHT_MOUSE_BUTTON] = false;
          run_mouse_hooks(RIGHT_MOUSE_BUTTON_RELEASE, e.motion.x, e.motion.y);
          break;
        }
      }
      else if (e.type == SDL_MOUSEMOTION)
      {
        switch (e.button.button)
        {
        case (SDL_BUTTON_LEFT):
          if (mouse_button_states[LEFT_MOUSE_BUTTON])
            run_mouse_hooks(LEFT_MOUSE_BUTTON_DRAG, e.motion.x, e.motion.y);
          break;
        case (SDL_BUTTON_RIGHT):
          if (mouse_button_states[RIGHT_MOUSE_BUTTON])
            run_mouse_hooks(RIGHT_MOUSE_BUTTON_DRAG, e.motion.x, e.motion.y);
          break;
        }

        mouse_x = e.motion.x;
        mouse_y = e.motion.y;
        run_mouse_hooks(MOUSE_MOTION, e.motion.x, e.motion.y);
      }
      else if (e.type == SDL_MOUSEWHEEL)
      {
        if (e.wheel.y > 0) // scroll up
        {
          run_mouse_hooks(MOUSE_WHEEL_UP, e.motion.x, e.motion.y);
        }
        else if (e.wheel.y < 0) // scroll down
        {
          run_mouse_hooks(MOUSE_WHEEL_DOWN, e.motion.x, e.motion.y);
        }
      }
    }

    if (!io.WantCaptureKeyboard)
    {
      if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
      {
        switch (e.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          return false;

        case SDLK_UP:
        case SDLK_w:
          run_key_hooks(UP_MOVE_PRESS);
          break;

        case SDLK_DOWN:
        case SDLK_s:
          run_key_hooks(DOWN_MOVE_PRESS);
          break;

        case SDLK_LEFT:
        case SDLK_a:
          run_key_hooks(LEFT_MOVE_PRESS);
          break;

        case SDLK_RIGHT:
        case SDLK_d:
          run_key_hooks(RIGHT_MOVE_PRESS);
          break;

        case SDLK_o:
          run_key_hooks(DEBUG_PRESS);
          break;
        }
      }
      else if (e.type == SDL_KEYUP && e.key.repeat == 0)
      {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_w:
          run_key_hooks(UP_MOVE_RELEASE);
          break;

        case SDLK_DOWN:
        case SDLK_s:
          run_key_hooks(DOWN_MOVE_RELEASE);
          break;

        case SDLK_LEFT:
        case SDLK_a:
          run_key_hooks(LEFT_MOVE_RELEASE);
          break;

        case SDLK_RIGHT:
        case SDLK_d:
          run_key_hooks(RIGHT_MOVE_RELEASE);
          break;

        case SDLK_o:
          run_key_hooks(DEBUG_RELEASE);
          break;
        }
      }
    }
  }

  for (auto &it : mouse_button_states)
  {
    if (it.second)
    {
      switch (it.first)
      {
      case LEFT_MOUSE_BUTTON:
        run_mouse_hooks(LEFT_MOUSE_BUTTON_HOLD, mouse_x, mouse_y);
        break;
      case RIGHT_MOUSE_BUTTON:
        run_mouse_hooks(RIGHT_MOUSE_BUTTON_HOLD, mouse_x, mouse_y);
        break;
      }
    }
  }

  return true;
}
