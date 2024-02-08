#pragma once

#include "node.hpp"
#include "world/position.hpp"

namespace adv
{

class Object: public Node
{
  public:
    virtual ~Object() {}

    // https://gamedev.stackexchange.com/questions/74858/how-can-i-improve-my-collision-detections-performance
    virtual bool check_collision(Object obj) {
      return false;
    };

    Position& pos();
    Position position_in_viewport(Position camera_pos);

  private:
    Position position;

};

};