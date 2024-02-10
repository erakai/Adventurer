#pragma once

namespace adv
{

/*
Can act as both a point and a rectangle

When used as a viewport, (x,y) is world position of camera, (width, height) is display bounds
*/
class PositionRect
{
  public:
    PositionRect() {}
    PositionRect(int x, int y) : _x(x), _y(y) {}
    PositionRect(int x, int y, int width, int height) : 
      _x(x), _y(y), _width(width), _height(height) {}
    PositionRect(const PositionRect& pos) :
      _x(pos._x), _y(pos._y), _width(pos._width), _height(pos._height) {}

    int x() const;
    int y() const;
    void x(int new_x);
    void y(int new_y);

    int width();
    int height();
    void width(int new_width);
    void height(int new_height);

    bool valid();
    void toggle_valid();

  private:
    int _x;
    int _y;
    int _width;
    int _height;

    bool _valid = true;

};

};