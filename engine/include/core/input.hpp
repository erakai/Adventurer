#pragma once

#include <functional>
#include <vector>

namespace adv
{

namespace input
{

enum KeyEventType {
  LEFT_MOVE_PRESS,
  RIGHT_MOVE_PRESS,
  UP_MOVE_PRESS,
  DOWN_MOVE_PRESS,
  LEFT_MOVE_RELEASE,
  RIGHT_MOVE_RELEASE,
  UP_MOVE_RELEASE,
  DOWN_MOVE_RELEASE,
};

// Callbacks for specific key events
extern std::unordered_map<KeyEventType, std::vector<std::function<void()>>>
    key_callbacks;

// Callbacks for every key event
extern std::vector<std::function<void(KeyEventType k)>> general_key_callbacks;

// Callbacks to be run before input loop begins
extern std::vector<std::function<void(void)>> before_input_callbacks;

void before_input_hook(std::function<void()> func);
void key_hook(KeyEventType e, std::function<void()> func);
void key_hook(std::function<void(KeyEventType e)> func);

void run_before_input_hooks();
void run_key_hooks(KeyEventType e);
bool poll_event_loop();

}; // namespace input

}; // namespace adv
