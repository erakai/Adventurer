#include "objs/entity.hpp"

using namespace adv;

void Entity::update(long delta)
{
  move(delta);
}

void Entity::move(long delta)
{
  if (velocity.mag() == 0) return;
  Vector2f dir = velocity.normalized();

  float moved = (speed / 1000.0) * delta;
  dir *= moved;

  Point new_position(pos().x() + dir.x, pos().y() + dir.y);
  Point only_x(pos().x() + dir.x, pos().y());
  Point only_y(pos().x(), pos().y() + dir.y);
  if (check_collisions(new_position).size() == 0)
  {
    pos().x(pos().x() + dir.x);
    pos().y(pos().y() + dir.y);
  }
  else if (check_collisions(only_x).size() == 0)
  {
    pos().x(pos().x() + dir.x);
  }
  else if ( check_collisions(only_y).size() == 0)
  {
    pos().y(pos().y() + dir.y);
  }

};

Vector2f& Entity::vel()
{
  return velocity;
}