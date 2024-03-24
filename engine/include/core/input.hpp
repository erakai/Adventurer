#pragma once

#include "display/camera.hpp"

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
  DEBUG_PRESS,
  DEBUG_RELEASE,
};

enum MouseButton
{
  LEFT_MOUSE_BUTTON,
  RIGHT_MOUSE_BUTTON,
};

enum MouseEventType
{
  MOUSE_MOTION,
  MOUSE_WHEEL_DOWN,
  MOUSE_WHEEL_UP,
  LEFT_MOUSE_BUTTON_PRESS,
  LEFT_MOUSE_BUTTON_RELEASE,
  LEFT_MOUSE_BUTTON_HOLD,
  LEFT_MOUSE_BUTTON_DRAG,
  RIGHT_MOUSE_BUTTON_PRESS,
  RIGHT_MOUSE_BUTTON_RELEASE,
  RIGHT_MOUSE_BUTTON_HOLD,
  RIGHT_MOUSE_BUTTON_DRAG,
};

// Callbacks for specific key events
extern std::unordered_map<KeyEventType, std::vector<std::function<void()>>>
    key_callbacks;

// Callbacks for every key event
extern std::vector<std::function<void(KeyEventType k)>> general_key_callbacks;

// Callbacks to be run before input loop begins
extern std::vector<std::function<void(void)>> before_input_callbacks;

// Callbacks to be run on mouse click
extern std::unordered_map<
    MouseEventType, std::vector<std::function<void(int mouse_x, int mouse_y)>>>
    mouse_callbacks;
extern std::vector<
    std::function<void(MouseEventType m, int mouse_x, int mouse_y)>>
    general_mouse_callbacks;

extern std::unordered_map<MouseButton, bool> mouse_button_states;
extern std::shared_ptr<Camera> camera;

extern int mouse_x, mouse_y;

void add_camera(std::shared_ptr<Camera> cam);

void before_input_hook(std::function<void()> func);
void key_hook(KeyEventType e, std::function<void()> func);
void key_hook(std::function<void(KeyEventType e)> func);
void mouse_hook(
    std::function<void(MouseEventType m, int mouse_x, int mouse_y)> func);
void mouse_hook(MouseEventType e,
                std::function<void(int mouse_x, int mouse_y)> func);

void run_before_input_hooks();
void run_key_hooks(KeyEventType e);
void run_mouse_hooks(MouseEventType m, int mouse_x, int mouse_y);
bool poll_event_loop();

}; // namespace input

}; // namespace adv
