#pragma once

#include "node.hpp"
#include "world/position_rect.hpp"

namespace adv
{

class GameObject: public Node
{
  public:
    GameObject() {}
    GameObject(PositionRect pos);
    virtual ~GameObject() {}

    // https://gamedev.stackexchange.com/questions/74858/how-can-i-improve-my-collision-detections-performance
    virtual bool check_collision(GameObject obj) {
      return false;
    };

    PositionRect& pos();
    PositionRect& display_pos();
    void update_display_position(PositionRect camera_pos);

  private:
    PositionRect position;
    PositionRect display_position;

};

};