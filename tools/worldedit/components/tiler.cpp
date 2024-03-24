#include "tiler.hpp"
#include "core/input.hpp"
#include "utils/globals.hpp"

using namespace adv;

Tiler::Tiler(Dimension world_size)
    : UINode({0, 0}, {1200, 940}), world_size(world_size)
{
  if (world_size.h % globals::TILES_PER_CHUNK != 0 ||
      world_size.w % globals::TILES_PER_CHUNK != 0)
  {
    throw std::invalid_argument("World size must be divisible by chunk size");
  }

  tiles.resize(world_size.h);
  for (auto &v : tiles)
  {
    v.resize(world_size.w);
  }

  std::function<void(input::MouseEventType m, int mouse_x, int mouse_y)> input =
      [this](input::MouseEventType m, int x, int y)
  { handle_mouse_input(m, x, y); };
  input::mouse_hook(input);
};

void Tiler::render_self(SDL_Renderer *renderer)
{
  // draw border of world

  // draw each tile within viewport to zoom

  // draw hovered tile

  // draw grid
}

void Tiler::handle_mouse_input(input::MouseEventType m, int mouse_x,
                               int mouse_y)
{
  mouse_pos.x(mouse_x);
  mouse_pos.y(mouse_y);

  if (m == input::LEFT_MOUSE_BUTTON_RELEASE)
    place_tile(selected_tile, mouse_x, mouse_y);
}

void Tiler::place_tile(Tile tile, int mouse_x, int mouse_y)
{
  if (!tile_id_map.contains(tile))
  {
    int id = max_tile_id++;
    tile_id_map[tile] = id;
    id_tile_map[id] = tile;
  }

  Vector2f tile_dim = tile_size();
  int tile_x = static_cast<int>((mouse_x - pos().x()) / tile_dim.x);
  int tile_y = static_cast<int>((mouse_y - pos().y()) / tile_dim.x);

  if (tile_x < 0 || tile_x > world_size.w)
    return;
  if (tile_y < 0 || tile_y > world_size.h)
    return;

  tiles[tile_y][tile_x] = tile_id_map[tile];
}

void Tiler::set_selected_tile(Tile tile)
{
  selected_tile = tile;
}

void Tiler::adjust_center(Point delta)
{
  camera_center += delta;
}

void Tiler::adjust_zoom(bool mouse_down)
{
  zoom_level = zoom_level + (1 ? mouse_down : -1);
}

Vector2f Tiler::tile_size()
{
  return {zoom_level * globals::TILE_SIZE, zoom_level * globals::TILE_SIZE};
}

void Tiler::read(std::string filepath){};
void Tiler::write(std::string filepath){};
