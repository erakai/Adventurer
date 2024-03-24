#pragma once

#include "display/ui_node.hpp"

namespace adv
{

class GlobalDebugWindow : public UINode
{
public:
  GlobalDebugWindow();

private:
  void render_self(SDL_Renderer *renderer) override;

  void handle_debug_release();

  bool visible = false;
};

} // namespace adv
