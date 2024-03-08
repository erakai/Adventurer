#include "player.hpp"
#include "core/game.hpp"
#include "utils/rect.hpp"

using namespace adv;

Player::Player(int speed, adv::Point pos)
    : Entity(speed, adv::Rect(pos.x(), pos.y(), {450, 600}))
{
  std::function<void(input::KeyEventType e)> input =
      [this](input::KeyEventType k) { handle_input(k); };
  input::key_hook(input);
}

void Player::render_self(SDL_Renderer *renderer, adv::Point draw_pos)
{
  SDL_Rect clip = {350, 0, 1220, 1920};
  adv::CURRENT_SCENE->res()->textures["player"].render(
      renderer, adv::Rect(draw_pos.x(), draw_pos.y(), display_size()), clip);
}

void Player::handle_input(input::KeyEventType e)
{
  switch (e)
  {
  case input::LEFT_MOVE_PRESS:
    if (vel().x > -1)
      vel().x -= 1;
    break;
  case input::RIGHT_MOVE_PRESS:
    if (vel().x < 1)
      vel().x += 1;
    break;
  case input::UP_MOVE_PRESS:
    if (vel().y > -1)
      vel().y -= 1;
    break;
  case input::DOWN_MOVE_PRESS:
    if (vel().y < 1)
      vel().y += 1;
    break;
  case input::LEFT_MOVE_RELEASE:
    vel().x += 1;
    break;
  case input::RIGHT_MOVE_RELEASE:
    vel().x -= 1;
    break;
  case input::UP_MOVE_RELEASE:
    vel().y += 1;
    break;
  case input::DOWN_MOVE_RELEASE:
    vel().y -= 1;
    break;

  default:
    break;
  }
}
