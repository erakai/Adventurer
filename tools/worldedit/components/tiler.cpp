#include "tiler.hpp"
#include "core/game.hpp"
#include "core/input.hpp"
#include "utils/globals.hpp"
#include "utils/logger.hpp"

using namespace adv;

Tiler::Tiler(Dimension world_size)
    : UINode({0, 0}, {1640, 940}), world_size(world_size)
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

  adjust_zoom(0);
  world_pos = {0, 0};
};

void Tiler::render_self(SDL_Renderer *renderer)
{
  // draw hovered tile
  Point hover_coords = display_coords_to_tile(mouse_pos);
  if (selected_tile.valid && mouse_pos.x() > 0 && hover_coords.x() >= 0)
  {
    Texture tex =
        adv::CURRENT_SCENE->res()->textures[selected_tile.texture_name];
    tex.set_color(hover_color_tint);

    tex.render(
        renderer,
        {static_cast<int>(hover_coords.x() * tile_size.x + world_pos.x()),
         static_cast<int>(hover_coords.y() * tile_size.y + world_pos.y()),
         tile_size.to_dimension()},
        selected_tile.sprite_name);

    tex.reset_color();
  }

  // draw each tile within viewport to zoom
  Point tl = display_coords_to_tile({0, 0});
  Point br = {tl.x() + displayed_tiles.x(), tl.y() + displayed_tiles.y()};

  if (tl.x() < 0)
    tl.x(0);
  if (tl.y() < 0)
    tl.y(0);

  if (br.x() >= world_size.w)
    br.x(world_size.w);
  if (br.y() >= world_size.h)
    br.y(world_size.h);

  for (int y = tl.y(); y < br.y() + 1; y++)
  {
    for (int x = tl.x(); x < br.x() + 1; x++)
    {
      if (y >= tiles.size())
        continue;

      if (x >= tiles[y].size())
        continue;

      uint8_t t = tiles[y][x];

      if (t == 0)
        continue;

      Tile tile = id_tile_map[t];
      if (!tile.valid)
        continue;

      if (hover_coords.x() == x && hover_coords.y() == y)
        continue;

      int display_x = (x - tl.x()) * tile_size.x + world_pos.x();
      int display_y = (y - tl.y()) * tile_size.y + world_pos.y();

      adv::CURRENT_SCENE->res()->textures[tile.texture_name].render(
          renderer, adv::Rect(display_x, display_y, tile_size.to_dimension()),
          tile.sprite_name);
    }
  }

  // draw border of world
  SDL_Rect outline_rect = {world_pos.x(), world_pos.y(),
                           static_cast<int>(tile_size.x * world_size.w),
                           static_cast<int>(tile_size.y * world_size.h)};
  SDL_SetRenderDrawColor(renderer, outline_color.r, outline_color.g,
                         outline_color.b, outline_color.opacity);
  SDL_RenderDrawRect(renderer, &outline_rect);

  // draw grid
}

void Tiler::handle_mouse_input(input::MouseEventType m, int mouse_x,
                               int mouse_y)
{
  if (mouse_x > size().w)
  {
    return;
  }

  if (m == input::LEFT_MOUSE_BUTTON_DRAG)
  {
    Point delta = {mouse_x - mouse_pos.x(), mouse_y - mouse_pos.y()};
    pan(delta);
  }

  mouse_pos.x(mouse_x);
  mouse_pos.y(mouse_y);

  if (m == input::LEFT_MOUSE_BUTTON_PRESS)
  {
    lmb_pressed_at.x = static_cast<float>(mouse_x);
    lmb_pressed_at.y = static_cast<float>(mouse_y);
  }

  if (m == input::LEFT_MOUSE_BUTTON_RELEASE)
  {
    if (lmb_pressed_at.x >= 0 &&
        lmb_pressed_at.dist_to(
            {static_cast<float>(mouse_x), static_cast<float>(mouse_y)}) < 25)
    {
      place_tile(selected_tile, mouse_x, mouse_y);
      lmb_pressed_at.x = -1;
    }
  }

  if (m == input::MOUSE_WHEEL_DOWN)
    adjust_zoom(-0.15);

  if (m == input::MOUSE_WHEEL_UP)
    adjust_zoom(0.15);
}

void Tiler::place_tile(Tile tile, int mouse_x, int mouse_y)
{
  if (!tile_id_map.contains(tile))
  {
    int id = max_tile_id++;
    tile_id_map[tile] = id;
    id_tile_map[id] = tile;
  }

  Point tile_coords = display_coords_to_tile({mouse_x, mouse_y});
  if (tile_coords.x() < 0 || tile_coords.y() < 0)
    return;
  tiles[tile_coords.y()][tile_coords.x()] = tile_id_map[tile];
}

Point Tiler::display_coords_to_tile(Point coords)
{
  int tile_x = static_cast<int>((coords.x() - world_pos.x()) / tile_size.x);
  int tile_y = static_cast<int>((coords.y() - world_pos.y()) / tile_size.x);

  if (tile_x < 0 || tile_x > world_size.w)
    return {-1, -1};
  if (tile_y < 0 || tile_y > world_size.h)
    return {-1, -1};

  return {tile_x, tile_y};
}

void Tiler::set_selected_tile(Tile tile)
{
  selected_tile = tile;
}

void Tiler::pan(Point delta)
{
  world_pos += delta;
}

void Tiler::adjust_zoom(float am)
{
  zoom_level = zoom_level + am;

  if (zoom_level < min_zoom)
    zoom_level = min_zoom;
  if (zoom_level > max_zoom)
    zoom_level = max_zoom;

  tile_size = {zoom_level * globals::TILE_SIZE,
               zoom_level * globals::TILE_SIZE};

  int display_tile_width = size().w / tile_size.x;
  int display_tile_height = size().h / tile_size.y;
  displayed_tiles = {display_tile_width, display_tile_height};
}

void Tiler::read(std::string filepath){};
void Tiler::write(std::string filepath){};
