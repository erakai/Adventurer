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
  Positioned(Point pos, Rect size) : position(pos), size_rect(size)
  {
    update_display_position(Rect(0, 0, 0, 0));
  }

  virtual ~Positioned() {}

  Point &pos() { return position; }
  Point center() const
  {
    return Point(position.x() + size_rect.width() / 2,
                 position.y() + size_rect.height() / 2);
  }

  Point &display_pos() { return display_position; }

  Rect &size() { return size_rect; }

  void update_display_position(Rect camera_pos)
  {
    display_position.x((position.x() - camera_pos.x1()) /
                       globals::WORLD_DIST_PER_DISPLAY_PIXEL);
    display_position.y((position.y() - camera_pos.y1()) /
                       globals::WORLD_DIST_PER_DISPLAY_PIXEL);
  }

private:
  Point position;
  Point display_position;

  Rect size_rect;
};

} // namespace adv
