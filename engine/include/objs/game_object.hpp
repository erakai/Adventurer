#pragma once

#include "collider.hpp"
#include "core/node.hpp"
#include "utils/point.hpp"
#include "utils/quadtree.hpp"
#include "world/positioned.hpp"

#include <memory>
#include <vector>

namespace adv
{

class GameObject : public Node, public Positioned
{
public:
  GameObject() : collider(pos()) {}
  GameObject(Point position, int width, int height);
  GameObject(Rect rect);
  virtual ~GameObject() {}

  void render(SDL_Renderer *renderer, long delta, Rect viewport) override;
  virtual void render_self(SDL_Renderer *renderer, Point draw_pos) = 0;

  std::vector<std::shared_ptr<GameObject>> check_collisions();
  std::vector<std::shared_ptr<GameObject>> check_collisions(Point pos);

  Collider get_collider();
  void set_quadtrees(std::shared_ptr<QuadTree> moving,
                     std::shared_ptr<QuadTree> stationary);
  std::vector<std::shared_ptr<Positioned>> get_possible_collisions();

private:
  Collider collider;

  std::shared_ptr<QuadTree> moving_tree;
  std::shared_ptr<QuadTree> stationary_tree;
};

}; // namespace adv
