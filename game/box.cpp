#include "box.hpp"
#include "utils/globals.hpp"

Box::Box(int speed, adv::Point pos, adv::Color color, int side_length)
    : Entity(speed, adv::Rect(pos.x(), pos.y(), pos.x() + side_length,
                              pos.y() + side_length)),
      side_length(side_length / adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL),
      color(color)
{
}

void Box::render_self(SDL_Renderer *renderer, adv::Point draw_pos)
{
  SDL_Rect fillRect = {draw_pos.x(), draw_pos.y(), side_length, side_length};
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.opacity);
  SDL_RenderFillRect(renderer, &fillRect);
}
