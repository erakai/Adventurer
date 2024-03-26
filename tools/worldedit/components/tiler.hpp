#pragma once

#include "core/input.hpp"
#include "display/ui_node.hpp"
#include "utils/color.hpp"
#include "utils/point.hpp"
#include "utils/serializable.hpp"
#include "utils/vector2f.hpp"
#include "world/tile_resource.hpp"

#include <unordered_map>
#include <vector>

using namespace adv;

enum class Tool
{
  PAN,
  PLACE,
};

class Tiler : public UINode, public Serializable
{
public:
  Tiler(Dimension world_size);

  void place_tile(Tile tile, int mouse_x, int mouse_y);

  void set_tool(Tool tool);
  void set_selected_tile(Tile tile);
  void adjust_zoom(float am);
  void pan(int mouse_x, int mouse_y);

  void handle_mouse_input(input::MouseEventType m, int mouse_x, int mouse_y);

  void read(std::string filepath) override;
  void write(std::string filepath) override;

  float zoom_level = 0;
  float min_zoom = 0.02;
  float max_zoom = 10;

  bool show_grid = true;
  Color outline_color = {235, 177, 19};
  Color hover_color_tint = {255, 255, 255, 150};
  Color grid_color = {237, 228, 173, 100};

private:
  Point mouse_pos = {0, 0};

  Point world_pos;
  Dimension world_size;
  Vector2f tile_size;
  float effective_zoom = -1;

  Tile selected_tile = {"tiles", "floor", false, true};
  Tool selected_tool = Tool::PAN;

  // We need a way to associate tiles and their ids with each other on the fly
  // This is a (really) really bad way to implement a "bimap"
  std::vector<std::vector<uint8_t>> tiles;
  std::unordered_map<uint8_t, Tile> id_tile_map;
  std::unordered_map<Tile, uint8_t> tile_id_map;
  uint8_t max_tile_id = 1;

  void render_self(SDL_Renderer *renderer) override;
  Point display_coords_to_tile(Point coords);
};
