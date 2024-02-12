#pragma once

#include "box.hpp"

#include <iostream>

class Player: public Box
{
  public:
    Player(adv::Point pos, adv::Color color, int side_length);

    void handle_input(adv::input::KeyEventType e);

};