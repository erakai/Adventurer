#include "box.hpp"

Box::Box(adv::Point pos, adv::Color color, int side_length) :
  Entity(1500, adv::Rect(pos.x(), pos.y(), pos.x() + side_length, pos.y() + side_length)),
  side_length(side_length / adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL),
  color(color)
{
}

void Box::render(SDL_Renderer* renderer, long delta, adv::Rect viewport)
{
  update_display_position(viewport);

  SDL_Rect fillRect = { display_pos().x(), display_pos().y(), side_length, side_length };
  SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.opacity );        
  SDL_RenderFillRect( renderer, &fillRect );
}
