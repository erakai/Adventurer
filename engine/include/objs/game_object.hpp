#pragma once

#include "collider.hpp"
#include "core/node.hpp"
#include "utils/point.hpp"
#include "utils/globals.hpp"

#include <vector>

namespace adv
{

class GameObject: public Node
{
  public:
    GameObject() : collider(position) {}
    GameObject(Rect rect);
    GameObject(Point pos);
    virtual ~GameObject() {}

    std::vector<GameObject> check_collision(GameObject obj);
    std::vector<GameObject> check_collision(Point pos, GameObject obj);

    Point& pos();
    Point& display_pos();
    void update_display_position(Rect camera_pos);

  private:
    Point position;
    Point display_position;

    Collider collider;
};

};