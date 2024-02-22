#pragma once

#include <cmath>
#include <ostream>

namespace adv
{

class Vector2f
{
public:
  Vector2f() {}
  Vector2f(float x, float y) : x(x), y(y) {}
  Vector2f(const Vector2f &vec) : x(vec.x), y(vec.y) {}

  float x;
  float y;

  float mag() { return std::sqrt((x * x) + (y * y)); }
  float norm_x() { return mag() > 0 ? x / mag() : 0; }
  float norm_y() { return mag() > 0 ? y / mag() : 0; }
  void to_zero()
  {
    x = 0;
    y = 0;
  }
  void normalize()
  {
    x = norm_x();
    y = norm_y();
  }
  Vector2f normalized() { return Vector2f(norm_x(), norm_y()); }

  float dot(Vector2f other) { return x * other.x + y * other.y; }

  friend std::ostream &operator<<(std::ostream &os, const Vector2f &v)
  {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
  }

  bool operator==(const Vector2f &rhs) const
  {
    return x == rhs.x && y == rhs.y;
  }

  Vector2f operator+=(const float a)
  {
    x += a;
    y += a;
    return *this;
  }

  Vector2f operator-=(const float a)
  {
    x -= a;
    y -= a;
    return *this;
  }

  Vector2f operator*=(const float a)
  {
    x *= a;
    y *= a;
    return *this;
  }

  Vector2f operator+(const Vector2f &b) { return Vector2f(x + b.x, y + b.y); }

  Vector2f operator-(const Vector2f &b) { return Vector2f(x - b.x, y - b.y); }

  Vector2f operator*(const Vector2f &b) { return Vector2f(x * b.x, y * b.y); }
};

} // namespace adv
