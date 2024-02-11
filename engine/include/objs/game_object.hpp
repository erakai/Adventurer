#pragma once

#include "collider.hpp"
#include "core/node.hpp"
#include "utils/point.hpp"
#include "utils/globals.hpp"

#include <vector>
#include <memory>

namespace adv
{

class GameObject: public Node
{
  public:
    GameObject() : collider(position) {}
    GameObject(Rect rect);
    GameObject(Point pos);
    virtual ~GameObject() {}

    std::vector<std::shared_ptr<GameObject>> check_collisions();
    std::vector<std::shared_ptr<GameObject>> check_collisions(Point pos);

    Point& pos();
    Point& display_pos();
    Collider get_collider();
    void set_quadtree(std::shared_ptr<QuadTree> quadtree);
    void update_display_position(Rect camera_pos);

  private:
    Point position;
    Point display_position;

    Collider collider;
    std::shared_ptr<QuadTree> parent_quadtree;
};

};