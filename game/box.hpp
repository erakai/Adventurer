#pragma once

#include "objs/entity.hpp"
#include "utils/color.hpp"
#include "utils/point.hpp"

class Box : public adv::Entity
{
public:
  Box(int speed, adv::Point pos, adv::Color color, int side_length);

  void render_self(SDL_Renderer *renderer, adv::Point draw_pos) override;

private:
  int side_length;
  adv::Color color;
};
