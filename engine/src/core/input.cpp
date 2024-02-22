#include "core/input.hpp"
#include "SDL_events.h"

#include <map>

using namespace adv::input;

std::unordered_map<KeyEventType, std::vector<std::function<void()>>>
    adv::input::key_callbacks;
std::vector<std::function<void(KeyEventType k)>>
    adv::input::general_key_callbacks;
std::vector<std::function<void(void)>> adv::input::before_input_callbacks;

void adv::input::key_hook(KeyEventType e, std::function<void()> func)
{
  key_callbacks[e].push_back(func);
}

void adv::input::key_hook(std::function<void(KeyEventType k)> func)
{
  general_key_callbacks.push_back(func);
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

void adv::input::run_before_input_hooks()
{
  for (auto &f : before_input_callbacks)
    f();
}

bool adv::input::poll_event_loop()
{
  run_before_input_hooks();

  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return false;
    } else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
      switch (e.key.keysym.sym) {
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
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
      switch (e.key.keysym.sym) {
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
