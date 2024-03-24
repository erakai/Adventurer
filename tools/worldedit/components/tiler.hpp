#pragma once

#include "core/input.hpp"
#include "display/ui_node.hpp"
#include "utils/point.hpp"
#include "utils/serializable.hpp"
#include "utils/vector2f.hpp"
#include "world/tile_resource.hpp"

#include <unordered_map>
#include <vector>

using namespace adv;

class Tiler : public UINode, public Serializable
{
public:
  Tiler(Dimension world_size);

  void place_tile(Tile tile, int mouse_x, int mouse_y);

  void set_selected_tile(Tile tile);
  void adjust_zoom(bool mouse_down);
  void adjust_center(Point delta);

  void handle_mouse_input(input::MouseEventType m, int mouse_x, int mouse_y);

  Vector2f tile_size();

  void read(std::string filepath) override;
  void write(std::string filepath) override;

  float zoom_level = 1;
  bool show_grid = true;

private:
  Point camera_center = {0, 0};
  Point mouse_pos = {0, 0};
  Dimension world_size;

  Tile selected_tile;

  // We need a way to associate tiles and their ids with each other on the fly
  // This is a really bad way to implement a "bimap"
  std::vector<std::vector<uint8_t>> tiles;
  std::unordered_map<uint8_t, Tile> id_tile_map;
  std::unordered_map<Tile, uint8_t> tile_id_map;
  uint8_t max_tile_id = 0;

  void render_self(SDL_Renderer *renderer) override;
};
