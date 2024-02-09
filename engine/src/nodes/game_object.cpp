#include "nodes/game_object.hpp"
#include "utils/globals.hpp"

using namespace adv;

GameObject::GameObject(PositionRect pos) : position(pos), display_position(pos)
{
  display_position.x(display_position.x() / globals::WORLD_DIST_PER_DISPLAY_PIXEL);
  display_position.y(display_position.y() / globals::WORLD_DIST_PER_DISPLAY_PIXEL);
}

PositionRect& GameObject::pos()
{
  return position;
}

PositionRect& GameObject::display_pos()
{
  return display_position;
}

void GameObject::update_display_position(PositionRect camera_pos)
{
  display_position.x((position.x() - camera_pos.x()) / globals::WORLD_DIST_PER_DISPLAY_PIXEL);
  display_position.y((position.y() - camera_pos.y()) / globals::WORLD_DIST_PER_DISPLAY_PIXEL);
}