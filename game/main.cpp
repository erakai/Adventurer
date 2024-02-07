#include "core/game.hpp"
#include "core/config.hpp"

#include <iostream>

int main()
{
  std::cout << "Booting Adventurer...\n";

  adv::Config conf;
  adv::Game game(conf);

  game.run();

  return 0;
}