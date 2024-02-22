#include "player.hpp"

using namespace adv;

Player::Player(int speed, adv::Point pos, adv::Color color, int side_length)
    : Box(speed, pos, color, side_length)
{
  std::function<void(input::KeyEventType e)> input =
      [this](input::KeyEventType k) { handle_input(k); };
  input::key_hook(input);
}

void Player::handle_input(input::KeyEventType e)
{
  switch (e) {
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
