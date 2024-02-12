#include "core/game.hpp"
#include "core/config.hpp"

#include "player.hpp"
#include "box.hpp"

#include <time.h>
#include <iostream>

int main(int argv, char** args)
{
  adv::Config conf;
  conf.title = "Some Squares";
  adv::Game game(conf);

  std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player(adv::Point(100, 100), {0xFF, 0x00, 0x00}, 500));
  game.scene()->add_child_object(player);

  srand(time(NULL));
  for (int i = 0; i < 40; i++)
  {
    std::shared_ptr<Box> box = std::shared_ptr<Box>(new Box(adv::Point(rand() % 12700 + 610, rand() % 7100 + 610),
                                                            {0x00, 0x00, 0xFF},
                                                            rand() % 700 + 100));
    game.scene()->add_child_object(box);
  }

  game.run();

  return 0;
}