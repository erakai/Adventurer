#pragma once

#include "objs/positioned.hpp"
#include "globals.hpp"
#include "rect.hpp"
#include "globals.hpp"
#include "logger.hpp"

#include <vector>
#include <memory>

namespace adv
{

// https://code.tutsplus.com/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374t
class QuadTree  
{
  public:
    QuadTree(Rect bounds) : bounds(bounds) {};
    QuadTree(int level, Rect bounds) :
      level(level), bounds(bounds) {};

    void clear();
    void insert(std::shared_ptr<Positioned> obj);
    std::vector<std::shared_ptr<Positioned>> retrieve_nearby(const Positioned obj);

    void debug_render(SDL_Renderer* renderer, long delta, Rect viewport) {
      SDL_Rect outlineRect = { bounds.x1() / 10, bounds.y1() / 10, bounds.width() / 10, bounds.height() / 10 };
      SDL_SetRenderDrawColor( renderer , 0x00, 0xFF, 0x00, 0xFF );        
      SDL_RenderDrawRect( renderer, &outlineRect );

      if (has_split)
      {
        for (auto &n: nodes) n->debug_render(renderer, delta, viewport);
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

}