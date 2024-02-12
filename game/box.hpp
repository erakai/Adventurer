#pragma once

#include "objs/entity.hpp"
#include "core/input.hpp"
#include "utils/rect.hpp"
#include "utils/globals.hpp"
#include "utils/point.hpp"
#include "utils/color.hpp"

#include <iostream>

class Box: public adv::Entity
{
  public:
    Box(int speed, adv::Point pos, adv::Color color, int side_length);

    void render(SDL_Renderer* renderer, long delta, adv::Rect viewport) override;

  private:
    int side_length;
    adv::Color color;
};