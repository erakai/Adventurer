#include "tiler.hpp"
#include "core/game.hpp"
#include "core/input.hpp"
#include "utils/globals.hpp"
#include <cmath>

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
  // Compute tile mouse is hovering over
  Point hover_coords = display_coords_to_tile(mouse_pos);

  // Compute bounds of viewport in tile coordinates
  Point tl = display_coords_to_tile({0, 0});
  Point br = display_coords_to_tile({size().w + 1, size().h + 1});

  // Begin drawing all visible tiles
  for (int y = tl.y(); y < br.y() + 1; y++)
  {
    // Draw horizontal grid lines
    if (show_grid)
    {
      SDL_SetRenderDrawColor(renderer, grid_color.r, grid_color.g, grid_color.b,
                             grid_color.opacity);
      int line_y = world_pos.y() + (y * tile_size.y);
      SDL_RenderDrawLine(
          renderer, world_pos.x(), line_y,
          world_pos.x() + static_cast<int>(tile_size.x * world_size.w), line_y);
    }

    for (int x = tl.x(); x < br.x() + 1; x++)
    {
      // Draw vertical grid lines
      if (show_grid && y == tl.y())
      {
        SDL_SetRenderDrawColor(renderer, grid_color.r, grid_color.g,
                               grid_color.b, grid_color.opacity);
        int line_x = world_pos.x() + (x * tile_size.x);
        SDL_RenderDrawLine(renderer, line_x, world_pos.y(), line_x,
                           world_pos.y() +
                               static_cast<int>(tile_size.y * world_size.h));
      }

      if (y >= static_cast<int>(tiles.size()))
        continue;

      if (x >= static_cast<int>(tiles[y].size()))
        continue;

      // Render tile to screen
      uint8_t t = tiles[y][x];

      if (t == 0)
        continue;

      Tile tile = id_tile_map[t];
      if (!tile.valid)
        continue;

      if (hover_coords.x() == x && hover_coords.y() == y)
        continue;

      int display_x = x * tile_size.x + world_pos.x();
      int display_y = y * tile_size.y + world_pos.y();

      adv::CURRENT_SCENE->res()->textures[tile.texture_name].render(
          renderer, adv::Rect(display_x, display_y, tile_size.to_dimension()),
          tile.sprite_name);
    }
  }

  // Draw transparent tile under mouse
  if (selected_tile.valid && mouse_pos.x() > 0 && hover_coords.x() >= 0 &&
      selected_tool != Tool::PAN)
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

  // Draw overall border around world
  SDL_Rect outline_rect = {world_pos.x(), world_pos.y(),
                           static_cast<int>(tile_size.x * world_size.w),
                           static_cast<int>(tile_size.y * world_size.h)};
  SDL_SetRenderDrawColor(renderer, outline_color.r, outline_color.g,
                         outline_color.b, outline_color.opacity);
  SDL_RenderDrawRect(renderer, &outline_rect);
}

void Tiler::handle_mouse_input(input::MouseEventType m, int mouse_x,
                               int mouse_y)
{
  if (mouse_x > size().w)
  {
    return;
  }

  if (m == input::MOUSE_WHEEL_DOWN)
  {
    adjust_zoom(-0.15);
    return;
  }

  if (m == input::MOUSE_WHEEL_UP)
  {
    adjust_zoom(0.15);
    return;
  }

  if (m == input::MIDDLE_MOUSE_BUTTON_DRAG)
  {
    pan(mouse_x, mouse_y);
  }

  switch (selected_tool)
  {
  case Tool::PAN:
    if (m == input::LEFT_MOUSE_BUTTON_DRAG)
      pan(mouse_x, mouse_y);
    break;
  case Tool::PLACE:
    if (m == input::LEFT_MOUSE_BUTTON_RELEASE)
      place_tile(selected_tile, mouse_x, mouse_y);
    break;
  }

  mouse_pos.x(mouse_x);
  mouse_pos.y(mouse_y);
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
  int tile_y = static_cast<int>((coords.y() - world_pos.y()) / tile_size.y);

  if (tile_x < 0)
    tile_x = 0;
  if (tile_x >= world_size.w)
    tile_x = world_size.w - 1;
  if (tile_y < 0)
    tile_y = 0;
  if (tile_y >= world_size.h)
    tile_y = world_size.h - 1;

  return {tile_x, tile_y};
}

void Tiler::set_tool(Tool tool)
{
  selected_tool = tool;
}

void Tiler::set_selected_tile(Tile tile)
{
  selected_tile = tile;
}

void Tiler::pan(int mouse_x, int mouse_y)
{
  Point delta = {mouse_x - mouse_pos.x(), mouse_y - mouse_pos.y()};
  world_pos += delta;
}

void Tiler::adjust_zoom(float am)
{
  // Sigmoid function so zooming feels natural

  float new_effective_zoom = (exp(zoom_level + am) / 1 + exp(zoom_level + am));

  if (new_effective_zoom < min_zoom)
    new_effective_zoom = min_zoom;
  if (new_effective_zoom > max_zoom)
    new_effective_zoom = max_zoom;

  if (new_effective_zoom == effective_zoom && am != 0)
    return;

  effective_zoom = new_effective_zoom;
  zoom_level = zoom_level + am;

  // Calculate what world pos needs to be for us to zoom into the mouse pos

  Vector2f new_size = {effective_zoom * globals::TILE_SIZE,
                       effective_zoom * globals::TILE_SIZE};

  world_pos.x(mouse_pos.x() -
              ((new_size.x * (mouse_pos.x() - world_pos.x())) / tile_size.x));
  world_pos.y(mouse_pos.y() -
              ((new_size.y * (mouse_pos.y() - world_pos.y())) / tile_size.y));

  tile_size = new_size;
}

void Tiler::read(std::string filepath){};
void Tiler::write(std::string filepath){};
