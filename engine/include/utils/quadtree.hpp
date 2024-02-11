#pragma once

#include "objs/game_object.hpp"
#include "globals.hpp"
#include "rect.hpp"

#include <vector>
#include <memory>

namespace adv
{

// https://code.tutsplus.com/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374t
class QuadTree  
{
  public:
    QuadTree(Rect bounds);
    QuadTree(int level, Rect bounds);

    void clear();
    void insert(std::shared_ptr<GameObject> obj);
    std::vector<std::shared_ptr<GameObject>> retrieve_nearby(std::shared_ptr<GameObject> obj);
  
  private:
    void split();
    int getIndex(std::shared_ptr<GameObject> obj);
    std::vector<std::shared_ptr<GameObject>> retrieve(std::vector<std::shareD_ptr<GameObject>> return_objs,
                                                      std::shared_ptr<GameObject> obj);

    Rect bounds;
    int level;
    std::vector<std::shared_ptr<GameObject>> objects;
    QuadTree nodes[4];

};

}