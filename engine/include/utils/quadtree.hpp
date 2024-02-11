#pragma once

#include "objs/game_object.hpp"
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
    void insert(std::shared_ptr<GameObject> obj);
    std::vector<std::shared_ptr<GameObject>> retrieve_nearby(const GameObject obj);
  
  private:
    void split();
    int get_index(GameObject obj);
    void retrieve(std::vector<std::shared_ptr<GameObject>> &return_objs,
                  const GameObject obj);

    int level = 0;
    Rect bounds;
    std::vector<std::shared_ptr<GameObject>> objects;
    bool has_split = false;
    std::shared_ptr<QuadTree> nodes[4] = {};

};

}