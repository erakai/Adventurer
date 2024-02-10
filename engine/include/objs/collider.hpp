#pragma once

#include "world/position_rect.hpp"

#include <vector>

namespace adv
{

struct BoundingBox
{
  int x;
  int y;
  int x2;
  int y2;
};

class Collider
{
  public:
    Collider(PositionRect& pos) :
      owner_pos(pos) {}
    Collider(PositionRect& pos, std::vector<BoundingBox> boxes) :
      owner_pos(pos), _boxes(boxes) {}
    Collider(PositionRect& pos, int layer) :
      owner_pos(pos), _layer(layer) {}
    Collider(PositionRect& pos, int layer, std::vector<BoundingBox> boxes) : 
      owner_pos(pos), _layer(layer), _boxes(boxes) {}

    bool check_collision(Collider other);
    BoundingBox adjust_to_owner(BoundingBox box);

    std::vector<BoundingBox> boxes();
    int layer();
    bool can_collide();

    void toggle_can_collide();
    Collider& add_box(BoundingBox box);

  private:
    const PositionRect& owner_pos;

    int _layer = 1;
    bool _can_collide = true;
    std::vector<BoundingBox> _boxes;


};

}