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

void GameObject::update_display_position(Rect camera_pos)
{
  display_position.x((position.x() - camera_pos.x1()) / globals::WORLD_DIST_PER_DISPLAY_PIXEL);
  display_position.y((position.y() - camera_pos.y1()) / globals::WORLD_DIST_PER_DISPLAY_PIXEL);
}

std::vector<GameObject> GameObject::check_collision(GameObject obj)
{
  return check_collision(pos(), obj);
}

std::vector<GameObject> GameObject::check_collision(Point pos, GameObject obj)
{
  // hook into quadtree and use collider.check_collision()
  return {};
}