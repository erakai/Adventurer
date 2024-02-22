#pragma once

#include "objs/entity.hpp"
#include "utils/color.hpp"
#include "utils/point.hpp"
#include "utils/rect.hpp"

class Box : public adv::Entity
{
public:
  Box(int speed, adv::Point pos, adv::Color color, int side_length);

  void render(SDL_Renderer *renderer, long delta, adv::Rect viewport) override;

private:
  int side_length;
  adv::Color color;
};
