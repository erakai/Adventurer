#include "objs/collider.hpp"

using namespace adv;

bool Collider::check_collision(Collider other)
{
  if (!can_collide() || !other.can_collide()) return false;
  if (layer() != other.layer()) return false;

  for (auto& first_box: boxes())
  {
    BoundingBox box = adjust_to_owner(first_box);
    for (auto& second_box: other.boxes())
    {
      BoundingBox box2 = other.adjust_to_owner(second_box);
      bool collision = (box.x2 >= box2.x && box2.x2 >= box.x) &&
                       (box.y2 >= box2.y && box2.y2 >= box.y);
      if (collision) return collision;
    }
  }

  return false;
}

BoundingBox Collider::adjust_to_owner(BoundingBox box)
{
  return {
    box.x + owner_pos.x(),
    box.y + owner_pos.y(),
    box.x2 + owner_pos.x(),
    box.y2 + owner_pos.y()
  };
}

Collider& Collider::add_box(BoundingBox box)
{
  _boxes.push_back(box);
  return (*this);
}

std::vector<BoundingBox> Collider::boxes()
{
  return _boxes;
}

int Collider::layer()
{
  return _layer;
}

bool Collider::can_collide() 
{
  return _can_collide;
}

void Collider::toggle_can_collide()
{
  _can_collide = !_can_collide;
}