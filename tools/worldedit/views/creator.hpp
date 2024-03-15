#pragma once

#include "display/ui_node.hpp"

#include <string>

class Creator : public adv::UINode
{
public:
  Creator();

  void transition_to_editor();

private:
  std::string path_to_assets;
  std::string name_of_world;
  int tile_width, tile_height;

  void render_self(SDL_Renderer *renderer) override;
};
