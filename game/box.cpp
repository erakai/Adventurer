#include "box.hpp"
#include "core/game.hpp"
#include "utils/globals.hpp"
#include "utils/rect.hpp"

Box::Box(int speed, adv::Point pos, adv::Color color, int side_length)
    : Entity(speed, adv::Rect(pos.x(), pos.y(), pos.x() + side_length,
                              pos.y() + side_length)),
      side_length(side_length / adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL),
      color(color)
{
}

void Box::render_self(SDL_Renderer *renderer, adv::Point draw_pos)
{
  adv::CURRENT_SCENE->res()->textures["box"].render(
      renderer, adv::Rect(draw_pos.x(), draw_pos.y(), display_size()));
}
