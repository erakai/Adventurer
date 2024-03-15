#pragma once

#include "display/ui_node.hpp"
#include <string>

class Sidebar : public adv::UINode
{
public:
  Sidebar();

  void load_assets(std::string filepath);

private:
  void render_self(SDL_Renderer *renderer) override;
};
