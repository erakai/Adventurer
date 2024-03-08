#pragma once

#include "utils/globals.hpp"
#include "utils/point.hpp"
#include "utils/rect.hpp"

namespace adv
{

class Positioned
{
public:
  Positioned() : position(Point(0, 0)), display_position(Point(0, 0)) {}
  Positioned(Point pos) : position(pos), display_position(Point(0, 0))
  {
    update_display_position(Rect(0, 0, 0, 0));
  }
  Positioned(Point pos, Dimension size) : position(pos), size_dim(size)
  {
    update_display_position(Rect(0, 0, 0, 0));
  }

  virtual ~Positioned() {}

  Point &pos() { return position; }
  Point center() const
  {
    return Point(position.x() + size_dim.w / 2, position.y() + size_dim.h / 2);
  }

  Point &display_pos() { return display_position; }

  Dimension &size() { return size_dim; }
  Dimension display_size()
  {
    return {size().w / globals::SUBPIXELS, size().h / globals::SUBPIXELS};
  }

  void update_display_position(Rect camera_pos)
  {
    display_position.x((position.x() - camera_pos.x1()) / globals::SUBPIXELS);
    display_position.y((position.y() - camera_pos.y1()) / globals::SUBPIXELS);
  }

private:
  Point position;
  Point display_position;

  Dimension size_dim;
};

} // namespace adv
