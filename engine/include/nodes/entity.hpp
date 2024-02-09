#pragma once

#include "game_object.hpp"
#include "utils/vector2f.hpp"

#include "SDL.h"

namespace adv
{

class Entity: public GameObject
{
  public:
    Entity() {}
    Entity(int speed);
    virtual ~Entity() {}

    void move(long delta);
    void update(long delta) override;
    Vector2f& vel();

  private:
    int speed;
    Vector2f velocity;

};

};