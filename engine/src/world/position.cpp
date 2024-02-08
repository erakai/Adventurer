#include "world/position.hpp"

using namespace adv;

int Position::x()
{
  return _x;
}

int Position::y()
{
  return _y;
}

void Position::x(int new_x)
{
  _x = new_x;
}

void Position::y(int new_y)
{
  _y = new_y;
}

bool Position::valid()
{
  return _valid;
}

void Position::toggle_valid()
{
  _valid = !_valid;
}