#pragma once

#include "objs/entity.hpp"
#include "core/input.hpp"

#include <iostream>

class Player: public adv::Entity
{
  public:
    Player(int side_length);

    void render(SDL_Renderer* renderer, long delta, adv::Rect viewport) override;
    void handle_input(adv::input::KeyEventType e);

  private:
    int side_length;
};