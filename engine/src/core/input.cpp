#include "core/input.hpp"
#include "SDL_events.h"
#include "display/camera.hpp"
#include "utils/globals.hpp"

using namespace adv::input;

std::unordered_map<KeyEventType, std::vector<std::function<void()>>>
    adv::input::key_callbacks;
std::vector<std::function<void(KeyEventType k)>>
    adv::input::general_key_callbacks;
std::vector<std::function<void(void)>> adv::input::before_input_callbacks;
std::vector<std::function<void(MouseEventType m, int mouse_x, int mouse_y)>>
    adv::input::mouse_callbacks;

std::unordered_map<MouseButton, bool> adv::input::mouse_button_states;
std::shared_ptr<adv::Camera> adv::input::camera;

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
  mouse_callbacks.push_back(func);
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
    mouse_x =
        mouse_x + (viewport.x1() / adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL);
    mouse_y =
        mouse_y + (viewport.y1() / adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL);
  }

  for (auto &f : mouse_callbacks)
    f(e, mouse_x, mouse_y);
}

void adv::input::run_before_input_hooks()
{
  for (auto &f : before_input_callbacks)
    f();
}

bool adv::input::poll_event_loop()
{
  run_before_input_hooks();

  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      return false;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
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
        break;
      case (SDL_BUTTON_RIGHT):
        mouse_button_states[RIGHT_MOUSE_BUTTON] = false;
        break;
      }
    }
    else if (e.type == SDL_MOUSEMOTION)
    {
      for (auto &it : mouse_button_states)
      {
        if (it.second)
        {
          switch (it.first)
          {
          case LEFT_MOUSE_BUTTON:
            run_mouse_hooks(LEFT_MOUSE_BUTTON_DRAG, e.motion.x, e.motion.y);
            break;
          case RIGHT_MOUSE_BUTTON:
            run_mouse_hooks(RIGHT_MOUSE_BUTTON_DRAG, e.motion.x, e.motion.y);
            break;
          }
        }
      }
    }
    else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
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
      }
    }
  }

  return true;
}
