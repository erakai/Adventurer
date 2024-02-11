#include "core/game.hpp"
#include "core/config.hpp"

#include "player.hpp"

#include <iostream>

int main(int argv, char** args)
{
  adv::Config conf;
  conf.title = "Some Squares";
  adv::Game game(conf);

  std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player(50));
  game.scene()->add_child_object(player);
  game.run();

  return 0;
}