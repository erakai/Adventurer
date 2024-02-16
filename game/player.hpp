#pragma once

#include "box.hpp"

#include <string>
#include <iostream>

class Player: public Box
{
  public:
    Player(int speed, adv::Point pos, adv::Color color, int side_length);

    void handle_input(adv::input::KeyEventType e);
    void update(long delta) override;

};