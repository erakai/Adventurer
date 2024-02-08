#pragma once

#include "game_object.hpp"
#include "utils/vector2f.hpp"

namespace adv
{

class Entity: public GameObject
{
  public:

  private:
    int speed;
    Vector2f velocity;

};

};