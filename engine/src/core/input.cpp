#include "core/input.hpp"

using namespace adv::input;

std::unordered_map<KeyEventType, std::vector<std::function<void()>>> adv::input::callback_map;

void adv::input::key_hook(KeyEventType e, std::function<void()> func)
{
  callback_map[e].push_back(func);
}

void adv::input::run_key_hooks(KeyEventType e)
{
  for (auto &f: callback_map[e])
  {
    f();
  }
}

bool adv::input::poll_event_loop()
{
  SDL_Event e;

  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      return false;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
      {
        case SDLK_UP:
          run_key_hooks(UP_MOVE);
          break;

        case SDLK_DOWN:
          run_key_hooks(DOWN_MOVE);
          break;

        case SDLK_LEFT:
          run_key_hooks(LEFT_MOVE);
          break;

        case SDLK_RIGHT:
          run_key_hooks(RIGHT_MOVE);
          break;
      }
    }
  }

  return true;
}