#pragma once

#include "utils/point.hpp"

#include <vector>

namespace adv
{

struct BoundingBox {
  int x;
  int y;
  int x2;
  int y2;
};

class Collider
{
public:
  Collider(Point &pos) : owner_pos(pos) {}
  Collider(Point &pos, std::vector<BoundingBox> boxes)
      : owner_pos(pos), _boxes(boxes)
  {
  }
  Collider(Point &pos, int layer) : owner_pos(pos), _layer(layer) {}
  Collider(Point &pos, int layer, std::vector<BoundingBox> boxes)
      : owner_pos(pos), _layer(layer), _boxes(boxes)
  {
  }

  bool check_collision(Collider other);
  bool check_collision(Point my_pos, Collider other);

  BoundingBox adjust_box(BoundingBox box, const Point pos);
  BoundingBox adjust_box_to_owner(BoundingBox box);

  std::vector<BoundingBox> boxes();
  int layer();
  bool can_collide();

  void toggle_can_collide();
  Collider &add_box(BoundingBox box);

private:
  const Point &owner_pos;

  int _layer = 1;
  bool _can_collide = true;
  std::vector<BoundingBox> _boxes;
};

} // namespace adv
