#include "objs/entity.hpp"

#include <iostream>

using namespace adv;

Entity::Entity(int speed) : speed(speed)
{
}

void Entity::update(long delta)
{
  move(delta);
}

void Entity::move(long delta)
{
  Vector2f dir = velocity.normalized();

  dir *= speed;

  pos().x(pos().x() + dir.x);
  pos().y(pos().y() + dir.y);
};

Vector2f& Entity::vel()
{
  return velocity;
}