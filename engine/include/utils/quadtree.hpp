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