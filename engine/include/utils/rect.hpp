#pragma once

#include <cmath>

#include "SDL_rect.h"
#include "point.hpp"

namespace adv
{

struct Dimension
{
  int w;
  int h;
};

class Rect
{
public:
  Rect() {}
  Rect(Dimension d) : p1(0, 0), p2(d.w, d.h) {}
  Rect(Point p1, Point p2) : p1(p1), p2(p2) {}
  Rect(int x1, int y1, int x2, int y2) : p1(x1, y1), p2(x2, y2) {}
  Rect(int x1, int y1, Dimension d) : p1(x1, y1), p2(x1 + d.w, y1 + d.h) {}
  Rect(const Rect &copy) : p1(copy.p1), p2(copy.p2) {}

  Point tl() const { return p1; }
  Point br() const { return p2; }
  Point center() const { return Point(center_x(), center_y()); }

  int x1() const { return p1.x(); }
  int y1() const { return p1.y(); }
  int x2() const { return p2.x(); }
  int y2() const { return p2.y(); }

  void x1(int new_x) { p1.x(new_x); }
  void y1(int new_y) { p1.y(new_y); }
  void x2(int new_x) { p2.x(new_x); }
  void y2(int new_y) { p2.y(new_y); }

  Dimension dim() const { return {width(), height()}; }
  int width() const { return std::abs(p2.x() - p1.x()); }
  int height() const { return std::abs(p2.y() - p1.y()); }
  float center_x() const { return (x1() + (width() / 2.0)); }
  float center_y() const { return (y1() + (height() / 2.0)); }

  SDL_Rect to_sdl_rect() const { return {x1(), y1(), width(), height()}; }

  bool operator==(const Rect &rhs) const
  {
    return (p1 == rhs.p1 && p2 == rhs.p2) || (p1 == rhs.p2 && p2 == rhs.p1);
  }

private:
  Point p1;
  Point p2;
};

} // namespace adv
