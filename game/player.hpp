#pragma once

#include "nodes/entity.hpp"
#include "core/input.hpp"

#include <iostream>

class Player: public adv::Entity
{
  public:
    Player();

    void render(SDL_Renderer* renderer, long delta, adv::PositionRect viewport) override;
    void handle_input(adv::input::KeyEventType e);
};