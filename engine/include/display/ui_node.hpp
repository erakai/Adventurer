#pragma once

#include "core/node.hpp"
#include "world/positioned.hpp"

#include "imgui.h"

namespace adv
{

/*
For UI elements, we have no concept of display_position/size. Their pos()
is directly equivalent to their position on the screen.
*/
class UINode : public Node, public Positioned
{
public:
  UINode(Point pos) : Positioned(pos){};
  UINode(Point pos, Dimension size) : Positioned(pos, size){};

  void render(SDL_Renderer *renderer, long delta, Rect viewport)
  {
    Node::render(renderer, delta, viewport);
    render_self(renderer);
  }

protected:
  virtual void render_self(SDL_Renderer *renderer) = 0;

  void set_imgui_window()
  {
    ImGui::SetNextWindowPos(
        {static_cast<float>(pos().x()), static_cast<float>(pos().y())},
        ImGuiCond_Once);
    ImGui::SetNextWindowSize(
        {static_cast<float>(size().w), static_cast<float>(size().h)},
        ImGuiCond_Once);
  }
};

} // namespace adv
