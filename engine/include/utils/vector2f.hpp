#pragma once

#include <cmath>

namespace adv
{

class Vector2f
{
  public:
    Vector2f() {}
    Vector2f(float x, float y) : x(x), y(y) {}
    Vector2f(const Vector2f& vec) : x(vec.x), y(vec.y) {}

    float mag() { return std::sqrt((x * x) + (y * y)); }
    float norm_x() { return x / mag(); }
    float norm_y() { return y / mag(); }
    void normalized() { x = norm_x(); y = norm_y(); }

    float dot(Vector2f other) {
      return x * other.x + y * other.y;
    }

    float x;
    float y;
};

}

