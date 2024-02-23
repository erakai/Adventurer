#pragma once

#include <functional>
#include <vector>

namespace adv
{

namespace input
{

enum KeyEventType
{
  LEFT_MOVE_PRESS,
  RIGHT_MOVE_PRESS,
  UP_MOVE_PRESS,
  DOWN_MOVE_PRESS,
  LEFT_MOVE_RELEASE,
  RIGHT_MOVE_RELEASE,
  UP_MOVE_RELEASE,
  DOWN_MOVE_RELEASE,
};

enum MouseEventType
{
  LEFT_MOUSE_BUTTON,
};

// Callbacks for specific key events
extern std::unordered_map<KeyEventType, std::vector<std::function<void()>>>
    key_callbacks;

// Callbacks for every key event
extern std::vector<std::function<void(KeyEventType k)>> general_key_callbacks;

// Callbacks to be run before input loop begins
extern std::vector<std::function<void(void)>> before_input_callbacks;

// Callbacks to be run on mouse click
extern std::vector<
    std::function<void(MouseEventType m, int mouse_x, int mouse_y)>>
    mouse_callbacks;

extern std::unordered_map<MouseEventType, bool> mouse_button_states;

void before_input_hook(std::function<void()> func);
void key_hook(KeyEventType e, std::function<void()> func);
void key_hook(std::function<void(KeyEventType e)> func);
void mouse_hook(
    std::function<void(MouseEventType m, int mouse_x, int mouse_y)> func);

void run_before_input_hooks();
void run_key_hooks(KeyEventType e);
void run_mouse_hooks(MouseEventType m, int mouse_x, int mouse_y);
bool poll_event_loop();

}; // namespace input

}; // namespace adv
