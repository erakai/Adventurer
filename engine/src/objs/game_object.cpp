#include "objs/game_object.hpp"

using namespace adv;

GameObject::GameObject(Point position, int width, int height) :
  Positioned(position, Rect(0, 0, width, height)), collider(pos())
{
}

GameObject::GameObject(Rect rect) :
  Positioned(rect.tl(), Rect(0, 0, rect.width(), rect.height())),
  collider(pos(), { {0, 0, rect.width(), rect.height() } })
{
}

Collider GameObject::get_collider()
{
  return collider;
}

void GameObject::set_quadtrees(std::shared_ptr<QuadTree> moving, std::shared_ptr<QuadTree> stationary)
{
  moving_tree = moving;
  stationary_tree = stationary;
}

std::vector<std::shared_ptr<GameObject>> GameObject::check_collisions()
{
  return check_collisions(pos());
}

std::vector<std::shared_ptr<Positioned>> GameObject::get_possible_collisions()
{
  std::vector<std::shared_ptr<Positioned>> a = moving_tree->retrieve_nearby(*this);
  std::vector<std::shared_ptr<Positioned>> b = stationary_tree->retrieve_nearby(*this);

  a.insert(a.end(), b.begin(), b.end());

  return a; 
}

std::vector<std::shared_ptr<GameObject>> GameObject::check_collisions(Point pos)
{
  std::vector<std::shared_ptr<Positioned>> possible_collisions = get_possible_collisions();

  //if (globals::COLLISION_DEBUG) logger::log("Checking against " + std::to_string(possible_collisions.size()));
  
  std::vector<std::shared_ptr<GameObject>> actual_collisions;
  for (auto &obj: possible_collisions)
  {
    std::shared_ptr<GameObject> collideable = std::dynamic_pointer_cast<GameObject>(obj);
    if (collideable != nullptr &&
        (this) != (collideable.get()) &&
        collider.check_collision(pos, collideable->get_collider()))
    {
      actual_collisions.push_back(collideable);
    }
  }

  return actual_collisions;
}