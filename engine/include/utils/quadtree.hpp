#pragma once

#include "SDL_rect.h"
#include "SDL_render.h"
#include "rect.hpp"
#include "world/positioned.hpp"

#include <memory>
#include <vector>

namespace adv
{

// TODO: Optimize by not using a vector in every QuadTree node

class QuadTree
{
public:
  QuadTree(Rect world_bounds) : bounds(world_bounds){};
  QuadTree(int level, Rect world_bounds) : level(level), bounds(world_bounds){};

  void clear();
  void insert(std::shared_ptr<Positioned> obj);
  std::vector<std::shared_ptr<Positioned>>
  retrieve_nearby(const Positioned obj);

  void debug_render(SDL_Renderer *renderer, long delta, Rect viewport)
  {
    SDL_Rect outline_rect = {(bounds.x1() - viewport.x1()) / globals::SUBPIXELS,
                             (bounds.y1() - viewport.y1()) / globals::SUBPIXELS,
                             bounds.width() / globals::SUBPIXELS,
                             bounds.height() / globals::SUBPIXELS};
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawRect(renderer, &outline_rect);

    if (has_split)
    {
      for (auto &n : nodes)
        n->debug_render(renderer, delta, viewport);
    }
  }

private:
  void split();
  int get_index(Positioned obj);
  void retrieve(std::vector<std::shared_ptr<Positioned>> &return_objs,
                const Positioned obj);

  int level = 0;
  Rect bounds;
  std::vector<std::shared_ptr<Positioned>> objects;
  bool has_split = false;
  std::shared_ptr<QuadTree> nodes[4] = {};
};

} // namespace adv
