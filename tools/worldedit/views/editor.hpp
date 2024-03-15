#pragma once

#include "display/ui_node.hpp"
#include "utils/serializable.hpp"
#include "world/tile_resource.hpp"

#include <unordered_set>
#include <vector>

class Editor : public adv::UINode, public adv::Serializable
{
public:
  Editor();

  void place_tile(adv::Tile tile);
  void generate_tile_resource();

  void read(std::string filepath) override;
  void write(std::string filepath) override;

private:
  bool save_dialogue_open = false;
  int tile_width, tile_height;

  std::vector<std::vector<adv::Tile>> tiles;

  // https://stackoverflow.com/questions/50888127/how-can-i-use-an-unordered-set-with-a-custom-struct
  std::unordered_set<adv::Tile> tiles_in_use;

  void render_self(SDL_Renderer *renderer) override;
};
