#include "box.hpp"
#include "core/game.hpp"
#include "utils/globals.hpp"
#include "utils/rect.hpp"

Box::Box(int speed, adv::Point pos, adv::Color color, int side_length)
    : Entity(speed, pos, {static_cast<int>(side_length * 1.37), side_length}),
      side_length(side_length / adv::globals::SUBPIXELS), color(color)
{
  collider.add_box({0, 0, size().w, static_cast<int>(0.4444 * size().h)});
}

void Box::render_self(SDL_Renderer *renderer, adv::Point draw_pos)
{
  adv::CURRENT_SCENE->res()->textures["decor"].render(
      renderer, adv::Rect(draw_pos.x(), draw_pos.y(), display_size()), "tomb");
}
