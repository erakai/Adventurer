#include "core/game.hpp"
#include "core/config.hpp"

#include "player.hpp"

#include <iostream>

int main(int argv, char** args)
{
  std::cout << "Booting Adventurer...\n";

  adv::Config conf;
  adv::Game game(conf);

  std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player(50));
  game.scene()->add_child(player);
  game.run();

  return 0;
}