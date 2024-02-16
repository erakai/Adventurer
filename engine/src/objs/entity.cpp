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
  if (check_collisions(new_position).size() == 0)
  {
    pos().x(pos().x() + dir.x);
    pos().y(pos().y() + dir.y);
    return;
  }

  Point only_x(pos().x() + dir.x, pos().y());
  Point only_y(pos().x(), pos().y() + dir.y);
  auto x_objs = check_collisions(only_x);
  auto y_objs = check_collisions(only_y);

  if (x_objs.size() == 0)
  {
    pos().x(pos().x() + dir.x);
  }

  if (y_objs.size() == 0)
  {
    pos().y(pos().y() + dir.y);
  }

  // TODO: Make these checks use bounding boxes instead of the other object's general size rect
  // if (x_objs.size() > 0)
  // {
  //   if (dir.x < 0)
  //   {
  //     int max_x = 0;
  //     for (auto &obj: x_objs)
  //     {
  //       int new_pos = (pos().x() - (obj->pos().x() + obj->size().width()));
  //       if (max_x == 0 || new_pos < max_x) max_x = new_pos;
  //     }

  //     if (max_x != 0) pos().x(pos().x() - max_x);
  //   }
  //   else if (dir.x > 0)
  //   {
  //     int min_x = 0;
  //     for (auto &obj: x_objs)
  //     {
  //       int new_pos = (obj->pos().x() - (pos().x() + size().width()));
  //       if (min_x == 0 || new_pos < min_x) min_x = new_pos;
  //     }

  //     if (min_x != 0) pos().x(pos().x() + min_x);
  //   }
  // }

  // if (y_objs.size() > 0)
  // {
  //   if (dir.y < 0)
  //   {
  //     int max_y = 0;
  //     for (auto &obj: y_objs)
  //     {
  //       int new_pos = (pos().y() - (obj->pos().y() + obj->size().height()));
  //       if (max_y == 0 || new_pos < max_y) max_y = new_pos;
  //     }

  //     if (max_y != 0) pos().y(pos().y() - max_y);
  //   }
  //   else if (dir.y > 0)
  //   {
  //     int min_y = 0;
  //     for (auto &obj: y_objs)
  //     {
  //       int new_pos = (obj->pos().y() - (pos().y() + size().height()));
  //       if (min_y == 0 || new_pos < min_y) min_y = new_pos;
  //     }

  //     if (min_y != 0) pos().y(pos().y() + min_y);
  //   }
  // }

};

Vector2f& Entity::vel()
{
  return velocity;
}