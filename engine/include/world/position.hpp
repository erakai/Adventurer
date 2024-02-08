#pragma once

namespace adv
{

class Position
{

  int x();
  int y();
  void x(int new_x);
  void y(int new_y);

  bool valid();
  void toggle_valid();

  private:
    int _x;
    int _y;

    bool _valid;

};

};