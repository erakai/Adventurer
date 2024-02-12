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

  std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player(1000, adv::Point(0, 0), {0xFF, 0x00, 0x00}, 40));
  game.scene()->add_child(player);
  game.scene()->register_collideable(player, true);

  srand(time(NULL));
  for (int i = 0; i < 20000; i++)
  {
    std::shared_ptr<Box> box = std::shared_ptr<Box>(new Box(0, adv::Point(rand() % conf.screen_width + 40, rand() % conf.screen_height + 40),
                                                            {0x00, 0x00, 0xFF},
                                                            rand() % 40 + 10));
    game.scene()->add_child(box);
    game.scene()->register_collideable(box, false);
  }

  game.run();

  return 0;
}