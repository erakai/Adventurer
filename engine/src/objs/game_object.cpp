#include "objs/game_object.hpp"
#include "core/game.hpp"
#include "utils/globals.hpp"

using namespace adv;

GameObject::GameObject(Point position, int width, int height)
    : Positioned(position, {width, height}), collider(pos())
{
}

GameObject::GameObject(Rect collider)
    : Positioned(collider.tl(), {collider.width(), collider.height()}),
      collider(pos(), {{0, 0, collider.width(), collider.height()}})
{
}

void GameObject::render(SDL_Renderer *renderer, long delta, Rect viewport)
{
  update_display_position(viewport);

  if (display_pos().x() + size().w > 0 &&
      display_pos().x() < viewport.width() &&
      display_pos().y() + size().h > 0 && display_pos().y() < viewport.height())
  {
    if (globals::COLLISION_DEBUG)
    {
      collider.debug_render(renderer, display_pos());
    }

    render_self(renderer, display_pos());
  }
}

Collider GameObject::get_collider()
{
  return collider;
}

std::vector<std::shared_ptr<GameObject>> GameObject::check_collisions()
{
  return check_collisions(pos());
}

std::vector<std::shared_ptr<Positioned>> GameObject::get_possible_collisions()
{
  std::vector<std::shared_ptr<Positioned>> a =
      CURRENT_SCENE->get_moving_collision_tree()->retrieve_nearby(*this);
  std::vector<std::shared_ptr<Positioned>> b =
      CURRENT_SCENE->get_stationary_collision_tree()->retrieve_nearby(*this);

  a.insert(a.end(), b.begin(), b.end());

  return a;
}

std::vector<std::shared_ptr<GameObject>> GameObject::check_collisions(Point pos)
{
  std::vector<std::shared_ptr<Positioned>> possible_collisions =
      get_possible_collisions();

  // if (globals::COLLISION_DEBUG) logger::log("Checking against " +
  // std::to_string(possible_collisions.size()));

  std::vector<std::shared_ptr<GameObject>> actual_collisions;
  for (auto &obj : possible_collisions)
  {
    std::shared_ptr<GameObject> collideable =
        std::dynamic_pointer_cast<GameObject>(obj);
    if (collideable != nullptr && (this) != (collideable.get()) &&
        collider.check_collision(pos, collideable->get_collider()))
    {
      actual_collisions.push_back(collideable);
    }
  }

  return actual_collisions;
}
