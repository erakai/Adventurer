#pragma once

#include <ostream>

namespace adv
{

class Point
{
public:
  Point() {}
  Point(int x, int y) : _x(x), _y(y) {}
  Point(const Point &pos) : _x(pos._x), _y(pos._y) {}

  int x() const { return _x; }
  int y() const { return _y; }
  void x(int new_x) { _x = new_x; }
  void y(int new_y) { _y = new_y; }

  bool operator==(const Point &rhs) const
  {
    return _x == rhs._x && _y == rhs._y;
  }

  Point operator+=(const Point a)
  {
    _x += a._x;
    _y += a._y;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const Point &v)
  {
    os << "(" << v.x() << ", " << v.y() << ")";
    return os;
  }

private:
  int _x;
  int _y;
};

} // namespace adv
