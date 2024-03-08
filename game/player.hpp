#pragma once

#include "core/input.hpp"
#include "objs/entity.hpp"

class Player : public adv::Entity
{
public:
  Player(int speed, adv::Point pos);
  void handle_input(adv::input::KeyEventType e);

  void render_self(SDL_Renderer *renderer, adv::Point draw_pos) override;
};
