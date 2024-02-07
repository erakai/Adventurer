#pragma once

#include "SDL_events.h"

#include <map>
#include <vector>
#include <functional>

namespace adv
{

namespace input
{


enum KeyEventType
{
  LEFT_MOVE,
  RIGHT_MOVE,
  UP_MOVE,
  DOWN_MOVE
};

extern std::unordered_map<KeyEventType, std::vector<std::function<void()>>> callback_map;

void key_hook(KeyEventType e, std::function<void()> func);
void run_key_hooks(KeyEventType e);
bool poll_event_loop();

};

};