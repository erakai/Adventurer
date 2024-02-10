#pragma once

#include "collider.hpp"
#include "core/node.hpp"
#include "world/position_rect.hpp"
#include "utils/globals.hpp"

namespace adv
{

class GameObject: public Node
{
  public:
    GameObject() : collider(position) {}
    GameObject(PositionRect pos);
    virtual ~GameObject() {}

    virtual bool check_collision(GameObject obj) {
      return collider.check_collision(obj.collider);
    };

    PositionRect& pos();
    PositionRect& display_pos();
    void update_display_position(PositionRect camera_pos);

  private:
    PositionRect position;
    PositionRect display_position;

    Collider collider;
};

};