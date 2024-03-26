#pragma once

#include "SDL_render.h"
#include "display/ui_node.hpp"
#include "tiler.hpp"

using namespace adv;

class ToolSelector : public UINode
{
public:
  ToolSelector(std::function<void(Tool k)> st);

private:
  std::function<void(Tool k)> set_tool;

  void render_self(SDL_Renderer *renderer) override;
};
