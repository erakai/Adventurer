#include "objs/collider.hpp"
#include "utils/globals.hpp"

using namespace adv;

bool Collider::check_collision(Collider other)
{
  return check_collision(owner_pos, other);
}

bool Collider::check_collision(Point my_pos, Collider other)
{
  if (!can_collide() || !other.can_collide())
    return false;
  if (layer() != other.layer())
    return false;

  for (auto &first_box : boxes())
  {
    BoundingBox box = adjust_box(first_box, my_pos);
    for (auto &second_box : other.boxes())
    {
      BoundingBox box2 = other.adjust_box_to_owner(second_box);
      bool collision = (box.x2 > box2.x && box2.x2 > box.x) &&
                       (box.y2 > box2.y && box2.y2 > box.y);
      if (collision)
        return collision;
    }
  }

  return false;
}

BoundingBox Collider::adjust_box_to_owner(BoundingBox box)
{
  return adjust_box(box, owner_pos);
}

BoundingBox Collider::adjust_box(BoundingBox box, const Point pos)
{
  return {box.x + pos.x(), box.y + pos.y(), box.x2 + pos.x(), box.y2 + pos.y()};
}

Collider &Collider::add_box(BoundingBox box)
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

void Collider::debug_render(SDL_Renderer *renderer, Point draw_pos)
{
  for (auto bb : _boxes)
  {
    SDL_Rect box = {
        draw_pos.x() - 1, draw_pos.y() - 1,
        ((bb.x2 - bb.x) / globals::WORLD_DIST_PER_DISPLAY_PIXEL) + 2,
        ((bb.y2 - bb.y) / globals::WORLD_DIST_PER_DISPLAY_PIXEL) + 2};
    SDL_SetRenderDrawColor(renderer, 43, 117, 50, 50);
    SDL_RenderFillRect(renderer, &box);
  }
}
