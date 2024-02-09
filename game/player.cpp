#include "player.hpp"

using namespace adv;

Player::Player() : Entity(20)
{
  pos().x(100);
  pos().y(100);
  
  std::function<void(input::KeyEventType e)> input = [this] (input::KeyEventType k) 
    { handle_input(k);};
  input::key_hook(input);
}


void Player::render(SDL_Renderer* renderer, long delta, PositionRect viewport)
{
  update_display_position(viewport);

  SDL_Rect fillRect = { display_pos().x(), display_pos().y(), 50, 50 };
  SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );        
  SDL_RenderFillRect( renderer, &fillRect );
}

void Player::handle_input(input::KeyEventType e)
{
  switch (e)
  {
    case input::LEFT_MOVE_PRESS:
      if (vel().x > -1) vel().x -= 1;
      break;
    case input::RIGHT_MOVE_PRESS:
      if (vel().x < 1) vel().x += 1;
      break;
    case input::UP_MOVE_PRESS:
      if (vel().y > -1) vel().y -= 1;
      break;
    case input::DOWN_MOVE_PRESS:
      if (vel().y < 1) vel().y += 1;
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