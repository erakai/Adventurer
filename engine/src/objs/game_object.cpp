#include "objs/game_object.hpp"

using namespace adv;

GameObject::GameObject(Point pos) :
  position(pos), display_position(pos), collider(position)
{
  update_display_position(Rect(0, 0, 0, 0));
}

GameObject::GameObject(Rect rect) :
  position(rect.tl()), display_position(rect.tl()),
  collider(position, { {0, 0, rect.width(), rect.height() } })
{
  update_display_position(Rect(0, 0, 0, 0));
}

Point& GameObject::pos()
{
  return position;
}

Point& GameObject::display_pos()
{
  return display_position;
}

Collider GameObject::get_collider()
{
  return collider;
}

void GameObject::set_quadtree(std::shared_ptr<QuadTree> quadtree)
{
  parent_quadtree = quadtree;
}

void GameObject::update_display_position(Rect camera_pos)
{
  display_position.x((position.x() - camera_pos.x1()) / globals::WORLD_DIST_PER_DISPLAY_PIXEL);
  display_position.y((position.y() - camera_pos.y1()) / globals::WORLD_DIST_PER_DISPLAY_PIXEL);
}

std::vector<std::shared_ptr<GameObject>> GameObject::check_collisions()
{
  return check_collisions(pos());
}

std::vector<std::shared_ptr<GameObject>> GameObject::check_collisions(Point pos)
{
  std::vector<std::shared_ptr<GameObject>> possible_collisions =
    parent_quadtree->retrieve_nearby(*this);

  std::vector<std::shared_ptr<GameObject>> actual_collisions;
  for (auto &obj: possible_collisions)
  {
    if (collider.check_collision(pos, obj->get_collider()))
    {
      actual_collisions.push_back(obj);
    }
  }

  return actual_collisions;
}