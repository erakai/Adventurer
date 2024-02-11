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
    Entity(int speed) : speed(speed) {} ;
    Entity(int speed, Rect rect) : GameObject(rect), speed(speed) {};
    virtual ~Entity() {}

    void move(long delta);
    void update(long delta) override;
    Vector2f& vel();

  private:
    // speed is how many world pixels you can move per second
    int speed;

    Vector2f velocity;

};

};