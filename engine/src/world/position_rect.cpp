#include "world/position_rect.hpp"

using namespace adv;

int PositionRect::x() const
{
  return _x;
}

int PositionRect::y() const
{
  return _y;
}

void PositionRect::x(int new_x)
{
  _x = new_x;
}

void PositionRect::y(int new_y)
{
  _y = new_y;
}

int PositionRect::width()
{
  return _width;
}

int PositionRect::height()
{
  return _height;
}

void PositionRect::width(int new_width)
{
  _width = new_width;
}

void PositionRect::height(int new_height)
{
  _height = new_height;
}


bool PositionRect::valid()
{
  return _valid;
}

void PositionRect::toggle_valid()
{
  _valid = !_valid;
}